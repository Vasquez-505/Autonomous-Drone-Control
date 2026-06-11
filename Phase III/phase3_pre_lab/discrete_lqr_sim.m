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

%% ── 6. Reference setpoints and simulation setup ──────────────────────────
x_ref   = 1;
y_ref   = 2;
z_ref   = 4;
phi_ref = 0.5;
t_end = 20;
%% ── 6. Reference setpoints (Workspace Format) ──────────────────────────
t_ref = (0 : Ts : t_end)';  % Use your Ts (0.005) for consistency

% Define Y-position reference (r2)
y_ref_val = zeros(size(t_ref)); 
y_ref_val(t_ref >= 2.0) = 3;    % Step to 3m after 2 seconds

% Combine into [Time, Data] matrix
y_ref_data = [t_ref, y_ref_val];

% Optional: Set others if you want them to change over time
x_ref_data = [t_ref, zeros(size(t_ref))]; % Stay at 0
z_ref_data = [t_ref, 5 * ones(size(t_ref))]; % Stay at 5


t_end = 20;
dt    = 0.001;
t_vec = (0 : dt : t_end)';
N     = length(t_vec);

F3_hover  = -m * g;
u_input   = [t_vec, F3_hover*ones(N,1), zeros(N,3)];
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


%% ── 8. Plots ─────────────────────────────────────────────────────────────
lw = 1.8;  fs = 10;  fs_t = 11;
c6 = {[0.00 0.45 0.70], [0.85 0.33 0.10], [0.47 0.67 0.19], ...
      [0.49 0.18 0.56], [0.93 0.69 0.13], [0.30 0.75 0.93]};
slabels  = {'r_1', 'r_2', 'r_3', '\theta_1', '\theta_2', '\theta_3'};
ylabs    = {'Position [m]','Position [m]','Position [m]', ...
            'Angle [rad]', 'Angle [rad]', 'Angle [rad]'};
ref_vals = [x_ref, y_ref, z_ref, phi_ref, 0, 0];

try
    t_out = out.tout;
    Xtr = [out.position.Data, out.orientation.Data];
    
    % Only synchronize time and True state (Estimated removed)
    len_t   = length(t_out);
    len_tr  = size(Xtr, 1);
    N_samples = min([len_t, len_tr]);
    
    t_plot   = t_out(1:N_samples);
    Xtr_plot = Xtr(1:N_samples, :);

    for s = 1:6
        figure('Name', sprintf('Discrete LQR – %s', slabels{s}), ...
               'NumberTitle','off', 'Color','white', ...
               'Position', [40+50*s, 40+30*s, 800, 500]);
        hold on;
        
        % 1. Reference Line
        yline(ref_vals(s), ':', 'Color',[0.5 0.5 0.5], 'LineWidth',1.2, ...
              'DisplayName','Reference');
          
        % 2. True State (Solid Line)
        plot(t_plot, Xtr_plot(:,s), '-',  'Color',c6{s}, 'LineWidth',lw, ...
             'DisplayName', [slabels{s} ' (True)']);
             
        % REMOVED: Estimated State plotting block
             
        hold off;
        
        % Formatting
        xlabel('Time [s]', 'FontSize',fs);
        ylabel(ylabs{s},   'FontSize',fs);
        title(sprintf('Discrete LQR Servo (T_s = 5 ms) | %s Response', slabels{s}), ...
              'FontSize',fs_t, 'FontWeight','bold', 'Color',[0.15 0.15 0.15]);
        
        legend('Location','best','FontSize',fs-1,'Box','off');
        grid on; grid minor;
        set(gca, 'Color','white', 'GridAlpha',0.15, 'MinorGridAlpha',0.05, ...
                 'Box','on', 'FontSize',fs);
    end
    fprintf('All %d plots (True states only) generated successfully.\n', length(slabels));
catch ME
    fprintf('\nPlotting failed: %s\n', ME.message);
end

% %% ═══════════════════════════════════════════════════════════════════════════
% %% LOCAL FUNCTIONS
% %% ═══════════════════════════════════════════════════════════════════════════
% 
% function [Ad, Bd] = zoh_disc(A, B, Ts)
% % ZOH discretisation via matrix exponential.
% % Exact for any A, including nilpotent (no matrix inversion needed).
%     n  = size(A,1);
%     m  = size(B,2);
%     M  = expm([A, B; zeros(m, n+m)] * Ts);
%     Ad = M(1:n,    1:n);
%     Bd = M(1:n, n+1:end);
% end
% 
% function [Kd, Kid] = dlqr_servo(Ad, Bd, Cout, Q, R, Ts)
% % Discrete LQR servo: augments plant with one integrator, solves DARE.
% %   Augmented:  Aa = [Ad, 0; -Ts*Cout, 1],  Ba = [Bd; 0]
% %   Control:    u[k] = -Kd*x_hat[k] - Kid*xi[k]
%     n  = size(Ad,1);
%     Aa = [Ad,        zeros(n,1);
%           -Ts*Cout,  1         ];
%     Ba = [Bd; 0];
%     P  = my_dare(Aaok, Ba, Q, R);
%     Ka = (R + Ba'*P*Ba) \ (Ba'*P*Aa);
%     Kd  = Ka(1:n);
%     Kid = Ka(n+1:end);
% end
% 
% function P = my_dare(A, B, Q, R)
% % Discrete Algebraic Riccati Equation via value iteration (no toolbox).
%     P = Q;
%     for i = 1:10000
%         K  = (R + B'*P*B) \ (B'*P*A);
%         Pn = A'*P*A - A'*P*B*K + Q;
%         if norm(Pn - P, 'fro') < 1e-12 * (1 + norm(P,'fro'))
%             break
%         end
%         P = Pn;
%     end
%     P = Pn;
% end
