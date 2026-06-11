function plot_sweep_simulink_lqr(t_end, vals, val_name, ...
                                 Q_base, R_base, ref, ...
                                 ss_index, colors, fig_name, mode)

    model_name = 'Linear_model_LQR';

    K_names  = {'K1',  'K2',  'K3',  'K4'};
    ki_names = {'ki1', 'ki2', 'ki3', 'ki4'};
    all_refs = {'z_ref', 'y_ref', 'x_ref', 'phi_ref'};
    sys_names = {'ss1_augmented', 'ss2_augmented', ...
                 'ss3_augmented', 'ss4_augmented'};

    sys = evalin('base', sys_names{ss_index});

    if ~bdIsLoaded(model_name)
        load_system(model_name);
        fprintf('Loaded model: %s\n', model_name);
    end

    try
        K_orig  = evalin('base', K_names{ss_index});
        ki_orig = evalin('base', ki_names{ss_index});
    catch
        K_orig  = [];
        ki_orig = [];
    end

    fig = figure('Name', fig_name, 'NumberTitle', 'off', 'Visible', 'on');
    sgtitle(sprintf('%s - Effect of %s', fig_name, val_name), ...
            'FontWeight', 'bold', 'FontSize', 12);

    ax1 = axes; hold(ax1, 'on'); grid(ax1, 'on');
    yline(ax1, ref, 'k--', 'LineWidth', 1.2, 'HandleVisibility', 'off');
    ylabel(ax1, 'Position [m]');
    xlabel(ax1, 'Time [s]');
    title(ax1, 'Output Tracking');

    plotted_y = false;

    for i = 1:numel(vals)
        Q = Q_base;
        R = R_base;

        switch upper(mode)
            case 'R'
                R      = vals(i);
                label  = sprintf('R=%.3g', vals(i));
            case 'Q11'
                Q(1,1) = vals(i);
                label  = sprintf('Q_{11}=%.3g', vals(i));
            case 'Q22'
                Q(2,2) = vals(i);
                label  = sprintf('Q_{22}=%.3g', vals(i));
            case 'Q33'
                Q(3,3) = vals(i);
                label  = sprintf('Q_{33}=%.3g', vals(i));
            case 'Q44'
                Q(4,4) = vals(i);
                label  = sprintf('Q_{44}=%.3g', vals(i));
            case 'Q55'
                Q(5,5) = vals(i);
                label  = sprintf('Q_{55}=%.3g', vals(i));
            otherwise
                error('plot_sweep_simulink_lqr: unknown mode "%s"', mode);
        end

        try
            K_lqr = lqr(sys, Q, R);
        catch lqrErr
            fprintf('[SKIP] lqr() failed for %s=%.3g: %s\n', ...
                    mode, vals(i), lqrErr.message);
            continue;
        end

        nx     = length(K_lqr);
        K_new  =  K_lqr(1:nx-1);
        ki_new = -K_lqr(nx);

        assignin('base', K_names{ss_index},  K_new(:).');
        assignin('base', ki_names{ss_index}, ki_new);

        for j = 1:4
            assignin('base', all_refs{j}, 5);
        end
        assignin('base', all_refs{ss_index}, ref);

        set_param(model_name, 'SimulationCommand', 'update');

        fprintf('  Running %s=%.3g  (ref=%g) ...', mode, vals(i), ref);

        try
            simOut = sim(model_name, ...
                'StopTime',       num2str(t_end), ...
                'SrcWorkspace',   'base',          ...
                'SaveOutput',     'on',             ...
                'OutputSaveName', 'yout',           ...
                'SaveTime',       'on',             ...
                'TimeSaveName',   'tout');
            fprintf(' OK\n');
        catch ME
            fprintf('\n[ERROR] sim() failed for %s=%.3g\n', mode, vals(i));
            print_causes(ME, 1);
            continue;
        end

        if ss_index == 1
            plot(ax1, simOut.tout, simOut.y1_meas(:,1), 'LineWidth', 1.5, 'Color', colors(i,:), 'DisplayName', label);
        elseif ss_index == 2
            plot(ax1, simOut.tout, simOut.y2_meas(:,1), 'LineWidth', 1.5, 'Color', colors(i,:), 'DisplayName', label);
        elseif ss_index == 3
            plot(ax1, simOut.tout, simOut.y3_meas(:,1), 'LineWidth', 1.5, 'Color', colors(i,:), 'DisplayName', label);
        elseif ss_index == 4
            plot(ax1, simOut.tout, simOut.y4_meas(:,1), 'LineWidth', 1.5, 'Color', colors(i,:), 'DisplayName', label);
        end
        plotted_y = true;
        drawnow;
    end

    if plotted_y
        legend(ax1, 'Location', 'best');
    else
        text(ax1, 0.5, 0.5, 'No output data.', ...
             'Units', 'normalized', 'HorizontalAlignment', 'center');
    end

    if ~isempty(K_orig)
        assignin('base', K_names{ss_index},  K_orig);
        assignin('base', ki_names{ss_index}, ki_orig);
    end

    figure(fig);
    drawnow;

    % Save figure as PNG
    png_name = strrep(fig_name, ' ', '_');
    png_name = strrep(png_name, '/', '_');
    png_name = strrep(png_name, '\', '_');
    exportgraphics(fig, sprintf('%s.png', png_name), 'Resolution', 300);
    fprintf('Saved: %s.png\n', png_name);

    fprintf('Sweep complete: %s\n\n', fig_name);
end


function print_causes(ME, depth)
    indent = repmat('  ', 1, depth);
    fprintf('%s-> [%s] %s\n', indent, ME.identifier, ME.message);
    for k = 1:numel(ME.cause)
        print_causes(ME.cause{k}, depth+1);
    end
end