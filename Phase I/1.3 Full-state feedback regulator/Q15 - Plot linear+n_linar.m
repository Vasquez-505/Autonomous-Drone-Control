%% Q14_plot_combined.m
% Loads linear_data.mat and n_linear_data.mat and plots both on the same figures.
% Run Q14_pole_placement_linear.m and Q14_pole_placement_nonlinear.m first
% to generate the .mat files.

clear all
clc

%% 1. Load data
lin  = load('linear_data.mat');
nlin = load('n_linear_data.mat');

%% 2. Style
c_x = [0.00 0.45 0.70];   % blue
c_y = [0.85 0.33 0.10];   % orange
c_z = [0.47 0.67 0.19];   % green
lw  = 1.8;  fs = 10;  fs_t = 11;

ic_names = { ...
    'IC1: r_3 = 0.5 m (altitude)'; ...
    'IC2: r_1 = 1 m (longitudinal)'; ...
    'IC3: r_3=0.5, r_1=1, v_2=2 m/s, \theta_1=0.1, \theta_2=0.1, \omega_1=0.2 rad/s'};

n_ic = 3;

%% 3. Extract linear states from results cell
% linear_data.mat contains: results{idx} with out.yout (Nx12) and out.tout
function S = get_linear(results, idx)
    out  = results{idx};
    yout = out.yout;
    S.t  = out.tout;
    Dz   = yout(:,1:2);
    Dy   = yout(:,3:6);
    Dx   = yout(:,7:10);
    Dphi = yout(:,11:12);
    S.r1=Dx(:,1); S.r2=Dy(:,1); S.r3=Dz(:,1);
    S.v1=Dx(:,3); S.v2=Dy(:,3); S.v3=Dz(:,2);
    S.th1=Dy(:,2); S.th2=Dx(:,2); S.th3=Dphi(:,1);
    S.w1=Dy(:,4);  S.w2=Dx(:,4);  S.w3=Dphi(:,2);
end

%% 4. Extract nonlinear states from results cell
% n_linear_data.mat contains: results{idx} with out.position, out.lin_v, etc.
function S = get_nonlinear(results, idx)
    out  = results{idx};
    S.t  = out.tout;
    S.r1 = out.position.Data(:,1);
    S.r2 = out.position.Data(:,2);
    S.r3 = out.position.Data(:,3);
    S.v1 = out.lin_v.Data(:,1);
    S.v2 = out.lin_v.Data(:,2);
    S.v3 = out.lin_v.Data(:,3);
    S.th1= out.orientation.Data(:,1);
    S.th2= out.orientation.Data(:,2);
    S.th3= out.orientation.Data(:,3);
    S.w1 = out.ang_v.Data(:,1);
    S.w2 = out.ang_v.Data(:,2);
    S.w3 = out.ang_v.Data(:,3);
end

%% 5. Plot
for idx = 1:n_ic

    % --- get data ---
    L = []; NL = [];
    try; L  = get_linear(lin.results,   idx); catch ME
        warning('Linear IC%d: %s', idx, ME.message);
    end
    try; NL = get_nonlinear(nlin.results, idx); catch ME
        warning('Nonlinear IC%d: %s', idx, ME.message);
    end
    if isempty(L) && isempty(NL); continue; end

    figure('Name', sprintf('Q14 Lin vs NLin IC%d', idx), ...
           'NumberTitle','off','Color','white','Position',[60+idx*30 60 1050 820]);
    sgtitle(sprintf('Linear (—) vs Nonlinear (- -) | %s', ic_names{idx}), ...
            'FontSize',12,'FontWeight','bold','Color',[0.15 0.15 0.15]);

    colors = {c_x; c_y; c_z};
    rlabels  = {'r_1 (x)','r_2 (y)','r_3 (z)'};
    vlabels  = {'v_1','v_2','v_3'};
    thlabels = {'\theta_1','\theta_2','\theta_3'};
    wlabels  = {'\omega_1','\omega_2','\omega_3'};

    L_pos  = {[],[],[]};  NL_pos  = {[],[],[]};
    L_vel  = {[],[],[]};  NL_vel  = {[],[],[]};
    L_ang  = {[],[],[]};  NL_ang  = {[],[],[]};
    L_omg  = {[],[],[]};  NL_omg  = {[],[],[]};

    if ~isempty(L)
        L_pos  = {L.r1,  L.r2,  L.r3 };
        L_vel  = {L.v1,  L.v2,  L.v3 };
        L_ang  = {L.th1, L.th2, L.th3};
        L_omg  = {L.w1,  L.w2,  L.w3 };
    end
    if ~isempty(NL)
        NL_pos = {NL.r1,  NL.r2,  NL.r3 };
        NL_vel = {NL.v1,  NL.v2,  NL.v3 };
        NL_ang = {NL.th1, NL.th2, NL.th3};
        NL_omg = {NL.w1,  NL.w2,  NL.w3 };
    end

    sp_data   = {L_pos,  NL_pos,  L_vel,  NL_vel, ...
                 L_ang,  NL_ang,  L_omg,  NL_omg};
    sp_ylabel = {'Position [m]','Velocity [m/s]', ...
                 'Angle [rad]','Angular velocity [rad/s]'};
    sp_title  = {'Position','Linear Velocity','Orientation','Angular Velocity'};
    sp_labels = {rlabels, vlabels, thlabels, wlabels};
    t_L  = []; if ~isempty(L);  t_L  = L.t;  end
    t_NL = []; if ~isempty(NL); t_NL = NL.t; end

    for sp = 1:4
        subplot(4,1,sp); hold on;
        Ldata  = sp_data{2*sp-1};   % linear data set for this subplot
        NLdata = sp_data{2*sp  };   % nonlinear data set for this subplot
        % Plot all linear first, then all nonlinear (controls legend order)
        for j = 1:3
            if ~isempty(L) && ~isempty(Ldata{j})
                plot(t_L,  Ldata{j},  '-',  'Color',colors{j}, 'LineWidth',lw, ...
                     'DisplayName',['Lin '  sp_labels{sp}{j}]);
            end
        end
        for j = 1:3
            if ~isempty(NL) && ~isempty(NLdata{j})
                plot(t_NL, NLdata{j}, '--', 'Color',colors{j}, 'LineWidth',lw, ...
                     'DisplayName',['NLin ' sp_labels{sp}{j}]);
            end
        end
        hold off;
        ylabel(sp_ylabel{sp},'FontSize',fs);
        xlabel('Time [s]','FontSize',fs);
        title(sp_title{sp},'FontSize',fs_t,'FontWeight','bold');
        legend('Location','eastoutside','FontSize',fs-1,'Box','off');
        grid on; grid minor;
        set(gca,'Color','white','GridAlpha',0.15,'MinorGridAlpha',0.05, ...
                'Box','on','FontSize',fs);
    end

    % line-style legend annotation
    annotation('textbox',[0.01 0.005 0.3 0.025], ...
               'String','— Linear     - - Nonlinear', ...
               'EdgeColor','none','FontSize',9,'Color',[0.3 0.3 0.3]);
end

fprintf('Combined plot complete.\n');