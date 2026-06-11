%% Q8_phase2 - Helical Ascending + Descending Trajectory
clear all
clc
run kalman_observer.m

model_name = 'Non_Linear_model';

%% 1. Parameters
drone_model_parameters

%% 2. State-space matrices
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

%% 3. Simulation settings
t_end = 60;   % long enough to complete ascent + descent

%% 4. Local functions
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
    en = zeros(1,n); en(end) = 1;
    K  = en * inv(Co) * pA;
end

function ki = prefilter(A, B, C, K)
    Acl = A - B*K;
    dcg = -C * (Acl \ B);
    ki  = 1 / dcg(1);
end

function [K, S, E] = my_lqr(A, B, Q, R)
    n = size(A,1);
    H = [ A       , -B*(R\B') ;
         -Q       , -A'      ];
    [V, D] = eig(H);
    idx = find(real(diag(D)) < 0);
    Vs  = V(:, idx);
    V1  = Vs(1:n,     :);
    V2  = Vs(n+1:end, :);
    S   = real(V2 / V1);
    K   = R \ (B' * S);
    E   = eig(A - B*K);
end

function [L, P, E] = my_lqe(A, G, C, Q, R)
    [L, P, E] = my_lqr(A', C', Q, R);
    L = L';
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

fprintf('Closed-loop eigenvalues:\n');
fprintf('  SS1 (altitude)      : '); disp(real(eig(A1-B1*K1)).');
fprintf('  SS2 (lateral-roll)  : '); disp(real(eig(A2-B2*K2)).');
fprintf('  SS3 (lateral-pitch) : '); disp(real(eig(A3-B3*K3)).');
fprintf('  SS4 (yaw)           : '); disp(real(eig(A4-B4*K4)).');
fprintf('Pre-filter gains: ki1=%.4f  ki2=%.4f  ki3=%.4f  ki4=%.4f\n', ...
        ki1, ki2, ki3, ki4);

%% 6. Figure-8 via Waypoints (constant blocks, no Simulink changes)
dt    = 0.01;
t_seg = 8;        % seconds per waypoint - enough time to settle

% Figure-8 waypoints traced around two loops
% Left loop then right loop
a = 2.5;   % x amplitude
b = 1.5;   % y amplitude

waypoints = [
%   x       y       z
    0,      0,      3;     % centre - start
    a,      b,      3;     % right loop top
    a*1.2,  0,      3;     % right tip
    a,     -b,      3;     % right loop bottom
    0,      0,      3;     % centre crossing
   -a,      b,      3;     % left loop top
   -a*1.2,  0,      3;     % left tip
   -a,     -b,      3;     % left loop bottom
    0,      0,      3;     % centre - end
];

n_wp = size(waypoints, 1);
t_end_total = n_wp * t_seg;

%% 7. Initial conditions
noise_on   = 1;
prnoise_on = 1;

r1guess = 0; r2guess = 0; r3guess = 3;
th1guess = 0; th2guess = 0; th3guess = 0;
r1dotguess = 0; r2dotguess = 0; r3dotguess = 0;
th1dotguess = 0; th2dotguess = 0; th3dotguess = 0;

load_system(model_name);

% Storage
t_all       = [];
pos_all     = [];
ori_all     = [];
pos_hat_all = [];
ori_hat_all = [];

% Drone starts at centre hovering at z=3
r_n0   = [0; 0; 0];
v0     = [0; 0; 0];
theta0 = [0; 0; 0];
omega0 = [0; 0; 0];

t_offset = 0;

%% 8. Run one sim per waypoint
for wp = 1:n_wp
    x_ref   = waypoints(wp, 1);
    y_ref   = waypoints(wp, 2);
    z_ref   = waypoints(wp, 3);
    phi_ref = 0;

    t_vec = (0:dt:t_seg)';
    N     = length(t_vec);

    F3_hover  = -m * g;
    u_input   = [t_vec, F3_hover*ones(N,1), zeros(N,1), zeros(N,1), zeros(N,1)];
    ext_input = [t_vec, zeros(N,3)];

    fprintf('\nWaypoint %d/%d: x=%.1f  y=%.1f  z=%.1f\n', ...
             wp, n_wp, x_ref, y_ref, z_ref);

    try
        simIn = Simulink.SimulationInput(model_name);
        simIn = simIn.setModelParameter('StopTime',   num2str(t_seg));
        simIn = simIn.setModelParameter('SolverType', 'Variable-step');
        simIn = simIn.setModelParameter('Solver',     'ode45');
        simIn = simIn.setModelParameter('MaxStep',    num2str(dt));
        simIn = simIn.setModelParameter('RelTol',     '1e-3');
        simIn = simIn.setModelParameter('AbsTol',     '1e-4');
        out = sim(simIn);

        t_out   = out.tout + t_offset;
        pos     = out.position.Data;
        ori     = out.orientation.Data;
        pos_hat = out.position_hat.Data;
        ori_hat = out.orientation_hat.Data;

        t_all       = [t_all;       t_out];
        pos_all     = [pos_all;     pos];
        ori_all     = [ori_all;     ori];
        pos_hat_all = [pos_hat_all; pos_hat];
        ori_hat_all = [ori_hat_all; ori_hat];

        % Pass final state to next segment
        r_n0   = pos(end,:)';
        v0     = out.lin_v.Data(end,:)';
        theta0 = ori(end,:)';
        omega0 = out.ang_v.Data(end,:)';

        r1guess  = pos_hat(end,1); r2guess  = pos_hat(end,2);
        r3guess  = pos_hat(end,3);
        th1guess = ori_hat(end,1); th2guess = ori_hat(end,2);
        th3guess = ori_hat(end,3);

        t_offset = t_offset + t_seg;
        fprintf('  Done.\n');

    catch ME
        fprintf('  ERROR: %s\n', ME.message);
        for k = 1:length(ME.cause)
            fprintf('    Cause %d: %s\n', k, ME.cause{k}.message);
        end
        break;
    end
end

%% 9. Plots
lw = 1.8; fs = 10; fs_t = 11;

c6 = {[0.00 0.45 0.70], [0.85 0.33 0.10], [0.47 0.67 0.19], ...
      [0.49 0.18 0.56], [0.93 0.69 0.13], [0.30 0.75 0.93]};

slabels  = {'r_1','r_2','r_3','\theta_1','\theta_2','\theta_3'};
ylabs    = {'Position [m]','Position [m]','Position [m]', ...
            'Angle [rad]','Angle [rad]','Angle [rad]'};

Xtr = [pos_all, ori_all];
Xes = [pos_hat_all, ori_hat_all];

% Build reference staircase for plotting
t_ref      = (0:dt:(t_offset-dt))';
n_ref      = length(t_ref);
x_ref_plot = zeros(n_ref, 1);
y_ref_plot = zeros(n_ref, 1);
z_ref_plot = zeros(n_ref, 1);
pts_per_seg = round(t_seg/dt);
for wp = 1:n_wp
    i1 = (wp-1)*pts_per_seg + 1;
    i2 = min(wp*pts_per_seg, n_ref);
    x_ref_plot(i1:i2) = waypoints(wp,1);
    y_ref_plot(i1:i2) = waypoints(wp,2);
    z_ref_plot(i1:i2) = waypoints(wp,3);
end

% ideal figure-8 curve for reference overlay
t_ideal = linspace(0, 2*pi, 500);
x_ideal =  a     * sin(t_ideal);
y_ideal =  b     * sin(2*t_ideal) / 2;
z_ideal =  3     * ones(size(t_ideal));

% 3D trajectory
figure('Name','Figure-8 Waypoints 3D','NumberTitle','off', ...
       'Color','white','Position',[100 100 900 650]);
plot3(x_ideal, y_ideal, z_ideal, '--', ...
      'Color',[0.5 0.5 0.5],'LineWidth',1.5,'DisplayName','Ideal figure-8');
hold on;
plot3(Xtr(:,1), Xtr(:,2), Xtr(:,3), '-', ...
      'Color',[0.00 0.45 0.74],'LineWidth',1.8,'DisplayName','True');
scatter3(waypoints(:,1), waypoints(:,2), waypoints(:,3), ...
         80, 'r', 'filled', 'DisplayName','Waypoints');
scatter3(Xtr(1,1), Xtr(1,2), Xtr(1,3), 100, 'g', 'filled', ...
         'DisplayName','Start');
hold off;
xlabel('x [m]'); ylabel('y [m]'); zlabel('z [m]');
title('Figure-8 Trajectory (Waypoints) | with Kalman Bucy observer', ...
      'FontSize', fs_t, 'FontWeight','bold');
legend('Location','best'); grid on; view(0, 90);  % top-down view shows the 8

% Per-axis time plots
ref_plot_all = {x_ref_plot, y_ref_plot, z_ref_plot, ...
                zeros(size(t_ref)), zeros(size(t_ref)), zeros(size(t_ref))};

for s = 1:6
    figure('Name', sprintf('Fig8 - %s', slabels{s}), ...
           'NumberTitle','off','Color','white', ...
           'Position',[40+50*s, 40, 800, 500]);
    hold on;
    plot(t_ref, ref_plot_all{s}, ':', 'Color',[0.5 0.5 0.5], ...
         'LineWidth',1.2,'DisplayName','ref');
    plot(t_all, Xtr(:,s), '-',  'Color', c6{s},      'LineWidth', lw, ...
         'DisplayName',[slabels{s} ' (true)']);
    plot(t_all, Xes(:,s), '--', 'Color', c6{s}*0.65, 'LineWidth', lw, ...
         'DisplayName',[slabels{s} ' (est)']);
    for wp = 1:n_wp
        xline(wp*t_seg,':', 'Color',[0.8 0.2 0.2],'LineWidth',0.8);
    end
    hold off;
    xlabel('Time [s]','FontSize',fs); ylabel(ylabs{s},'FontSize',fs);
    title(sprintf('Figure-8 Waypoints | %s', slabels{s}), ...
          'FontSize',fs_t,'FontWeight','bold');
    legend('Location','best','FontSize',fs-1,'Box','off');
    grid on; grid minor;
    set(gca,'Color','white','GridAlpha',0.15,'MinorGridAlpha',0.05, ...
            'Box','on','FontSize',fs);
end

disp('Figure-8 waypoint simulation complete.');