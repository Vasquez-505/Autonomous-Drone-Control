%% linear_validation.m
% Validation tests for the LINEAR quadcopter model
% Mirrors the structure and visual style of nonlinear_validation.m
% Run tests Q10-Q12 sequentially, generates the plots

%% ── Setup ────────────────────────────────────────────────────────────────
clear; clc; close all;
load('drone_model_parameters.mat');

% Simulation settings
dt       = 0.01;
t_end    = 20;
t_step   = 2;
t        = (0:dt:t_end)';
N        = length(t);

% Hover thrust
F3_hover = 0;

% Step amplitudes
step_F3   = -1.5;
step_M2   = 0.00005;
step_M3   = 0.001;
step_Fext = 0.1;

% Helper: step signal
step_signal = @(before, after) ...
    [before * ones(sum(t < t_step), 1); ...
      after  * ones(sum(t >= t_step), 1)];

%% ── State Space Matrices ──────────────────────────────────────────────────
% Subsystem 1: Altitude (r3, v3)
A1 = [0, 1; 0, 0];
B1 = [0; 1/m];
C1 = eye(2);
D1 = zeros(2,1);

% Subsystem 2: Lateral-Roll (r2, theta1, v2, omega1)
A2 = [0, 0, 1, 0; 0, 0, 0, 1; 0, g, 0, 0; 0, 0, 0, 0];
B2 = [0; 0; 0; 1/J11];
C2 = eye(4);
D2 = zeros(4,1);

% Subsystem 3: Longitudinal-Pitch (r1, theta2, v1, omega2)
A3 = [0, 0, 1, 0; 0, 0, 0, 1; 0, -g, 0, 0; 0, 0, 0, 0];
B3 = [0; 0; 0; 1/J22];
C3 = eye(4);
D3 = zeros(4,1);

% Subsystem 4: Yaw (theta3, omega3)
A4 = [0, 1; 0, 0];
B4 = [0; 1/J33];
C4 = eye(2);
D4 = zeros(2,1);

%% ── Q10: Hover ────────────────────────────────────────────────────────────
fprintf('Running Q10: Hover...\n');

F3  = F3_hover * ones(N, 1);
M1  = zeros(N, 1);
M2  = zeros(N, 1);
M3  = zeros(N, 1);

u_input = [t, F3, M1, M2, M3];

out_Q10 = sim('Linear_model', t_end);

plot_results_linear(out_Q10, 'Q10 - Hover (Linear)');

%% ── Q11_1: Step in F3 ─────────────────────────────────────────────────────
fprintf('Running Q11_1: Step in F3...\n');

F3  = step_signal(0, step_F3);
M1  = zeros(N, 1);
M2  = zeros(N, 1);
M3  = zeros(N, 1);

u_input = [t, F3, M1, M2, M3];

out_Q11_1 = sim('Linear_model', t_end);

plot_results_linear(out_Q11_1, 'Q11_1 - Step in F3 (Linear)');

%% ── Q11_2: Step in M3 (Yaw) ──────────────────────────────────────────────
fprintf('Running Q11_2: Step in M3...\n');

F3  = F3_hover * ones(N, 1);
M1  = zeros(N, 1);
M2  = zeros(N, 1);
M3  = step_signal(0, step_M3);

u_input = [t, F3, M1, M2, M3];

out_Q11_2 = sim('Linear_model', t_end);

plot_results_linear(out_Q11_2, 'Q11_2 - Step in M3 Yaw (Linear)');

%% ── Q11_3: Step in M2 (Pitch) ────────────────────────────────────────────
fprintf('Running Q11_3: Step in M2...\n');

F3  = F3_hover * ones(N, 1);
M1  = zeros(N, 1);
M2  = step_signal(0, step_M2);
M3  = zeros(N, 1);

u_input = [t, F3, M1, M2, M3];

out_Q11_3 = sim('Linear_model', t_end);

plot_results_linear(out_Q11_3, 'Q11_3 - Step in M2 Pitch (Linear)');

%% ── Q12: Takeoff, Rotate and Land ────────────────────────────────────────
fprintf('Running Q12: Takeoff, Rotate and Land...\n');

% ── Task timing ───────────────────────────────────────────────────────────
t_to      = 5;
t_rot     = 10;
t_land    = 5;
t_end_Q12 = t_to + t_rot + t_land;  % 20s total

% ── Acceleration amplitudes ───────────────────────────────────────────────
alfa_to   = -0.016;
alfa_rot  =  pi/25;
alfa_land =  0.016;

% ── Time vector ───────────────────────────────────────────────────────────
t_Q12 = (0:dt:t_end_Q12)';
N_Q12 = length(t_Q12);

% ── Piecewise acceleration helper ─────────────────────────────────────────
acc_profile = @(alfa, tf, t) ...
    (t >= 0 & t < tf/2)  .* alfa + ...
    (t >= tf/2 & t <= tf) .* (-alfa);

% ── Reconstruct inputs ────────────────────────────────────────────────────
F3_r = m   * acc_profile(alfa_to,   t_to,   t_Q12) + ...
       m   * acc_profile(alfa_land, t_land, t_Q12 - t_to - t_rot);

M3_r = J33 * acc_profile(alfa_rot,  t_rot,  t_Q12 - t_to);

% ── Setup simulation inputs ───────────────────────────────────────────────
u_input = [t_Q12, F3_r, zeros(N_Q12,1), zeros(N_Q12,1), M3_r];

% ── Run simulation ────────────────────────────────────────────────────────
out_Q12 = sim('Linear_model', t_end_Q12);

% ── Plot ──────────────────────────────────────────────────────────────────
plot_results_linear(out_Q12, 'Q12 - Takeoff Rotate and Land (Linear)');



%% ── Plotting function for Linear model ───────────────────────────────────
function plot_results_linear(out, test_name)

    % ── Same color palette and style as nonlinear_validation.m ───────────
    c = [0.00 0.45 0.70;   % blue
         0.85 0.33 0.10;   % orange
         0.47 0.67 0.19];  % green

    lw       = 1.8;
    fs       = 10;
    fs_title = 11;

    % ── Extract simulation time ───────────────────────────────────────────
    t_sim = out.tout;

    % ── Extract outputs from each subsystem ──────────────────────────────
    % Variable names match the To Workspace blocks in Linear_model.slx:
    %   out.s1_vertical     → Vertical Displacement     [r3,  v3]
    %   out.s2_lateral      → Lateral Displacement      [r2,  theta1, v2,  omega1]
    %   out.s3_longitudinal → Longitudinal Displacement [r1,  theta2, v1,  omega2]
    %   out.s4_yaw          → Yaw Displacement          [theta3, omega3]

    sub1 = squeeze(out.s1_vertical.Data);
    sub2 = squeeze(out.s2_lateral.Data);
    sub3 = squeeze(out.s3_longitudinal.Data);
    sub4 = squeeze(out.s4_yaw.Data);

    % Ensure column orientation
    if size(sub1,1) ~= length(t_sim), sub1 = sub1'; end
    if size(sub2,1) ~= length(t_sim), sub2 = sub2'; end
    if size(sub3,1) ~= length(t_sim), sub3 = sub3'; end
    if size(sub4,1) ~= length(t_sim), sub4 = sub4'; end

    % ── Reassemble into familiar groups ──────────────────────────────────
    % Position:         [r1,  r2,  r3]
    position = [sub3(:,1), sub2(:,1), sub1(:,1)];

    % Linear velocity:  [v1,  v2,  v3]
    lin_v    = [sub3(:,3), sub2(:,3), sub1(:,2)];

    % Orientation:      [theta1, theta2, theta3]
    orient   = [sub2(:,2), sub3(:,2), sub4(:,1)];

    % Angular velocity: [omega1, omega2, omega3]
    ang_v    = [sub2(:,4), sub3(:,4), sub4(:,2)];

    % ── Extract accelerations from out.acceleration ───────────────────────
    % out.acceleration is the derivative of all 4 subsystem outputs
    % concatenated, giving 12 columns total:
    %   cols  1- 2: d/dt of s1_vertical     → [v3,     a3          ]
    %   cols  3- 6: d/dt of s2_lateral      → [v2,     alpha1, a2, alphadot1]
    %   cols  7-10: d/dt of s3_longitudinal → [v1,     alpha2, a1, alphadot2]
    %   cols 11-12: d/dt of s4_yaw          → [alpha3, alphadot3   ]
    acc_raw = squeeze(out.acceleration.Data);
    if size(acc_raw,1) ~= length(t_sim), acc_raw = acc_raw'; end

    % Linear acceleration  [a1,  a2,  a3]
    lin_acc = [acc_raw(:,9), acc_raw(:,4), acc_raw(:,2)];

    % Angular acceleration [alphadot1, alphadot2, alphadot3]
    ang_acc = [acc_raw(:,6), acc_raw(:,10), acc_raw(:,12)];

    % ════════════════════════════════════════════════════════════════════
    % Figure 1 — States
    % ════════════════════════════════════════════════════════════════════
    figure('Name', [test_name ' - States'], ...
           'NumberTitle', 'off', ...
           'Color', 'white', ...
           'Position', [100 100 1200 900]);

    sgtitle([test_name ' — States'], ...
            'FontSize', 14, 'FontWeight', 'bold', 'Color', [0.15 0.15 0.15]);

    labels_pos = {'r_1 (X)', 'r_2 (Y)', 'r_3 (Z)'};
    labels_vel = {'v_1', 'v_2', 'v_3'};
    labels_acc = {'a_1', 'a_2', 'a_3'};
    labels_ori = {'\theta_1 (roll)', '\theta_2 (pitch)', '\theta_3 (yaw)'};
    labels_wv  = {'\omega_1', '\omega_2', '\omega_3'};
    labels_wa  = {'\alpha_1', '\alpha_2', '\alpha_3'};

    plot_panel(3, 2, 1, t_sim, position, 'Position',             'Position [m]',             labels_pos, c, lw, fs, fs_title);
    plot_panel(3, 2, 2, t_sim, lin_v,    'Linear Velocity',      'Velocity [m/s]',           labels_vel, c, lw, fs, fs_title);
    plot_panel(3, 2, 3, t_sim, lin_acc,  'Linear Acceleration',  'Acceleration [m/s²]',      labels_acc, c, lw, fs, fs_title);
    plot_panel(3, 2, 4, t_sim, orient,   'Orientation',          'Angle [rad]',              labels_ori, c, lw, fs, fs_title);
    plot_panel(3, 2, 5, t_sim, ang_v,    'Angular Velocity',     'Angular velocity [rad/s]', labels_wv,  c, lw, fs, fs_title);
    plot_panel(3, 2, 6, t_sim, ang_acc,  'Angular Acceleration', 'Angular accel. [rad/s²]',  labels_wa,  c, lw, fs, fs_title);

    % ════════════════════════════════════════════════════════════════════
    % Figure 2 — Control Inputs
    % ════════════════════════════════════════════════════════════════════
    figure('Name', [test_name ' - Inputs'], ...
           'NumberTitle', 'off', ...
           'Color', 'white', ...
           'Position', [200 100 1100 550]);

    sgtitle([test_name ' — Control Inputs'], ...
            'FontSize', 14, 'FontWeight', 'bold', 'Color', [0.15 0.15 0.15]);

    input_labels = {'F_3'' [N]', 'M_1 [N·m]', 'M_2 [N·m]', 'M_3 [N·m]'};
    input_titles = {'Vertical Force F_3''', 'Roll Moment M_1', ...
                    'Pitch Moment M_2',     'Yaw Moment M_3'};

    raw = out.input.Data;
    if ndims(raw) == 3
        input_data = squeeze(raw);
    else
        input_data = raw;
    end
    if size(input_data,1) == 4 && size(input_data,2) ~= 4
        input_data = input_data';
    end

    t_in = out.input.Time;

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

end


%% ── Helper: single subplot panel (identical to nonlinear version) ─────────
function plot_panel(rows, cols, idx, t, data, ttl, ylbl, leg, c, lw, fs, fs_t)
    subplot(rows, cols, idx);
    hold on;
    for k = 1:size(data, 2)
        plot(t, data(:, k), 'Color', c(k,:), 'LineWidth', lw);
    end
    yline(0, '--', 'Color', [0.6 0.6 0.6], 'LineWidth', 0.8);
    hold off;

    xlabel('Time [s]', 'FontSize', fs);
    ylabel(ylbl,       'FontSize', fs);
    title(ttl,         'FontSize', fs_t, 'FontWeight', 'bold');
    grid on; grid minor;

    yl    = ylim;
    bound = max(abs(yl)) * 1.1;
    if bound < 1e-6; bound = 1; end
    ylim([-bound, bound]);

    lgd = legend(leg, 'FontSize', fs-1, 'Location', 'eastoutside');
    lgd.Box = 'off';

    set(gca, 'GridAlpha', 0.15, 'MinorGridAlpha', 0.05, ...
             'Box', 'on', 'FontSize', fs);
end