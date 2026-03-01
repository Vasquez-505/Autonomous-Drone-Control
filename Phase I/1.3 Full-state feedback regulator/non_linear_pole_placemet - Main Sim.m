%% Q14_pole_placement_nonlinear.m
% Q14 - Full-state feedback pole placement validated on the NONLINEAR Simulink model
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
% NOTE: Change 'Non_Linear_model' to your actual .slx filename


clear all
clc

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
t_end = 6;

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

%% 6. Reference setpoints
x_ref   = 2;
y_ref   = 1;
z_ref   = 4;
phi_ref = 0.5;

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

%% 7. Initial condition sets
% Format: [r1  r2  r3   v1  v2  v3   th1   th2   th3  w1  w2  w3]
ic_sets = [
    0    0   0.5   0   0   0    0     0     0    0   0   0;  % IC1: r3=0.5m
    1.0  0   0     0   0   0    0     0     0    0   0   0;  % IC2: r1=1m
    1.0  0   0.5   0   0   2    0     0.1   0.1    0.2   0   0;  % IC3: multi
];

ic_names = { ...
    'IC: r_3 = 0.5 m (altitude)', ...
    'IC2: r_1 = 1 m (longitudinal)', ...
    'IC: r_3=0.5 m, r_1=1 m, v_2 = 2m/s, theta_1=0.1 rad, theta_2=0.1 rad, theta_3= 0.1 w1 = 0.2 rad/s'};

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

%% 9. Plot results (same style as linear script)
c_x   = [0.00 0.45 0.70];
c_y   = [0.85 0.33 0.10];
c_z   = [0.47 0.67 0.19];
lw = 1.8;  fs = 10;  fs_t = 11;

for idx = 1:size(ic_sets,1)
    out = results{idx};
    out_n_linear = out; 
 %   fprintf('Available fields in out:\n');
%disp(fieldnames(out));
    if isempty(out); continue; end

    try
        t_out = out.tout;
        r1 = out.position.Data(:,1);
        r2 = out.position.Data(:,2);
        r3 = out.position.Data(:,3);
        v1 = out.lin_v.Data(:,1);
        v2 = out.lin_v.Data(:,2);
        v3 = out.lin_v.Data(:,3);
        th1 = out.orientation.Data(:,1);
        th2 = out.orientation.Data(:,2);
        th3 = out.orientation.Data(:,3);
        w1  = out.ang_v.Data(:,1);
        w2  = out.ang_v.Data(:,2);
        w3  = out.ang_v.Data(:,3);
    catch ME
        warning('Could not extract states for IC%d: %s', idx, ME.message);
        continue;
    end

    figure('Name', sprintf('Non Linear'), ...
           'NumberTitle','off','Color','white','Position',[80+idx*25 80 900 800]);
    sgtitle(sprintf('Nonlinear Model  |  %s', ic_names{idx}), ...
            'FontSize',12,'FontWeight','bold','Color',[0.15 0.15 0.15]);

    % Position
    subplot(4,1,1); hold on;
    plot(t_out, r1, 'Color',c_x, 'LineWidth',lw, 'DisplayName','r_1 (x)');
    plot(t_out, r2, 'Color',c_y, 'LineWidth',lw, 'DisplayName','r_2 (y)');
    plot(t_out, r3, 'Color',c_z, 'LineWidth',lw, 'DisplayName','r_3 (z)');
    hold off;
    ylabel('Position [m]','FontSize',fs);
    xlabel('Time[s]','FontSize',fs);
    title('Position','FontSize',fs_t,'FontWeight','bold');
    legend('Location','eastoutside','FontSize',fs-1,'Box','off');
    grid on; grid minor;
    set(gca,'Color','white','GridAlpha',0.15,'MinorGridAlpha',0.05,'Box','on','FontSize',fs);

    % Linear velocity
    subplot(4,1,2); hold on;
    plot(t_out, v1, 'Color',c_x, 'LineWidth',lw, 'DisplayName','v_1');
    plot(t_out, v2, 'Color',c_y, 'LineWidth',lw, 'DisplayName','v_2');
    plot(t_out, v3, 'Color',c_z, 'LineWidth',lw, 'DisplayName','v_3');
    hold off;
    ylabel('Velocity (m/s)','FontSize',fs);
    xlabel('Time [s]', 'FontSize',fs);
    title('Linear velocity','FontSize',fs_t,'FontWeight','bold');
    legend('Location','eastoutside','FontSize',fs-1,'Box','off');
    grid on; grid minor;
    set(gca,'Color','white','GridAlpha',0.15,'MinorGridAlpha',0.05,'Box','on','FontSize',fs);

    % Orientation
    subplot(4,1,3); hold on;
    plot(t_out, th1, 'Color',c_x, 'LineWidth',lw, 'DisplayName','\theta_1');
    plot(t_out, th2, 'Color',c_y, 'LineWidth',lw, 'DisplayName','\theta_2');
    plot(t_out, th3, 'Color',c_z, 'LineWidth',lw, 'DisplayName','\theta_3');
    hold off;
    ylabel('Angle (rad)','FontSize',fs);
    xlabel('Time [s]', 'FontSize',fs);
    title('Orientation','FontSize',fs_t,'FontWeight','bold');
    legend('Location','eastoutside','FontSize',fs-1,'Box','off');
    grid on; grid minor;
    set(gca,'Color','white','GridAlpha',0.15,'MinorGridAlpha',0.05,'Box','on','FontSize',fs);

    % Angular velocity
    subplot(4,1,4); hold on;
    plot(t_out, w1, 'Color',c_x, 'LineWidth',lw, 'DisplayName','\omega_1');
    plot(t_out, w2, 'Color',c_y, 'LineWidth',lw, 'DisplayName','\omega_2');
    plot(t_out, w3, 'Color',c_z, 'LineWidth',lw, 'DisplayName','\omega_3');
    hold off;
    xlabel('Time [s]','FontSize',fs);
    ylabel('Angular velocity (rad/s)','FontSize',fs);
    title('Angular velocity','FontSize',fs_t,'FontWeight','bold');
    legend('Location','eastoutside','FontSize',fs-1,'Box','off');
    grid on; grid minor;
    set(gca,'Color','white','GridAlpha',0.15,'MinorGridAlpha',0.05,'Box','on','FontSize',fs);
end

save('n_linear_data.mat')
fprintf('\nQ14 nonlinear complete.\n');