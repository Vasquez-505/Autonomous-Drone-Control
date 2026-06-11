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

%% ---- Noise parameters ----
Ts    = 0.01;
t_end = 5;

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

%% ---- Run full simulation - Model 1 ----
model_name_1 = 'Linear_model_LQR_obs';
simOut1 = sim(model_name_1, ...
    'StopTime',       num2str(t_end), ...
    'SrcWorkspace',   'base',          ...
    'SaveOutput',     'on',            ...
    'OutputSaveName', 'yout',          ...
    'SaveTime',       'on',            ...
    'TimeSaveName',   'tout');

%% ---- Run full simulation - Model 2 ----
model_name_2 = 'Linear_model_LQR';   
simOut2 = sim(model_name_2, ...
    'StopTime',       num2str(t_end), ...
    'SrcWorkspace',   'base',          ...
    'SaveOutput',     'on',            ...
    'OutputSaveName', 'yout',          ...
    'SaveTime',       'on',            ...
    'TimeSaveName',   'tout');

%% ---- Plot comparison ----
color1 = [0.00, 0.45, 0.74];   % blue  – Model 1
color2 = [0.85, 0.33, 0.10];   % red   – Model 2
lw     = 1.5;

labels = {'LQR- without observer', 'LQR'};

figure('Name','Comparison - Key Outputs','NumberTitle','off', ...
       'Color','white','Units','normalized','Position',[0.05 0.05 0.55 0.85]);

% --- Subplot 1: Vertical position (z) ---
ax1 = axes(); 
plot(simOut1.tout, simOut1.y1_meas(:,1), '-',  'Color', color1, 'LineWidth', lw); hold on;
plot(simOut2.tout, simOut2.y1_meas(:,1), '--', 'Color', color2, 'LineWidth', lw);
yline(z_ref, 'k:', 'LineWidth', 1.2);
grid on;
ylabel('z [m]');
title('Vertical position');
legend([labels, {'Reference'}], 'Location', 'northwest');  % <-- moved to northwest

% --- Zoom region ---
x_zoom = [3, 3.25];
y_zoom_margin = 0.05;

mask1 = simOut1.tout >= x_zoom(1) & simOut1.tout <= x_zoom(2);
mask2 = simOut2.tout >= x_zoom(1) & simOut2.tout <= x_zoom(2);
y_vals = [simOut1.y1_meas(mask1,1); simOut2.y1_meas(mask2,1)];
y_zoom = [min(y_vals) - y_zoom_margin, max(y_vals) + y_zoom_margin];

rectangle('Position', [x_zoom(1), y_zoom(1), diff(x_zoom), diff(y_zoom)], ...
    'EdgeColor', 'k', 'LineStyle', '--', 'LineWidth', 1.0);

% --- Save position BEFORE inset ---
ax1_pos = get(ax1, 'Position');

% --- Inset axes — shifted left and made narrower ---
inset = axes('Position', [
    ax1_pos(1) + ax1_pos(3)*0.38, ...   % left  (was 0.55 — now more centered)
    ax1_pos(2) + ax1_pos(4)*0.08, ...   % bottom
    ax1_pos(3)*0.30, ...                % width (was 0.38 — now narrower)
    ax1_pos(4)*0.45  ...                % height
]);

plot(simOut1.tout, simOut1.y1_meas(:,1), '-',  'Color', color1, 'LineWidth', lw); hold on;
plot(simOut2.tout, simOut2.y1_meas(:,1), '--', 'Color', color2, 'LineWidth', lw);
yline(z_ref, 'k:', 'LineWidth', 1.0);
xlim(x_zoom);                           % strict zoom window
ylim(y_zoom);
grid on;
set(inset, 'FontSize', 7, 'Box', 'on', 'XMinorGrid', 'on');
title('Zoom [2–2.5 s]', 'FontSize', 7);

% --- Restore main axes size ---
set(ax1, 'Position', ax1_pos);
% --- Subplot 2: Lateral position (y) ---
%{
subplot(2,1,2);
plot(simOut1.tout, simOut1.y2_meas(:,1), '-',  'Color', color1, 'LineWidth', lw); hold on;
plot(simOut2.tout, simOut2.y2_meas(:,1), '--', 'Color', color2, 'LineWidth', lw);
yline(y_ref, 'k:', 'LineWidth', 1.2);
grid on;
ylabel('y [m]');
title('Lateral position');
legend([labels, {'Reference'}], 'Location', 'best');
%}

% --- Subplot 3: Longitudinal position (x) ---
%{
plot(simOut1.tout, simOut1.y3_meas(:,1), '-',  'Color', color1, 'LineWidth', lw); hold on;
plot(simOut2.tout, simOut2.y3_meas(:,1), '-', 'Color', color2, 'LineWidth', lw);
yline(x_ref, 'k:', 'LineWidth', 1.2);
grid on;
ylabel('x [m]');
title('Longitudinal position');
legend([labels, {'Reference'}], 'Location', 'best');
%}
% --- Subplot 4: Yaw (phi) ---
%{
subplot(2,1,2);
plot(simOut1.tout, simOut1.y4_meas(:,1), '-',  'Color', color1, 'LineWidth', lw); hold on;
plot(simOut2.tout, simOut2.y4_meas(:,1), '--', 'Color', color2, 'LineWidth', lw);
yline(phi_ref, 'k:', 'LineWidth', 1.2);
grid on;
ylabel('\phi [rad]');
xlabel('Time [s]');
title('Yaw');
legend([labels, {'Reference'}], 'Location', 'best');

%sgtitle('Controller Comparison: LQR vs MPC', 'FontSize', 14, 'FontWeight', 'bold');

disp('Comparison simulation complete.');

%% ---- Q/R sweep study ----
%}
disp('LQR weight study complete.');