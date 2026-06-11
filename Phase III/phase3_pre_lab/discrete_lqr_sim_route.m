%% discrete_lqr_sim.m
% Phase 3.1 – Discrete-Time LQR Servo Controller
%
% Only the REGULATOR is redesigned in discrete time (ZOH, Ts = 5 ms).
% The Kalman-Bucy observer is UNCHANGED from Phase II (continuous time).
%
% SUBSYSTEM CONVENTION (matches Phase I & II):
%   SS1 – Altitude:       x = [r3;  v3]
%   SS2 – Lateral-Roll:   x = [r2;  th1; v2;  w1]
%   SS3 – Lateral-Pitch:  x = [r1;  th2; v1;  w2]
%   SS4 – Yaw:            x = [th3; w3]
%
% DISCRETE SERVO STRUCTURE:
%   Each subsystem is augmented with one integrator state xi:
%       xi[k+1] = xi[k] + Ts*(r – Cout*x[k])
%   Augmented state:  xa = [x; xi]
%   Augmented plant:  Aa = [Ad, 0; -Ts*Cout, 1],  Ba = [Bd; 0]
%   Control law:      u[k] = -Kd*x_hat[k] - Kid*xi[k]
%   (No separate pre-filter needed – integral action ensures zero SS error)
%
% SIMULINK MODIFICATIONS REQUIRED (minimal):
%   1. Observer blocks: NO CHANGE – remain continuous with L1..L4 from Phase II.
%   2. Regulator block: replace continuous law (u = -K*xhat + ki*r) with
%      discrete servo law: u[k] = -Kd*xhat[k] - Kid*xi[k],
%      where xi is updated via a Unit Delay block at Ts = 0.005.
%   3. Add a ZOH block (Ts = 0.005) at each control output (F3, M1, M2, M3).

close all; clear all; clc;

model_name = 'Non_Linear_model';

%% ── 1. Load drone parameters and continuous Kalman-Bucy gains (Phase II) ─
% kalman_observer.m computes L1..L4 and the continuous observer matrices
% Ao1..4, Bo1..4, Co1..4, Do1..4 exactly as in Phase II.
run kalman_observer.m
clc

Ts = 0.005;    % ZOH sampling period [s]

%% ── 2. Continuous SS matrices ────────────────────────────────────────────
A1 = [0, 1; 0, 0];
B1 = [0; 1/m];
C1 = eye(2);

A2 = [0, 0, 1, 0;  0, 0, 0, 1;  0,  g, 0, 0;  0, 0, 0, 0];
B2 = [0; 0; 0; 1/J11];
C2 = eye(4);

A3 = [0, 0, 1, 0;  0, 0, 0, 1;  0, -g, 0, 0;  0, 0, 0, 0];
B3 = [0; 0; 0; 1/J22];
C3 = eye(4);

A4 = [0, 1; 0, 0];
B4 = [0; 1/J33];
C4 = eye(2);

%% ── 3. ZOH Discretisation of the plant matrices ─────────────────────────
% Used only to design the discrete regulator gains.
% The observer and plant themselves remain continuous in Simulink.
[Ad1, Bd1] = zoh_disc(A1, B1, Ts);
[Ad2, Bd2] = zoh_disc(A2, B2, Ts);
[Ad3, Bd3] = zoh_disc(A3, B3, Ts);
[Ad4, Bd4] = zoh_disc(A4, B4, Ts);

fprintf('=== ZOH Discretised – |eig(Ad)| (all must be inside unit disc) ===\n');
fprintf('|eig(Ad1)| = '); fprintf('%.8f  ', abs(eig(Ad1)).'); fprintf('\n');
fprintf('|eig(Ad2)| = '); fprintf('%.8f  ', abs(eig(Ad2)).'); fprintf('\n');
fprintf('|eig(Ad3)| = '); fprintf('%.8f  ', abs(eig(Ad3)).'); fprintf('\n');
fprintf('|eig(Ad4)| = '); fprintf('%.8f  ', abs(eig(Ad4)).'); fprintf('\n\n');

%% ── 4. Discrete LQR Servo Gains  (tune ONE parameter: rho) ──────────────
% Bryson's rule: Q_ii = 1 / max_state_deviation_i^2
%                R    = rho  (same for all subsystems – Q already normalises)
%
%   rho >> 1  →  gentler, slower (penalises control effort more)
%   rho << 1  →  more aggressive, faster (penalises state error more)
%
%   Start at rho = 1. Check printed |z| poles: target all between 0.92–0.99.
%   If any |z| < 0.85 → increase rho. If response too slow → decrease rho.

rho = 0.1; 

% ── Maximum acceptable deviation per state (physical limits) ─────────────
% SS1 – Altitude       [r3,    v3,    xi_r3]
r3_max  = 2;     v3_max  = 2;     xi1_max = 1;

% SS2 – Lateral-Roll   [r2,    th1,   v2,    w1,    xi_r2]
r2_max  = 1;     th1_max = 0.2;   v2_max  = 1;   w1_max = 1;   xi2_max = 0.4;

% SS3 – Lateral-Pitch  [r1,    th2,   v1,    w2,    xi_r1]
r1_max  = 1;     th2_max = 0.2;   v1_max  = 1;   w2_max = 1;   xi3_max = 0.4;

% SS4 – Yaw            [th3,   w3,    xi_th3]
%th3_max = 0.1;  w3_max  = 10;     xi4_max = 0.2;
th3_max = pi/4;  w3_max  = 1;     xi4_max = pi/4;

% ── Bryson Q matrices (automatically normalised) ──────────────────────────
Q_lqr1 = diag([1/r3_max^2,  1/v3_max^2,  1/xi1_max^2]);
Q_lqr2 = diag([1/r2_max^2,  1/th1_max^2, 1/v2_max^2,  1/w1_max^2,  1/xi2_max^2]);
Q_lqr3 = diag([1/r1_max^2,  1/th2_max^2, 1/v1_max^2,  1/w2_max^2,  1/xi3_max^2]);
Q_lqr4 = diag([1/th3_max^2, 1/w3_max^2,  1/xi4_max^2]);

% ── R scaled by rho (same across subsystems – Q normalisation handles the rest)
R_lqr1 = rho;
R_lqr2 = rho;
R_lqr3 = rho;
R_lqr4 = rho;

[Kd1, Kid1] = dlqr_servo(Ad1, Bd1, C1(1,:), Q_lqr1, R_lqr1, Ts);
[Kd2, Kid2] = dlqr_servo(Ad2, Bd2, C2(1,:), Q_lqr2, R_lqr2, Ts);
[Kd3, Kid3] = dlqr_servo(Ad3, Bd3, C3(1,:), Q_lqr3, R_lqr3, Ts);
[Kd4, Kid4] = dlqr_servo(Ad4, Bd4, C4(1,:), Q_lqr4, R_lqr4, Ts);

fprintf('=== Discrete LQR Servo Gains ===\n');
fprintf('Kd1  = ['); fprintf('%10.4f', Kd1);  fprintf('],  Kid1 = %10.4f\n', Kid1);
fprintf('Kd2  = ['); fprintf('%10.4f', Kd2);  fprintf('],  Kid2 = %10.4f\n', Kid2);
fprintf('Kd3  = ['); fprintf('%10.4f', Kd3);  fprintf('],  Kid3 = %10.4f\n', Kid3);
fprintf('Kd4  = ['); fprintf('%10.4f', Kd4);  fprintf('],  Kid4 = %10.4f\n\n', Kid4);

fprintf('Closed-loop poles of augmented systems (all |z| < 1 required):\n');
for ss = 1:4
    switch ss
        case 1, Aa=[Ad1,zeros(2,1);-Ts*C1(1,:),1]; Ba=[Bd1;0]; Ka=[Kd1,Kid1];
        case 2, Aa=[Ad2,zeros(4,1);-Ts*C2(1,:),1]; Ba=[Bd2;0]; Ka=[Kd2,Kid2];
        case 3, Aa=[Ad3,zeros(4,1);-Ts*C3(1,:),1]; Ba=[Bd3;0]; Ka=[Kd3,Kid3];
        case 4, Aa=[Ad4,zeros(2,1);-Ts*C4(1,:),1]; Ba=[Bd4;0]; Ka=[Kd4,Kid4];
    end
    ev = eig(Aa - Ba*Ka);
    fprintf('  SS%d |z| = ', ss); fprintf('%.6f  ', abs(ev).'); fprintf('\n');
end

%% ── 5. Assign gains to workspace ─────────────────────────────────────────
% Same variable names the Simulink Regulator block already uses.
K1 = Kd1;   K2 = Kd2;   K3 = Kd3;   K4 = Kd4;
ki1 = 2*Kid1; ki2 = 2*Kid2; ki3 = Kid3; ki4 = Kid4;
% L1..L4 and continuous observer matrices are already in the workspace
% from the kalman_observer.m call above – no change needed there.

%% ── 6. Reference setpoints (Figure-8 Trajectory) ──────────────────────────
t_end = 30;                 % Increased time to see the full pattern
t_ref = (0 : Ts : t_end)';  % Time vector matching controller Ts

% --- Trajectory Parameters ---
A_fig = 2;                  % Width of the 8 (meters)
B_fig = 1.5;                % Height of the 8 (meters)
freq  = 0.1;                % Speed of the pattern (Hz)
omega = 2 * pi * freq;      
t_start_8 = 5;              % Wait 5 seconds to finish climbing first

% Initialize arrays
x_ref_val = zeros(size(t_ref));
y_ref_val = zeros(size(t_ref));
z_ref_val = zeros(size(t_ref));
phi_ref_val = zeros(size(t_ref));

for i = 1:length(t_ref)
    t = t_ref(i);
    
    % 1. Altitude (r3): Smooth climb to 5m in first 4 seconds
    z_ref_val(i) = min(5, 1.25 * t); 
    
    % 2. Figure 8 Pattern (r1 and r2): Starts after 5 seconds
    if t > t_start_8
        tau = t - t_start_8; % Time relative to pattern start
        x_ref_val(i) = A_fig * sin(omega * tau);
        y_ref_val(i) = B_fig * sin(2 * omega * tau);
    else
        x_ref_val(i) = 0;
        y_ref_val(i) = 0;
    end
end

% Join into [Time, Data] matrices for the "From Workspace" blocks
x_ref_data = [t_ref, x_ref_val]; 
y_ref_data = [t_ref, y_ref_val]; 
z_ref_data = [t_ref, z_ref_val]; 
phi_ref_data = [t_ref, phi_ref_val];

% Setup simulation time variables
t_vec = (0 : 0.001 : t_end)';
N     = length(t_vec);
u_input   = [t_vec, (-m*g)*ones(N,1), zeros(N,3)];
ext_input = [t_vec, zeros(N,3)];


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

noise_on   = 1;
prnoise_on = 1;

% Observer initial guesses (same as Phase II)
r1guess = 0;  r2guess = 0;  r3guess = 0;
th1guess = 0; th2guess = 0; th3guess = 0;
r1dotguess = 0; r2dotguess = 0; r3dotguess = 0;
th1dotguess = 0; th2dotguess = 0; th3dotguess = 0;

ic     = [0 0 0  0 0 0  0 0 0  0 0 0];
r_n0   = ic(1:3)';
v0     = ic(4:6)';
theta0 = ic(7:9)';
omega0 = ic(10:12)';

%% ── 7. Run simulation ─────────────────────────────────────────────────────
% load_system(model_name);
% 
% try
%     out = sim(model_name, t_end);
%     fprintf('\nSimulation complete.\n');
% catch ME
%     fprintf('Simulation error: %s\n', ME.message);
%     for k = 1:length(ME.cause)
%         fprintf('  Cause %d: %s\n', k, ME.cause{k}.message);
%     end
%     return
% end
%% ── 7. Run simulation ─────────────────────────────────────────────────────
load_system(model_name);

% Fix: force fixed-step solver for mixed continuous-discrete model
set_param(model_name, 'SolverType',    'Fixed-step');
set_param(model_name, 'Solver',        'ode4');
set_param(model_name, 'FixedStep',     '0.0005');

try
    out = sim(model_name, t_end);


    fprintf('\nSimulation complete.\n');
catch ME
    fprintf('Simulation error: %s\n', ME.message);
    for k = 1:length(ME.cause)
        fprintf('  Cause %d: %s\n', k, ME.cause{k}.message);
    end
    return
end


%% ── 8. Plots (3D Trajectory + 2D States) ──────────────────────────────────
lw = 1.8;  fs = 10;  fs_t = 11;
c6 = {[0.00 0.45 0.70], [0.85 0.33 0.10], [0.47 0.67 0.19], ...
      [0.49 0.18 0.56], [0.93 0.69 0.13], [0.30 0.75 0.93]};
slabels  = {'r_1', 'r_2', 'r_3', '\theta_1', '\theta_2', '\theta_3'};
ylabs    = {'Position [m]','Position [m]','Position [m]', ...
            'Angle [rad]', 'Angle [rad]', 'Angle [rad]'};

try
    t_out = out.tout;
    % Extract Position (x=r1, y=r2, z=r3)
    % Note: Assumes position signal order [r1, r2, r3]
    Xtr = [out.position.Data, out.orientation.Data];
    
    len_t   = length(t_out);
    len_tr  = size(Xtr, 1);
    N_samples = min([len_t, len_tr]);
    
    t_plot   = t_out(1:N_samples);
    Xtr_plot = Xtr(1:N_samples, :);

    % ── 8.1. NEW: 3D Path Visualization ──
    figure('Name', 'Drone 3D Trajectory', 'Color', 'white', 'Position', [100, 100, 900, 700]);
    hold on;
    
    % Plot Reference Path (Grey dashed)
    plot3(x_ref_val, y_ref_val, z_ref_val, '--', 'Color', [0.6 0.6 0.6], ...
          'LineWidth', 1.2, 'DisplayName', 'Reference Path');
    
    % Plot Actual Path (Colored based on altitude)
    % Using scatter3 or plot3. plot3 is cleaner for routes.
    plot3(Xtr_plot(:,1), Xtr_plot(:,2), Xtr_plot(:,3), 'Color', c6{1}, ...
          'LineWidth', 2.5, 'DisplayName', 'Drone Path (True)');
    
    % Add Start and End markers
    plot3(Xtr_plot(1,1), Xtr_plot(1,2), Xtr_plot(1,3), 'ko', 'MarkerFaceColor', 'g', 'DisplayName', 'Start');
    plot3(Xtr_plot(end,1), Xtr_plot(end,2), Xtr_plot(end,3), 'ks', 'MarkerFaceColor', 'r', 'DisplayName', 'End');

    grid on; grid minor; axis equal;
    xlabel('X Position (r_1) [m]', 'FontSize', fs);
    ylabel('Y Position (r_2) [m]', 'FontSize', fs);
    zlabel('Altitude (r_3) [m]', 'FontSize', fs);
    title('3D Figure-8 Flight Route', 'FontSize', fs_t, 'FontWeight', 'bold');
    legend('Location', 'northeast');
    view(45, 30); % Set a good 3D perspective
    hold off;

    % ── 8.2. Individual State Plots (Time Domain) ──
    % Pre-calculate reference arrays for the loop
    ref_signals = {x_ref_val, y_ref_val, z_ref_val, zeros(size(t_ref)), zeros(size(t_ref)), zeros(size(t_ref))};

    for s = 1:6
        figure('Name', sprintf('Discrete LQR – %s', slabels{s}), ...
               'NumberTitle','off', 'Color','white', ...
               'Position', [40+30*s, 40+20*s, 600, 400]);
        hold on;
        
        % Dynamic reference for the Figure-8 states
        t_ref_plot = t_ref(1:min(length(t_ref), N_samples));
        ref_plot   = ref_signals{s}(1:min(length(ref_signals{s}), N_samples));
        
        plot(t_ref_plot, ref_plot, ':', 'Color', [0.5 0.5 0.5], 'LineWidth', 1.5, 'DisplayName', 'Reference');
        plot(t_plot, Xtr_plot(:,s), '-', 'Color', c6{s}, 'LineWidth', lw, 'DisplayName', 'True');
             
        xlabel('Time [s]', 'FontSize', fs);
        ylabel(ylabs{s}, 'FontSize', fs);
        title(sprintf('%s Response', slabels{s}), 'FontSize', fs_t);
        legend('Location', 'best');
        grid on;
    end
    
    fprintf('3D Trajectory and %d state plots generated.\n', length(slabels));
catch ME
    fprintf('\nPlotting failed: %s\n', ME.message);
end


