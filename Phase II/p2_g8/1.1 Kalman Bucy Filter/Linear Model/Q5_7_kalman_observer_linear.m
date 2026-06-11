%% Setup - Run this first before any simulation
drone_model_parameters

% --- State-space matrices ---
A1 = [0, 1; 0, 0];
B1 = [0; 1/m];
C1 = eye(2);
D1 = zeros(2, 1);

A2 = [0, 0, 1, 0; 0, 0, 0, 1; 0, g, 0, 0; 0, 0, 0, 0];
B2 = [0; 0; 0; 1/J11];
C2 = eye(4);
D2 = zeros(4, 1);

A3 = [0, 0, 1, 0; 0, 0, 0, 1; 0, -g, 0, 0; 0, 0, 0, 0];
B3 = [0; 0; 0; 1/J22];
C3 = eye(4);
D3 = zeros(4, 1);

A4 = [0, 1; 0, 0];
B4 = [0; 1/J33];
C4 = eye(2);
D4 = zeros(2, 1);

% --- Simulation settings ---
Ts    = 0.01;
t_end = 10;

% --- References (same as Phase I) ---
z_ref   = 4;
y_ref   = 1;
x_ref   = 2;
phi_ref = 0.5;

% --- Measurement noise variances (Table 2.1) ---
var_M_r1  = 7.3221e-1;
var_M_r2  = 4.2821e-1;
var_M_r3  = 1.8010e-3;
var_M_th1 = 3.4817e-4;
var_M_th2 = 2.6060e-4;
var_M_th3 = 3.8313e-2;
var_M_om1 = 1.8271e-6;
var_M_om2 = 4.1449e-6;
var_M_om3 = 7.0775e-6;
var_M_v1  = 2.2190e-3;
var_M_v2  = 2.2190e-3;
var_M_v3  = 1.8271e-4;

% --- Process noise variances (Table 2.2) ---
var_P_r1  = 9e-1;
var_P_r2  = 9e-1;
var_P_r3  = 1e-1;
var_P_th1 = 3e-1;
var_P_th2 = 2e-1;
var_P_th3 = 1e-1;
var_P_om1 = 1e-3;
var_P_om2 = 1e-3;
var_P_om3 = 1e-3;
var_P_v1  = 2e-1;
var_P_v2  = 2e-1;
var_P_v3  = 1e-2;

% --- Noise power vectors for Simulink Band-Limited White Noise blocks ---
noise_M_vert = [var_M_r3,  var_M_v3]                         * Ts;
noise_P_vert = [var_P_r3,  var_P_v3]                         * Ts;
noise_M_lat  = [var_M_r2,  var_M_th1, var_M_v2,  var_M_om1] * Ts;
noise_P_lat  = [var_P_r2,  var_P_th1, var_P_v2,  var_P_om1] * Ts;
noise_M_lon  = [var_M_r1,  var_M_th2, var_M_v1,  var_M_om2] * Ts;
noise_P_lon  = [var_P_r1,  var_P_th2, var_P_v1,  var_P_om2] * Ts;
noise_M_yaw  = [var_M_th3, var_M_om3]                        * Ts;
noise_P_yaw  = [var_P_th3, var_P_om3]                        * Ts;

% --- Optimal covariance matrices per subsystem ---
Q0_vert = diag([var_P_r3,  var_P_v3]);
R0_vert = diag([var_M_r3,  var_M_v3]);

Q0_lat  = diag([var_P_r2,  var_P_th1, var_P_v2,  var_P_om1]);
R0_lat  = diag([var_M_r2,  var_M_th1, var_M_v2,  var_M_om1]);

Q0_lon  = diag([var_P_r1,  var_P_th2, var_P_v1,  var_P_om2]);
R0_lon  = diag([var_M_r1,  var_M_th2, var_M_v1,  var_M_om2]);

Q0_yaw  = diag([var_P_th3, var_P_om3]);
R0_yaw  = diag([var_M_th3, var_M_om3]);

% --- Initial values for Kalman Filter blocks (optimal) ---
Q0_vert_k = Q0_vert;    R0_vert_k = R0_vert;
Q0_lat_k  = Q0_lat;     R0_lat_k  = R0_lat;
Q0_lon_k  = Q0_lon;     R0_lon_k  = R0_lon;
Q0_yaw_k  = Q0_yaw;     R0_yaw_k  = R0_yaw;

% --- Pole-placement regulator gains (from Phase I) ---
K1 = place(A1, B1, poles1);
K2 = place(A2, B2, poles2);
K3 = place(A3, B3, poles3);
K4 = place(A4, B4, poles4);

ki1 = prefilter(A1, B1, C1(1,:), K1);
ki2 = prefilter(A2, B2, C2(1,:), K2);
ki3 = prefilter(A3, B3, C3(1,:), K3);
ki4 = prefilter(A4, B4, C4(1,:), K4);

% --- Initial conditions ---
% System
x0_1 = [0; 0];
x0_2 = [0; 0; 0; 0];
x0_3 = [0; 0; 0; 0];
x0_4 = [0; 0];

% Observer (deliberately different from system)
x0_obs1 = [3; 0];
x0_obs2 = [3; 0; 0; 0];
x0_obs3 = [3; 0; 0; 0];
x0_obs4 = [0.5; 0];

% --- Load Simulink model ---
model_name = 'Linear_model_Kalman_Bucy';
if bdIsLoaded(model_name); close_system(model_name, 0); end
load_system(model_name);

fprintf('Setup complete. Ready to run Q5, Q6, Q7.\n');

%% Q5 - Observer Convergence (optimal Q0 and R0)
% Kalman Filter blocks already use optimal _k values from Setup
out_Q5 = sim(model_name, t_end);

t       = out_Q5.tout;
y1_meas = out_Q5.y1_meas;    x1_hat = out_Q5.x1_hat;
y2_meas = out_Q5.y2_meas;    x2_hat = out_Q5.x2_hat;
y3_meas = out_Q5.y3_meas;    x3_hat = out_Q5.x3_hat;
y4_meas = out_Q5.y4_meas;    x4_hat = out_Q5.x4_hat;

plot_key_outputs(t, y1_meas, x1_hat, y2_meas, x2_hat, ...
                    y3_meas, x3_hat, y4_meas, x4_hat, 'Q5');
fprintf('Q5 complete.\n');

%% Q6 - Sensitivity Analysis: Q0 (R0 fixed at optimal)
Q0_scales = [0.01, 0.1, 1, 10, 100];
Q0_labels = {'$Q_0 \times 0.01$', '$Q_0 \times 0.1$', 'Optimal $Q_0$', ...
             '$Q_0 \times 10$', '$Q_0 \times 100$'};
colors_Q6 = [0.85 0.33 0.10;
             0.93 0.69 0.13;
             0.00 0.45 0.70;
             0.47 0.67 0.19;
             0.49 0.18 0.56];

results_Q6 = cell(5, 1);

for k = 1:5
    fprintf('\nQ6: Running %s ...\n', Q0_labels{k});

    % Scale Q0 for all Kalman Filter blocks
    Q0_vert_k = Q0_vert * Q0_scales(k);
    Q0_lat_k  = Q0_lat  * Q0_scales(k);
    Q0_lon_k  = Q0_lon  * Q0_scales(k);
    Q0_yaw_k  = Q0_yaw  * Q0_scales(k);

    % R0 stays optimal
    R0_vert_k = R0_vert;
    R0_lat_k  = R0_lat;
    R0_lon_k  = R0_lon;
    R0_yaw_k  = R0_yaw;

    out_Q6 = sim(model_name, t_end);
    results_Q6{k}.t       = out_Q6.tout;
    results_Q6{k}.y1_meas = out_Q6.y1_meas;    results_Q6{k}.x1_hat = out_Q6.x1_hat;
    results_Q6{k}.y2_meas = out_Q6.y2_meas;    results_Q6{k}.x2_hat = out_Q6.x2_hat;
    results_Q6{k}.y3_meas = out_Q6.y3_meas;    results_Q6{k}.x3_hat = out_Q6.x3_hat;
    results_Q6{k}.y4_meas = out_Q6.y4_meas;    results_Q6{k}.x4_hat = out_Q6.x4_hat;
end

% Restore optimal values
Q0_vert_k = Q0_vert;    R0_vert_k = R0_vert;
Q0_lat_k  = Q0_lat;     R0_lat_k  = R0_lat;
Q0_lon_k  = Q0_lon;     R0_lon_k  = R0_lon;
Q0_yaw_k  = Q0_yaw;     R0_yaw_k  = R0_yaw;

plot_sensitivity(results_Q6, Q0_labels, colors_Q6, 'Q6 - Q0 Sensitivity Analysis');
fprintf('Q6 complete.\n');

%% Q7 - Sensitivity Analysis: R0 (Q0 fixed at optimal)
R0_scales = [0.01, 0.1, 1, 10, 100];
R0_labels = {'$R_0 \times 0.01$', '$R_0 \times 0.1$', 'Optimal $R_0$', ...
             '$R_0 \times 10$', '$R_0 \times 100$'};
colors_Q7 = [0.85 0.33 0.10;
             0.93 0.69 0.13;
             0.00 0.45 0.70;
             0.47 0.67 0.19;
             0.49 0.18 0.56];

results_Q7 = cell(5, 1);

for k = 1:5
    fprintf('\nQ7: Running %s ...\n', R0_labels{k});

    % Q0 stays optimal
    Q0_vert_k = Q0_vert;
    Q0_lat_k  = Q0_lat;
    Q0_lon_k  = Q0_lon;
    Q0_yaw_k  = Q0_yaw;

    % Scale R0 for all Kalman Filter blocks
    R0_vert_k = R0_vert * R0_scales(k);
    R0_lat_k  = R0_lat  * R0_scales(k);
    R0_lon_k  = R0_lon  * R0_scales(k);
    R0_yaw_k  = R0_yaw  * R0_scales(k);

    out_Q7 = sim(model_name, t_end);
    results_Q7{k}.t       = out_Q7.tout;
    results_Q7{k}.y1_meas = out_Q7.y1_meas;    results_Q7{k}.x1_hat = out_Q7.x1_hat;
    results_Q7{k}.y2_meas = out_Q7.y2_meas;    results_Q7{k}.x2_hat = out_Q7.x2_hat;
    results_Q7{k}.y3_meas = out_Q7.y3_meas;    results_Q7{k}.x3_hat = out_Q7.x3_hat;
    results_Q7{k}.y4_meas = out_Q7.y4_meas;    results_Q7{k}.x4_hat = out_Q7.x4_hat;
end

% Restore optimal values
Q0_vert_k = Q0_vert;    R0_vert_k = R0_vert;
Q0_lat_k  = Q0_lat;     R0_lat_k  = R0_lat;
Q0_lon_k  = Q0_lon;     R0_lon_k  = R0_lon;
Q0_yaw_k  = Q0_yaw;     R0_yaw_k  = R0_yaw;

plot_sensitivity(results_Q7, R0_labels, colors_Q7, 'Q7 - R0 Sensitivity Analysis');
fprintf('Q7 complete.\n');
fprintf('\nAll Q5-Q7 complete.\n');

%% Helper Functions

function plot_key_outputs(t, y1_meas, x1_hat, y2_meas, x2_hat, ...
                             y3_meas, x3_hat, y4_meas, x4_hat, prefix)
    lw     = 1.5;
    fs     = 10;
    fs_t   = 11;
    c_meas = [0.00 0.45 0.70];
    c_est  = [0.85 0.33 0.10];

    figure('Name', sprintf('%s - Key Outputs', prefix), ...
           'NumberTitle', 'off', 'Color', 'white', ...
           'Position', [100 100 600 800]);
    sgtitle(sprintf('%s | Key Outputs: $r_1$, $r_2$, $r_3$, $\\theta_3$', prefix), ...
            'FontSize', 12, 'FontWeight', 'bold', 'Interpreter', 'latex');

    subplot(4,1,1); hold on;
    plot(t, y1_meas(:,1), 'Color', c_meas, 'LineWidth', lw, 'DisplayName', 'Measured');
    plot(t, x1_hat(:,1),  'Color', c_est,  'LineWidth', lw, 'DisplayName', 'Estimated');
    hold off;
    ylabel('$r_3$ [m]', 'Interpreter', 'latex', 'FontSize', fs);
    xlabel('Time [s]', 'FontSize', fs);
    title('Vertical Position $r_3$', 'Interpreter', 'latex', 'FontSize', fs_t, 'FontWeight', 'bold');
    legend('Location', 'eastoutside', 'FontSize', fs-1, 'Box', 'off');
    grid on; grid minor;
    set(gca, 'Color', 'white', 'GridAlpha', 0.15, 'Box', 'on', 'FontSize', fs);

    subplot(4,1,2); hold on;
    plot(t, y2_meas(:,1), 'Color', c_meas, 'LineWidth', lw, 'DisplayName', 'Measured');
    plot(t, x2_hat(:,1),  'Color', c_est,  'LineWidth', lw, 'DisplayName', 'Estimated');
    hold off;
    ylabel('$r_2$ [m]', 'Interpreter', 'latex', 'FontSize', fs);
    xlabel('Time [s]', 'FontSize', fs);
    title('Lateral Position $r_2$', 'Interpreter', 'latex', 'FontSize', fs_t, 'FontWeight', 'bold');
    legend('Location', 'eastoutside', 'FontSize', fs-1, 'Box', 'off');
    grid on; grid minor;
    set(gca, 'Color', 'white', 'GridAlpha', 0.15, 'Box', 'on', 'FontSize', fs);

    subplot(4,1,3); hold on;
    plot(t, y3_meas(:,1), 'Color', c_meas, 'LineWidth', lw, 'DisplayName', 'Measured');
    plot(t, x3_hat(:,1),  'Color', c_est,  'LineWidth', lw, 'DisplayName', 'Estimated');
    hold off;
    ylabel('$r_1$ [m]', 'Interpreter', 'latex', 'FontSize', fs);
    xlabel('Time [s]', 'FontSize', fs);
    title('Longitudinal Position $r_1$', 'Interpreter', 'latex', 'FontSize', fs_t, 'FontWeight', 'bold');
    legend('Location', 'eastoutside', 'FontSize', fs-1, 'Box', 'off');
    grid on; grid minor;
    set(gca, 'Color', 'white', 'GridAlpha', 0.15, 'Box', 'on', 'FontSize', fs);

    subplot(4,1,4); hold on;
    plot(t, y4_meas(:,1), 'Color', c_meas, 'LineWidth', lw, 'DisplayName', 'Measured');
    plot(t, x4_hat(:,1),  'Color', c_est,  'LineWidth', lw, 'DisplayName', 'Estimated');
    hold off;
    ylabel('$\theta_3$ [rad]', 'Interpreter', 'latex', 'FontSize', fs);
    xlabel('Time [s]', 'FontSize', fs);
    title('Yaw $\theta_3$', 'Interpreter', 'latex', 'FontSize', fs_t, 'FontWeight', 'bold');
    legend('Location', 'eastoutside', 'FontSize', fs-1, 'Box', 'off');
    grid on; grid minor;
    set(gca, 'Color', 'white', 'GridAlpha', 0.15, 'Box', 'on', 'FontSize', fs);

    plot_subsystem(t, y1_meas, x1_hat, sprintf('%s - Vertical Subsystem (SS1)', prefix), ...
        {'$r_3$ [m]', '$\dot{r}_3$ [m/s]'}, c_meas, c_est, lw, fs, fs_t);
    plot_subsystem(t, y2_meas, x2_hat, sprintf('%s - Lateral Subsystem (SS2)', prefix), ...
        {'$r_2$ [m]', '$\theta_1$ [rad]', '$\dot{r}_2$ [m/s]', '$\dot{\theta}_1$ [rad/s]'}, ...
        c_meas, c_est, lw, fs, fs_t);
    plot_subsystem(t, y3_meas, x3_hat, sprintf('%s - Longitudinal Subsystem (SS3)', prefix), ...
        {'$r_1$ [m]', '$\theta_2$ [rad]', '$\dot{r}_1$ [m/s]', '$\dot{\theta}_2$ [rad/s]'}, ...
        c_meas, c_est, lw, fs, fs_t);
    plot_subsystem(t, y4_meas, x4_hat, sprintf('%s - Yaw Subsystem (SS4)', prefix), ...
        {'$\theta_3$ [rad]', '$\dot{\theta}_3$ [rad/s]'}, c_meas, c_est, lw, fs, fs_t);
end

function plot_subsystem(t, y_meas, x_hat, fig_title, state_labels, ...
                        c_meas, c_est, lw, fs, fs_t)
    n = size(y_meas, 2);
    figure('Name', fig_title, 'NumberTitle', 'off', 'Color', 'white', ...
           'Position', [100 100 600 200*n]);
    sgtitle(fig_title, 'FontSize', 12, 'FontWeight', 'bold', 'Interpreter', 'latex');
    for i = 1:n
        subplot(n, 1, i); hold on;
        plot(t, y_meas(:,i), 'Color', c_meas, 'LineWidth', lw, 'DisplayName', 'Measured');
        plot(t, x_hat(:,i),  'Color', c_est,  'LineWidth', lw, 'DisplayName', 'Estimated');
        hold off;
        ylabel(state_labels{i}, 'Interpreter', 'latex', 'FontSize', fs);
        xlabel('Time [s]', 'FontSize', fs);
        title(state_labels{i}, 'Interpreter', 'latex', 'FontSize', fs_t, 'FontWeight', 'bold');
        legend('Location', 'eastoutside', 'FontSize', fs-1, 'Box', 'off');
        grid on; grid minor;
        set(gca, 'Color', 'white', 'GridAlpha', 0.15, 'Box', 'on', 'FontSize', fs);
    end
end

function plot_sensitivity(results, labels, colors, fig_title)
    lw   = 1.0;
    fs   = 10;
    fs_t = 11;
    state_names        = {'$r_3$ [m]', '$r_2$ [m]', '$r_1$ [m]', '$\theta_3$ [rad]'};
    state_titles_plain = {'Vertical Position r3', 'Lateral Position r2', ...
                          'Longitudinal Position r1', 'Yaw theta3'};
    state_titles_latex = {'Vertical Position $r_3$', 'Lateral Position $r_2$', ...
                          'Longitudinal Position $r_1$', 'Yaw $\theta_3$'};
    fields      = {'x1_hat', 'x2_hat', 'x3_hat', 'x4_hat'};
    state_idx   = {1, 1, 1, 1};
    optimal_idx = 3;

    for s = 1:4
        figure('Name', sprintf('%s - %s', fig_title, state_titles_plain{s}), ...
               'NumberTitle', 'off', 'Color', 'white', 'Position', [100 100 700 400]);
        hold on;
        for k = 1:length(results)
            if k == optimal_idx; continue; end
            t     = results{k}.t;
            x_hat = results{k}.(fields{s});
            plot(t, x_hat(:, state_idx{s}), 'Color', colors(k,:), 'LineWidth', lw, ...
                 'DisplayName', labels{k});
        end
        t     = results{optimal_idx}.t;
        x_hat = results{optimal_idx}.(fields{s});
        plot(t, x_hat(:, state_idx{s}), 'Color', colors(optimal_idx,:), 'LineWidth', lw*2, ...
             'DisplayName', labels{optimal_idx});
        hold off;
        ylabel(state_names{s}, 'Interpreter', 'latex', 'FontSize', fs);
        xlabel('Time [s]', 'FontSize', fs);
        title(state_titles_latex{s}, 'Interpreter', 'latex', 'FontSize', fs_t, 'FontWeight', 'bold');
        legend('Location', 'eastoutside', 'FontSize', fs-1, 'Box', 'off', 'Interpreter', 'latex');
        grid on; grid minor;
        set(gca, 'Color', 'white', 'GridAlpha', 0.15, 'Box', 'on', 'FontSize', fs);
    end
end

function ki = prefilter(A, B, C, K)
    Acl = A - B*K;
    dcg = -C * (Acl \ B);
    ki  = 1 / dcg(1);
end