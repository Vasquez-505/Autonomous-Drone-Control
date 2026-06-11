%% full_lqr_simulink_run.m

clc;

%% ---- Plant data ----
run ABCDmatrixes_for_linear
run drone_model_parameters


%% ---- Augmented subsystems for servo LQR ----
c1 = [1 0];
c2 = [1 0 0 0];
c3 = [1 0 0 0];
c4 = [1 0];

A1_bar = [A1, zeros(2,1); -c1, 0];
A2_bar = [A2, zeros(4,1); -c2, 0];
A3_bar = [A3, zeros(4,1); -c3, 0];
A4_bar = [A4, zeros(2,1); -c4, 0];

B1_bar = [B1; 0];  B2_bar = [B2; 0];
B3_bar = [B3; 0];  B4_bar = [B4; 0];

C1_bar = [c1, 0];  C2_bar = [c2, 0];
C3_bar = [c3, 0];  C4_bar = [c4, 0];

D1_bar = zeros(1,1);  D2_bar = zeros(1,1);
D3_bar = zeros(1,1);  D4_bar = zeros(1,1);

ss1_augmented = ss(A1_bar, B1_bar, C1_bar, D1_bar);
ss2_augmented = ss(A2_bar, B2_bar, C2_bar, D2_bar);
ss3_augmented = ss(A3_bar, B3_bar, C3_bar, D3_bar);
ss4_augmented = ss(A4_bar, B4_bar, C4_bar, D4_bar);

% System (match Phase I)
x0_1 = [0; 0];        % vertical:      r3=0.5m, v3=0
x0_2 = [0; 0; 0; 0];    % lateral:       all zero
x0_3 = [0; 0; 0; 0];  % longitudinal:  r1=1m, rest zero
x0_4 = [0; 0];          % yaw:           all zero

% Observer (deliberately different from system)
x0_obs1 = [0; 0];
x0_obs2 = [0; 0; 0; 0];
x0_obs3 = [0; 0; 0; 0];
x0_obs4 = [0; 0];

%% ---- Noise parameters ----
Ts    = 0.01;
t_end = 10;

run noise_model_parameters

% Disable noise for clean tuning study
enable_noise = true;
if ~enable_noise
    noise_M_vert = [0 0];      noise_P_vert = [0 0];
    noise_M_lat  = zeros(1,4); noise_P_lat  = zeros(1,4);
    noise_M_lon  = zeros(1,4); noise_P_lon  = zeros(1,4);
    noise_M_yaw  = [0 0];      noise_P_yaw  = [0 0];
end

x0_1 = [0; 0];
x0_2 = [0; 0; 0; 0];
x0_3 = [0; 0; 0; 0];
x0_4 = [0; 0];

%% ---- References (set AFTER noise script) ----
z_ref   = 4;
y_ref   = 4;
x_ref   = 4;
phi_ref = 0;

%% ---- LQR weights ----
dQ = 1;  dR = 1;

Q1 = diag([1,   1,   10]) * dQ;
Q2 = diag([1,   0.1, 0.1, 0.1, 10]) * dQ;
Q3 = diag([1,   0.1, 0.1, 0.1, 10]) * dQ;
Q4 = diag([1,   0.1, 10]) * dQ;

R1 = 1 * dR;  R2 = 1 * dR;
R3 = 1 * dR;  R4 = 1 * dR;

%% ---- Compute LQR gains ----
[K1_lqr,~,~] = lqr(ss1_augmented, Q1, R1);
[K2_lqr,~,~] = lqr(ss2_augmented, Q2, R2);
[K3_lqr,~,~] = lqr(ss3_augmented, Q3, R3);
[K4_lqr,~,~] = lqr(ss4_augmented, Q4, R4);

K1  = K1_lqr(1:2);  ki1 = -K1_lqr(3);
K2  = K2_lqr(1:4);  ki2 = -K2_lqr(5);
K3  = K3_lqr(1:4);  ki3 = -K3_lqr(5);
K4  = K4_lqr(1:2);  ki4 = -K4_lqr(3);

fprintf('\nFull LQR gains:\n');
fprintf('K1=[%s] ki1=%.4g\n', num2str(K1,' %.4g'), ki1);
fprintf('K2=[%s] ki2=%.4g\n', num2str(K2,' %.4g'), ki2);
fprintf('K3=[%s] ki3=%.4g\n', num2str(K3,' %.4g'), ki3);
fprintf('K4=[%s] ki4=%.4g\n', num2str(K4,' %.4g'), ki4);

[L1, P1, E1] = lqe(A1, eye(2), C1, Q0_vert, R0_vert);
[L2, P2, E2] = lqe(A2, eye(4), C2, Q0_lat,  R0_lat);
[L3, P3, E3] = lqe(A3, eye(4), C3, Q0_lon,  R0_lon);
[L4, P4, E4] = lqe(A4, eye(2), C4, Q0_yaw,  R0_yaw);

%% ---- Run full simulation ----
model_name = 'Linear_model_LQR';
simOut = sim(model_name, ...
    'StopTime',       num2str(t_end), ...
    'SrcWorkspace',   'base',          ...
    'SaveOutput',     'on',            ...
    'OutputSaveName', 'yout',          ...
    'SaveTime',       'on',            ...
    'TimeSaveName',   'tout');

%% ---- Plot full simulation ----
figure('Name','Full LQR - Key Outputs','NumberTitle','off','Color','white');

subplot(4,1,1);
plot(simOut.tout, simOut.y1_meas(:,1), 'LineWidth', 1.5); hold on;
yline(z_ref,'k--'); grid on; ylabel('z [m]'); title('Vertical position');

subplot(4,1,2);
plot(simOut.tout, simOut.y2_meas(:,1), 'LineWidth', 1.5); hold on;
yline(y_ref,'k--'); grid on; ylabel('y [m]'); title('Lateral position');

subplot(4,1,3);
plot(simOut.tout, simOut.y3_meas(:,1), 'LineWidth', 1.5); hold on;
yline(x_ref,'k--'); grid on; ylabel('x [m]'); title('Longitudinal position');

subplot(4,1,4);
plot(simOut.tout, simOut.y4_meas(:,1), 'LineWidth', 1.5); hold on;
yline(phi_ref,'k--'); grid on;
ylabel('\phi [rad]'); xlabel('Time [s]'); title('Yaw');

disp('Full LQR simulation complete.');

%% ---- Q/R sweep study ----
colors5      = lines(5);
R_values     = [0.1, 1, 10];
q_scales     = [0.01, 0.1, 1, 10, 100];
q_scales_pos = [0.1,  1,   10, 100, 1000];

fprintf('\nStarting LQR weight study...\n');

% SS1 - Vertical
plot_sweep_simulink_lqr(t_end, R_values,             'R_1',         Q1, R1, z_ref, 1, lines(3),  'SS1 Vertical - Effect of R',             'R');
plot_sweep_simulink_lqr(t_end, Q1(1,1)*q_scales_pos, 'Q_{zz}',      Q1, R1, z_ref, 1, colors5,   'SS1 Vertical - Effect of z weight',       'Q11');
plot_sweep_simulink_lqr(t_end, Q1(2,2)*q_scales,     'Q_{dzdz}',    Q1, R1, z_ref, 1, colors5,   'SS1 Vertical - Effect of dz weight',      'Q22');
plot_sweep_simulink_lqr(t_end, Q1(3,3)*q_scales,     'Q_{\xi_z}',   Q1, R1, z_ref, 1, colors5,   'SS1 Vertical - Effect of integrator',     'Q33');

% SS3 - Longitudinal
plot_sweep_simulink_lqr(t_end, R_values,             'R_3',         Q3, R3, x_ref, 3, lines(3),  'SS3 Longitudinal - Effect of R',          'R');
plot_sweep_simulink_lqr(t_end, Q3(1,1)*q_scales_pos, 'Q_{xx}',      Q3, R3, x_ref, 3, colors5,   'SS3 Longitudinal - Effect of x weight',   'Q11');
plot_sweep_simulink_lqr(t_end, Q3(2,2)*q_scales,     'Q_{\theta}',  Q3, R3, x_ref, 3, colors5,   'SS3 Longitudinal - Effect of theta',      'Q22');
plot_sweep_simulink_lqr(t_end, Q3(3,3)*q_scales,     'Q_{dxdx}',    Q3, R3, x_ref, 3, colors5,   'SS3 Longitudinal - Effect of dx weight',  'Q33');
plot_sweep_simulink_lqr(t_end, Q3(4,4)*q_scales,     'Q_{d\theta}', Q3, R3, x_ref, 3, colors5,   'SS3 Longitudinal - Effect of dtheta',     'Q44');
plot_sweep_simulink_lqr(t_end, Q3(5,5)*q_scales,     'Q_{\xi_x}',   Q3, R3, x_ref, 3, colors5,   'SS3 Longitudinal - Effect of integrator', 'Q55');

disp('LQR weight study complete.');