%% nonlinear_validation.m
% Validation tests for the nonlinear quadcopter model (Phase I)
% Run all tests Q2-Q7 sequentially, generates the plots


%% ── Setup ────────────────────────────────────────────────────────────────
clear; clc; close all;
load('drone_model_parameters.mat');

% Simulation settings
dt       = 0.01;            % Time step [s]
t_end    = 20;              % Simulation duration [s]
t_step   = 2;               % Time at which step is applied [s]
t        = (0:dt:t_end)';   % Time vector
N        = length(t);       % Number of time steps

% Hover thrust
F3_hover = -(m * g);           % ≈ -0.618 N

% Step amplitudes
step_F3   = -1.5;            % Extra thrust [N]
step_M2   = 0.00005;          % Pitch moment [N*m]
step_M3   = 0.001;          % Yaw moment [N*m]
step_Fext = 0.1;            % Lateral external force [N]

% Helper function: generates a step signal
% value_before: signal value before step
% value_after:  signal value after step
step_signal = @(before, after) ...
    [before * ones(sum(t < t_step), 1); ...
      after * ones(sum(t >= t_step), 1)];

%% ── Q2: Hover ────────────────────────────────────────────────────────────
fprintf('Running Q2: Hover...\n');

% Constant hover thrust, no moments, no external forces
F3  = F3_hover * ones(N, 1);
M1  = zeros(N, 1);
M2  = zeros(N, 1);
M3  = zeros(N, 1);
F1e = zeros(N, 1);
F2e = zeros(N, 1);
F3e = zeros(N, 1);

u_input  = [t, F3, M1, M2, M3];
ext_input = [t, F1e, F2e, F3e];

out_Q2 = sim('Non_Linear_model', t_end);

plot_results(out_Q2, 'Q2 - Hover');

%% ── Q3: Step in F3 ───────────────────────────────────────────────────────
fprintf('Running Q3: Step in F3...\n');

% Apply extra thrust step at t_step
F3  = step_signal(0, step_F3);
M1  = zeros(N, 1);
M2  = zeros(N, 1);
M3  = zeros(N, 1);
F1e = zeros(N, 1);
F2e = zeros(N, 1);
F3e = zeros(N, 1);

u_input   = [t, F3, M1, M2, M3];
ext_input = [t, F1e, F2e, F3e];

out_Q3 = sim('Non_Linear_model', t_end);

plot_results(out_Q3, 'Q3 - Step in F3');

%% ── Q4: Step in M3 While Hovering (Yaw moment) ──────────────────────────────────────────
fprintf('Running Q4: Step in M3...\n');

% Hover + yaw moment step at t_step
F3  = F3_hover * ones(N, 1);
M1  = zeros(N, 1);
M2  = zeros(N, 1);
M3  = step_signal(0, step_M3);
F1e = zeros(N, 1);
F2e = zeros(N, 1);
F3e = zeros(N, 1);

u_input   = [t, F3, M1, M2, M3];
ext_input = [t, F1e, F2e, F3e];

out_Q4 = sim('Non_Linear_model', t_end);

plot_results(out_Q4, 'Q4 - Step in M3 (Yaw)');

%% ── Q5: Step in M2 While Hovering (Pitch moment) ────────────────────────────────────────
fprintf('Running Q5: Step in M2...\n');

% Hover + pitch moment step at t_step
F3  = F3_hover * ones(N, 1);
M1  = zeros(N, 1);
M2  = step_signal(0, step_M2);
M3  = zeros(N, 1);
F1e = zeros(N, 1);
F2e = zeros(N, 1);
F3e = zeros(N, 1);

u_input   = [t, F3, M1, M2, M3];
ext_input = [t, F1e, F2e, F3e];

out_Q5 = sim('Non_Linear_model', t_end);

plot_results(out_Q5, 'Q5 - Step in M2 (Pitch)');

%% ── Q6: Lateral perturbation ─────────────────────────────────────────────
F3  = F3_hover * ones(N, 1);
M1  = zeros(N, 1);
M2  = zeros(N, 1);
M3  = zeros(N, 1);
F1e = zeros(N, 1);
F2e = zeros(N, 1);
F2e(t >= t_step & t < t_step + 1) = step_Fext;  % 1 second pulse only
F3e = zeros(N, 1);

u_input   = [t, F3, M1, M2, M3];
ext_input = [t, F1e, F2e, F3e];

out_Q6 = sim('Non_Linear_model', t_end);
plot_results(out_Q6, 'Q6 - Lateral Perturbation');

%% ── Q7: Takeoff, Rotate and Land ─────────────────────────────────────────
fprintf('Running Q7: Takeoff, Rotate and Land...\n');
fprintf('NOTE: Make sure the Switch block is set to Takeoff-Rotate-Land input!\n');

% ── Task timing ───────────────────────────────────────────────────────────
t_to   = 5;
t_rot  = 10;
t_land = 5;
t_end_Q7 = t_to + t_rot + t_land;  % 20s total

% ── Acceleration parameters (Section 2.3.1) ──────────────────────────────
alfa_to   = -0.016;
alfa_rot  =  pi/25;
alfa_land =  0.016;

% ── Time vector ───────────────────────────────────────────────────────────
t_Q7 = (0:0.01:t_end_Q7)';
N_Q7 = length(t_Q7);

% ── Reconstruct inputs via Eq. 2.28 ──────────────────────────────────────
F3_r = zeros(N_Q7, 1);
M3_r = zeros(N_Q7, 1);

% ── Piecewise acceleration function Eq. 2.23 ────────────────────────────
function val = q_ddot(alfa, tf, t)
    if t >= 0 && t < tf/2
        val = alfa;
    elseif t >= tf/2 && t <= tf
        val = -alfa;
    else
        val = 0;
    end
end

for k = 1:N_Q7
    tk    = t_Q7(k);
    F3_r(k) = m   * q_ddot(alfa_to,   t_to,   tk) ...
            + m   * q_ddot(alfa_land,  t_land,  tk - t_to - t_rot) ...
            - m   * g;
    M3_r(k) = J33 * q_ddot(alfa_rot,  t_rot,   tk - t_to);
end

% ── Setup simulation inputs ───────────────────────────────────────────────
ext_input = [t_Q7, zeros(N_Q7, 3)];

% ── Run simulation ────────────────────────────────────────────────────────
out_Q7 = sim('Non_Linear_model', t_end_Q7);


% ── Plot ──────────────────────────────────────────────────────────────────
plot_results_Q7(out_Q7, t_Q7, F3_r, M3_r, 'Q7 - Takeoff Rotate Land');

%% ── Plotting function ────────────────────────────────────────────────────
function plot_results(out, test_name)

    c = [0.00 0.45 0.70;
         0.85 0.33 0.10;
         0.47 0.67 0.19];

    lw = 1.8;
    fs = 10;
    fs_title = 11;

    % ════════════════════════════════════════════════════════════════════
    % Figure 1 — States
    % ════════════════════════════════════════════════════════════════════
    figure('Name', [test_name ' — States'], ...
           'NumberTitle', 'off', ...
           'Color', 'white', ...
           'Position', [100 100 1200 750]);

    sgtitle([test_name ' — States'], ...
            'FontSize', 14, 'FontWeight', 'bold', 'Color', [0.15 0.15 0.15]);

    labels_pos = {'r_1 (X)', 'r_2 (Y)', 'r_3 (Z)'};
    labels_vel = {'v_1', 'v_2', 'v_3'};
    labels_acc = {'a_1', 'a_2', 'a_3'};
    labels_ori = {'\theta_1 (roll)', '\theta_2 (pitch)', '\theta_3 (yaw)'};
    labels_wv  = {'\omega_1', '\omega_2', '\omega_3'};
    labels_wa  = {'\alpha_1', '\alpha_2', '\alpha_3'};

    plot_panel(3,2,1, out.tout, out.position.Data,    'Position',             'Position [m]',             labels_pos, c, lw, fs, fs_title);
    plot_panel(3,2,2, out.tout, out.lin_v.Data,       'Linear Velocity',      'Velocity [m/s]',           labels_vel, c, lw, fs, fs_title);
    plot_panel(3,2,3, out.tout, out.lin_acc.Data,     'Linear Acceleration',  'Acceleration [m/s²]',      labels_acc, c, lw, fs, fs_title);
    plot_panel(3,2,4, out.tout, out.orientation.Data, 'Orientation',          'Angle [rad]',              labels_ori, c, lw, fs, fs_title);
    plot_panel(3,2,5, out.tout, out.ang_v.Data,       'Angular Velocity',     'Angular velocity [rad/s]', labels_wv,  c, lw, fs, fs_title);
    plot_panel(3,2,6, out.tout, out.ang_acc.Data,     'Angular Acceleration', 'Angular accel. [rad/s²]',  labels_wa,  c, lw, fs, fs_title);

    % ════════════════════════════════════════════════════════════════════
    % Figure 2 — Control Inputs
    % ════════════════════════════════════════════════════════════════════
    figure('Name', [test_name ' — Inputs'], ...
           'NumberTitle', 'off', ...
           'Color', 'white', ...
           'Position', [200 100 1100 550]);

    sgtitle([test_name ' — Control Inputs'], ...
            'FontSize', 14, 'FontWeight', 'bold', 'Color', [0.15 0.15 0.15]);

    input_labels = {'F_3 [N]', 'M_1 [N·m]', 'M_2 [N·m]', 'M_3 [N·m]'};
    input_titles = {'Vertical Force F_3', 'Roll Moment M_1', ...
                    'Pitch Moment M_2',   'Yaw Moment M_3'};

    raw = out.input_u.Data;
    if ndims(raw) == 3
        input_data = squeeze(raw);
    else
        input_data = raw;
    end
    if size(input_data, 1) == 4 && size(input_data, 2) ~= 4
        input_data = input_data';
    end

    t_in = out.input_u.Time;

    for i = 1:4
        subplot(2, 2, i);
        plot(t_in, input_data(:, i), ...
             'Color', c(min(i,3),:), 'LineWidth', lw);
        yline(0, '--', 'Color', [0.5 0.5 0.5], 'LineWidth', 0.8);
        xlabel('Time [s]', 'FontSize', fs);
        ylabel(input_labels{i}, 'FontSize', fs);
        title(input_titles{i}, 'FontSize', fs_title, 'FontWeight', 'bold');
        grid on; grid minor;
        val = input_data(:, i);
        mn  = min(val); mx = max(val);
        pad = max(abs(mx - mn) * 0.15, 1e-6);
        ylim([mn - pad, mx + pad]);
        set(gca, 'GridAlpha', 0.15, 'MinorGridAlpha', 0.05, ...
                 'Box', 'on', 'FontSize', fs);
    end

    % ════════════════════════════════════════════════════════════════════
    % Figure 3 — External Forces (only shown if non-zero)
    % ════════════════════════════════════════════════════════════════════
    raw_ext = out.ext_forces.Data;
    if ndims(raw_ext) == 3
        ext_data = squeeze(raw_ext);
    else
        ext_data = raw_ext;
    end
    if size(ext_data, 1) == 3 && size(ext_data, 2) ~= 3
        ext_data = ext_data';
    end

    if any(abs(ext_data(:)) > 1e-10)

        figure('Name', [test_name ' — External Forces'], ...
               'NumberTitle', 'off', ...
               'Color', 'white', ...
               'Position', [300 300 1100 320]);

        sgtitle([test_name ' — External Force Perturbation'], ...
                'FontSize', 14, 'FontWeight', 'bold', 'Color', [0.15 0.15 0.15]);

        t_ext = out.ext_forces.Time;

        ext_labels = {'F_{1,ext} [N]', 'F_{2,ext} [N]', 'F_{3,ext} [N]'};
        ext_titles = {'External Force X', 'External Force Y', 'External Force Z'};

        for i = 1:3
            subplot(1, 3, i);
            plot(t_ext, ext_data(:, i), ...
                 'Color', c(i,:), 'LineWidth', lw);
            yline(0, '--', 'Color', [0.5 0.5 0.5], 'LineWidth', 0.8);
            xlabel('Time [s]', 'FontSize', fs);
            ylabel(ext_labels{i}, 'FontSize', fs);
            title(ext_titles{i}, 'FontSize', fs_title, 'FontWeight', 'bold');
            grid on; grid minor;
            val = ext_data(:, i);
            mn  = min(val); mx = max(val);
            pad = max(abs(mx - mn) * 0.3, 1e-4);
            bound = max(abs(mn - pad), abs(mx + pad));
            if bound < 1e-10; bound = 0.1; end
            ylim([-bound, bound]);
            set(gca, 'GridAlpha', 0.15, 'MinorGridAlpha', 0.05, ...
                     'Box', 'on', 'FontSize', fs);
        end

    end

end  


%% ── Helper: single subplot panel ────────────────────────────────────────
function plot_panel(rows, cols, idx, t, data, ttl, ylbl, leg, c, lw, fs, fs_t)
    subplot(rows, cols, idx);
    hold on;
    for k = 1:size(data, 2)
        plot(t, data(:, k), 'Color', c(k,:), 'LineWidth', lw);
    end
    yline(0, '--', 'Color', [0.6 0.6 0.6], 'LineWidth', 0.8);   % zero reference
    hold off;

    xlabel('Time [s]', 'FontSize', fs);
    ylabel(ylbl,       'FontSize', fs);
    title(ttl,         'FontSize', fs_t, 'FontWeight', 'bold');
    grid on; grid minor;

    % ── Improvement 1: y-axis always centered on 0 ───────────────────
    yl = ylim;
    bound = max(abs(yl)) * 1.1;
    if bound < 1e-6; bound = 1; end   % avoid flat zero plots collapsing
    ylim([-bound, bound]);

    % ── Improvement 3: legend outside plot on the right ──────────────
    lgd = legend(leg, 'FontSize', fs-1, 'Location', 'eastoutside');
    lgd.Box = 'off';

    set(gca, 'GridAlpha', 0.15, 'MinorGridAlpha', 0.05, ...
             'Box', 'on', 'FontSize', fs);
end

%% ── Q7 dedicated plot function ───────────────────────────────────────────
function plot_results_Q7(out, t_in, F3_r, M3_r, test_name)

    c = [0.00 0.45 0.70;
         0.85 0.33 0.10;
         0.47 0.67 0.19];
    lw = 1.8; fs = 10; fs_title = 11;
    N  = length(t_in);

    % ════════════════════════════════════════════════════════════════════
    % Figure 1 — States (identical to plot_results)
    % ════════════════════════════════════════════════════════════════════
    figure('Name', [test_name ' — States'], ...
           'NumberTitle', 'off', 'Color', 'white', ...
           'Position', [100 100 1200 750]);

    sgtitle([test_name ' — States'], ...
            'FontSize', 14, 'FontWeight', 'bold', 'Color', [0.15 0.15 0.15]);

    labels_pos = {'r_1 (X)', 'r_2 (Y)', 'r_3 (Z)'};
    labels_vel = {'v_1', 'v_2', 'v_3'};
    labels_acc = {'a_1', 'a_2', 'a_3'};
    labels_ori = {'\theta_1 (roll)', '\theta_2 (pitch)', '\theta_3 (yaw)'};
    labels_wv  = {'\omega_1', '\omega_2', '\omega_3'};
    labels_wa  = {'\alpha_1', '\alpha_2', '\alpha_3'};

    plot_panel(3,2,1, out.tout, out.position.Data,    'Position',             'Position [m]',             labels_pos, c, lw, fs, fs_title);
    plot_panel(3,2,2, out.tout, out.lin_v.Data,       'Linear Velocity',      'Velocity [m/s]',           labels_vel, c, lw, fs, fs_title);
    plot_panel(3,2,3, out.tout, out.lin_acc.Data,     'Linear Acceleration',  'Acceleration [m/s²]',      labels_acc, c, lw, fs, fs_title);
    plot_panel(3,2,4, out.tout, out.orientation.Data, 'Orientation',          'Angle [rad]',              labels_ori, c, lw, fs, fs_title);
    plot_panel(3,2,5, out.tout, out.ang_v.Data,       'Angular Velocity',     'Angular velocity [rad/s]', labels_wv,  c, lw, fs, fs_title);
    plot_panel(3,2,6, out.tout, out.ang_acc.Data,     'Angular Acceleration', 'Angular accel. [rad/s²]',  labels_wa,  c, lw, fs, fs_title);

    % ════════════════════════════════════════════════════════════════════
    % Figure 2 — Reconstructed Inputs (autoscale)
    % ════════════════════════════════════════════════════════════════════
    input_data   = [F3_r, zeros(N,1), zeros(N,1), M3_r];
    input_labels = {'F_3 [N]', 'M_1 [N·m]', 'M_2 [N·m]', 'M_3 [N·m]'};
    input_titles = {'Vertical Force F_3', 'Roll Moment M_1', ...
                    'Pitch Moment M_2',   'Yaw Moment M_3'};

    figure('Name', [test_name ' — Inputs'], ...
           'NumberTitle', 'off', 'Color', 'white', ...
           'Position', [200 100 1100 550]);

    sgtitle([test_name ' — Control Inputs (reconstructed)'], ...
            'FontSize', 14, 'FontWeight', 'bold', 'Color', [0.15 0.15 0.15]);

    for i = 1:4
        subplot(2, 2, i);
        plot(t_in, input_data(:, i), ...
             'Color', c(min(i,3),:), 'LineWidth', lw);
        yline(0, '--', 'Color', [0.5 0.5 0.5], 'LineWidth', 0.8);
        xlabel('Time [s]', 'FontSize', fs);
        ylabel(input_labels{i}, 'FontSize', fs);
        title(input_titles{i}, 'FontSize', fs_title, 'FontWeight', 'bold');
        grid on; grid minor;

        % ── Autoscale to show signal range clearly ────────────────────
        val = input_data(:, i);
        mn  = min(val); mx = max(val);
        pad = max(abs(mx - mn) * 0.15, 1e-6);
        ylim([mn - pad, mx + pad]);

        set(gca, 'GridAlpha', 0.15, 'MinorGridAlpha', 0.05, ...
                 'Box', 'on', 'FontSize', fs);
    end

end