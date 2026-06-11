%% Q8_phase2
% 
%
% Uses the SAME poles as the linear script for direct comparison.
% The Regulator block in Non_Linear_model reads:
%   ki1, K1  -> vertical   (F3): states fed from fb1 (position) & fb2 (lin_v)
%   ki2, K2  -> lateral    (M1): states fed from fb1, fb2, fb3, fb4
%   ki3, K3  -> longitudinal(M2): states fed from fb1, fb2, fb3, fb4
%   ki4, K4  -> yaw        (M3): states fed from fb3 (rotation) & fb4 (ang_v)
%
% Initial conditions via workspace variables:
%   r_n0, v0, theta0, omega0  (column vectors, length 3)
%


clear all
clc
run kalman_observer.m

model_name = 'Non_Linear_model';



%% 1. Parameters
drone_model_parameters
        
%% 2. State-space matrices
% SS1 - Altitude:       x = [r3; v3]
A1 = [0, 1; 0, 0];
B1 = [0; 1/m];
C1 = eye(2);
D1 = zeros(2, 1);

% SS2 - Lateral-Roll:   x = [r2; th1; v2; w1]
A2 = [0, 0, 1, 0; 0, 0, 0, 1; 0, g, 0, 0; 0, 0, 0, 0];
B2 = [0; 0; 0; 1/J11];
C2 = eye(4);
D2 = zeros(4, 1);

% SS3 - Lateral-Pitch:  x = [r1; th2; v1; w2]
A3 = [0, 0, 1, 0; 0, 0, 0, 1; 0, -g, 0, 0; 0, 0, 0, 0];
B3 = [0; 0; 0; 1/J22];
C3 = eye(4);
D3 = zeros(4, 1);

% SS4 - Yaw:            x = [th3; w3]
A4 = [0, 1; 0, 0];
B4 = [0; 1/J33];
C4 = eye(2);
D4 = zeros(2, 1);


%% 3. Simulation settings
t_end = 10;

%% 4. Ackermann + prefilter (no toolbox)
function K = ackermann(A, B, poles)
    n  = size(A,1);
    Co = zeros(n,n);
    for i = 1:n
        Co(:,i) = (A^(i-1)) * B;
    end
    p_coeffs = real(poly(poles));
    pA = zeros(n,n);
    for i = 0:n
        pA = pA + p_coeffs(i+1) * A^(n-i);
    end
    en = zeros(1,n);  en(end) = 1;
    K  = en * inv(Co) * pA;  %#ok
end

function ki = prefilter(A, B, C, K)
    Acl = A - B*K;
    dcg = -C * (Acl \ B);
    ki  = 1 / dcg(1);
end

function [L, P, E] = my_lqe(A, G, C, Q, R)
    % Solves continuous filter ARE via Hamiltonian eigendecomposition.
    % Drop-in replacement for lqe() without the Control System Toolbox.
    n = size(A,1);
    H = [ A'          , -C'*(R\C) ;
         -G*Q*G'      , -A       ];
    [V, D] = eig(H);
    idx = find(real(diag(D)) < 0);
    Vs  = V(:, idx);
    V1  = Vs(1:n,     :);
    V2  = Vs(n+1:end, :);
    P   = real(V2 / V1);
    L   = P * C' / R;
    E   = eig(A - L*C);
end

%% 5. Gains

K1  = real(ackermann(A1, B1, poles1));
K2  = real(ackermann(A2, B2, poles2));
K3  = real(ackermann(A3, B3, poles3));
K4  = real(ackermann(A4, B4, poles4));

ki1 = prefilter(A1, B1, C1(1,:), K1);
ki2 = prefilter(A2, B2, C2(1,:), K2);
ki3 = prefilter(A3, B3, C3(1,:), K3);
ki4 = prefilter(A4, B4, C4(1,:), K4);

fprintf('Closed-loop eigenvalues (designed on linear model):\n');
fprintf('  SS1 (altitude)      : '); disp(real(eig(A1-B1*K1)).');
fprintf('  SS2 (lateral-roll)  : '); disp(real(eig(A2-B2*K2)).');
fprintf('  SS3 (lateral-pitch) : '); disp(real(eig(A3-B3*K3)).');
fprintf('  SS4 (yaw)           : '); disp(real(eig(A4-B4*K4)).');
fprintf('Pre-filter gains: ki1=%.4f  ki2=%.4f  ki3=%.4f  ki4=%.4f\n', ...
        ki1, ki2, ki3, ki4);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 6. Reference setpoints.
x_ref   = 4;  %model doesnt work for xref>6 (all other0)
y_ref   = 0;  %model doesnt work for yref>6 (all other0)
z_ref   = 0;
phi_ref = 0;


% From Workspace blocks need u_input and ext_input
% u_input is overridden by the Regulator (Switch set to Regulator)
% but the From Workspace block still needs a valid variable
dt    = 0.01;
t_vec = (0:dt:t_end)';
N     = length(t_vec);
%x_ref = x_ref * ones(N, 1);

F3_hover = -m * g;
u_input   = [t_vec, F3_hover*ones(N,1), zeros(N,1), zeros(N,1), zeros(N,1)];
ext_input = [t_vec, zeros(N,3)];

%% 7. Initial condition sets %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Format: [r1  r2  r3   v1  v2  v3   th1   th2   th3  w1  w2  w3]
ic_sets = [0   0   0   0   0   0   0    0   0   0   0   0 ];


ic_names = { ...
    'with Kalman Bucy observer', ...
    'IC2: r_1 = 1 m (longitudinal)', ...
    'IC: r_3=0.5 m, r_1=1 m, v_2 = 2m/s, theta_1=0.1 rad, theta_2=0.1 rad, theta_3= 0.1 w1 = 0.2 rad/s'};

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
noise_on=1; %mesurement noise
prnoise_on=1; %process noise
%1->noise, 0->no noise
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%observer initial guesses
r1guess = 3;
r2guess = 0;
r3guess = 0;

th1guess = 0;
th2guess = 0;
th3guess = 0;

r1dotguess = 0;
r2dotguess = 0;
r3dotguess = 0;

th1dotguess = 0;
th2dotguess = 0;
th3dotguess = 0;

%% 8. Load model and run
%if bdIsLoaded(model_name)
 %   close_system(model_name, 0);
%end
load_system(model_name);

results = cell(size(ic_sets,1), 1);

for idx = 1:size(ic_sets,1)
    fprintf('\nRunning %s ...\n', ic_names{idx});
    ic = ic_sets(idx,:);   % should be 1x12
    if numel(ic) < 12
        error('ic for index %d has %d elements (expected 12).', idx, numel(ic));
    end
    % unpack
    r_n0   = ic(1:3)';
    v0     = ic(4:6)';
    theta0 = ic(7:9)';
    omega0 = ic(10:12)';

    try
        out = sim(model_name, t_end);
        results{idx} = out;
        fprintf('  Done.\n');
    catch ME
        fprintf('  ERROR: %s\n', ME.message);
        for k = 1:length(ME.cause)
            fprintf('    Cause %d: %s\n', k, ME.cause{k}.message);
        end
        results{idx} = [];
    end
end



%% 9. Separated plots: ONE window per state per IC
lw = 1.8;  fs = 10;  fs_t = 11;

% One distinct colour per state
c6 = {[0.00 0.45 0.70], ...   % r1  - blue
      [0.85 0.33 0.10], ...   % r2  - red
      [0.47 0.67 0.19], ...   % r3  - green
      [0.49 0.18 0.56], ...   % th1 - purple
      [0.93 0.69 0.13], ...   % th2 - orange
      [0.30 0.75 0.93]};      % th3 - cyan

slabels  = {'r_1', 'r_2', 'r_3', '\theta_1', '\theta_2', '\theta_3'};
ylabs    = {'Position [m]','Position [m]','Position [m]', ...
            'Angle [rad]', 'Angle [rad]', 'Angle [rad]'};
ref_vals = [x_ref, y_ref, z_ref, phi_ref, 0, 0];  % reference for each state

for idx = 1:size(ic_sets,1)
    out = results{idx};
    if isempty(out); continue; end
    try
        t_out = out.tout;
        Xtr = [out.position.Data,     out.orientation.Data    ];  % Nx6 true
        Xes = [out.position_hat.Data, out.orientation_hat.Data];  % Nx6 estimated
    catch ME
        warning('IC%d: %s', idx, ME.message); continue;
    end

    % Create a separate figure for each state
    for s = 1:6
        figure('Name', sprintf('IC%d - %s', idx, slabels{s}), ...
               'NumberTitle','off','Color','white', ...
               'Position',[40+50*s, 40+30*idx, 800, 500]);
        hold on;
        % Reference line
        yline(ref_vals(s), ':', 'Color',[0.5 0.5 0.5], 'LineWidth',1.2, ...
              'DisplayName','ref');
        % True state
        plot(t_out, Xtr(:,s), '-',  'Color',c6{s}, 'LineWidth',lw, ...
             'DisplayName',[slabels{s} ' (true)']);
        % Estimated state
        plot(t_out, Xes(:,s), '--', 'Color',c6{s}*0.65, 'LineWidth',lw, ...
             'DisplayName',[slabels{s} ' (est)']);
        hold off;
        
        xlabel('Time [s]',  'FontSize',fs);
        ylabel(ylabs{s},    'FontSize',fs);
        title(sprintf('Nonlinear Model | %s | %s', ic_names{idx}, slabels{s}), ...
              'FontSize',fs_t, 'FontWeight','bold', 'Color',[0.15 0.15 0.15]);
        legend('Location','best','FontSize',fs-1,'Box','off');
        grid on; grid minor;
        set(gca,'Color','white','GridAlpha',0.15,'MinorGridAlpha',0.05, ...
                'Box','on','FontSize',fs);
    end
end



%% 10 & 11. Sensitivity Sweeps for r1, r2, r3, th3 (Separate Windows)
Q0_1_base = Q0_1; Q0_2_base = Q0_2; Q0_3_base = Q0_3; Q0_4_base = Q0_4;
R0_1_base = R0_1; R0_2_base = R0_2; R0_3_base = R0_3; R0_4_base = R0_4;

scan_mults = [0.01, 0.1, 1, 10, 100];
n_scans    = length(scan_mults);
cmap       = lines(n_scans);

% Pre-allocate cell arrays to store the results of the sweeps
out_Q = cell(n_scans, 1);
out_R = cell(n_scans, 1);

fprintf('\n=== Running Q0 sensitivity sweeps ===\n');
for qi = 1:n_scans
    qm = scan_mults(qi);
    [L1,~,~] = my_lqe(A1, eye(2), C1, qm*Q0_1_base, R0_1_base);
    [L2,~,~] = my_lqe(A2, eye(4), C2, qm*Q0_2_base, R0_2_base);
    [L3,~,~] = my_lqe(A3, eye(4), C3, qm*Q0_3_base, R0_3_base);
    [L4,~,~] = my_lqe(A4, eye(2), C4, qm*Q0_4_base, R0_4_base);

    simIn = Simulink.SimulationInput(model_name);
    simIn = simIn.setVariable('L1', L1);
    simIn = simIn.setVariable('L2', L2);
    simIn = simIn.setVariable('L3', L3);
    simIn = simIn.setVariable('L4', L4);
    simIn = simIn.setModelParameter('StopTime', num2str(t_end));
    out_Q{qi} = sim(simIn); 
end

fprintf('=== Running R0 sensitivity sweeps ===\n');
for ri = 1:n_scans
    rm = scan_mults(ri);
    [L1,~,~] = my_lqe(A1, eye(2), C1, Q0_1_base, rm*R0_1_base);
    [L2,~,~] = my_lqe(A2, eye(4), C2, Q0_2_base, rm*R0_2_base);
    [L3,~,~] = my_lqe(A3, eye(4), C3, Q0_3_base, rm*R0_3_base);
    [L4,~,~] = my_lqe(A4, eye(2), C4, Q0_4_base, rm*R0_4_base);

    simIn = Simulink.SimulationInput(model_name);
    simIn = simIn.setVariable('L1', L1);
    simIn = simIn.setVariable('L2', L2);
    simIn = simIn.setVariable('L3', L3);
    simIn = simIn.setVariable('L4', L4);
    simIn = simIn.setModelParameter('StopTime', num2str(t_end));
    out_R{ri} = sim(simIn); 
end

% Define which states to plot (1=r1, 2=r2, 3=r3, 6=th3)
sweep_states = [1, 2, 3, 6]; 
sw_labels    = {'r_1', 'r_2', 'r_3', '\theta_3'};
sw_refs      = [x_ref, y_ref, z_ref, 0];
sw_ylabs     = {'Position [m]', 'Position [m]', 'Position [m]', 'Angle [rad]'};

fprintf('\n=== Generating Separated Sweep Plots ===\n');
for k = 1:length(sweep_states)
    s_idx = sweep_states(k);
    
    % ---------------- Q0 Sweep Figure ----------------
    figure('Name', sprintf('%s Q0 Sensitivity', sw_labels{k}), ...
           'NumberTitle', 'off', 'Color', 'white', ...
           'Position', [100+k*40, 100+k*40, 800, 500]);
    hold on;
    yline(sw_refs(k), ':k', 'LineWidth', 1.4, 'DisplayName', 'ref');
    
    for qi = 1:n_scans
        t_s = out_Q{qi}.tout;
        % Extract the correct state array (position vs orientation)
        if s_idx <= 3
            val_t = out_Q{qi}.position.Data(:, s_idx);
            val_e = out_Q{qi}.position_hat.Data(:, s_idx);
        else
            val_t = out_Q{qi}.orientation.Data(:, s_idx-3);
            val_e = out_Q{qi}.orientation_hat.Data(:, s_idx-3);
        end
        
        % Plot true and estimated, overlaid
        plot(t_s, val_t, '-',  'Color', cmap(qi,:), 'LineWidth', 1.5, ...
             'DisplayName', sprintf('True (Q_0 \\times %g)', scan_mults(qi)));
        plot(t_s, val_e, '--', 'Color', cmap(qi,:)*0.6, 'LineWidth', 1.5, ...
             'DisplayName', sprintf('Est (Q_0 \\times %g)', scan_mults(qi)));
    end
    hold off;
    title(sprintf('%s: Q_0 Multiplier Sweep (R_0 fixed)', sw_labels{k}), 'FontSize', 12, 'FontWeight', 'bold');
    xlabel('Time [s]'); ylabel(sw_ylabs{k});
    legend('Location', 'best', 'NumColumns', 2, 'FontSize', 8);
    grid on; grid minor;
    
    % ---------------- R0 Sweep Figure ----------------
    figure('Name', sprintf('%s R0 Sensitivity', sw_labels{k}), ...
           'NumberTitle', 'off', 'Color', 'white', ...
           'Position', [120+k*40, 120+k*40, 800, 500]);
    hold on;
    yline(sw_refs(k), ':k', 'LineWidth', 1.4, 'DisplayName', 'ref');
    
    for ri = 1:n_scans
        t_s = out_R{ri}.tout;
        if s_idx <= 3
            val_t = out_R{ri}.position.Data(:, s_idx);
            val_e = out_R{ri}.position_hat.Data(:, s_idx);
        else
            val_t = out_R{ri}.orientation.Data(:, s_idx-3);
            val_e = out_R{ri}.orientation_hat.Data(:, s_idx-3);
        end
        
        plot(t_s, val_t, '-',  'Color', cmap(ri,:), 'LineWidth', 1.5, ...
             'DisplayName', sprintf('True (R_0 \\times %g)', scan_mults(ri)));
        plot(t_s, val_e, '--', 'Color', cmap(ri,:)*0.6, 'LineWidth', 1.5, ...
             'DisplayName', sprintf('Est (R_0 \\times %g)', scan_mults(ri)));
    end
    hold off;
    title(sprintf('%s: R_0 Multiplier Sweep (Q_0 fixed)', sw_labels{k}), 'FontSize', 12, 'FontWeight', 'bold');
    xlabel('Time [s]'); ylabel(sw_ylabs{k});
    legend('Location', 'best', 'NumColumns', 2, 'FontSize', 8);
    grid on; grid minor;
end