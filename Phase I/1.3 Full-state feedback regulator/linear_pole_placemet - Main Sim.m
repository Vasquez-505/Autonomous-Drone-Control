%% Q14_pole_placement_linear.m
% Q14 - Full-state feedback pole placement on the LINEAR Simulink model
%
% HOW ICs ARE HANDLED (no set_param needed):
%   In each SS block dialog, set "Initial conditions" to:
%       SS1 -> x0_1
%       SS2 -> x0_2
%       SS3 -> x0_3
%       SS4 -> x0_4
%   This script writes those workspace variables before each sim() call.
%
% NOTE: Change 'Linear_model' to your actual .slx filename (no extension)
clear all
clc

model_name = 'Linear_model';   % <-- your .slx name

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
dt    = 0.01;
t_end = 6;


%% 4. Pole placement via Ackermann's formula (no toolbox required)
function K = ackermann(A, B, poles)
    n        = size(A, 1);
    Co       = zeros(n, n);
    for i    = 1:n
        Co(:,i) = (A^(i-1)) * B;
    end
    p_coeffs = real(poly(poles));
    pA       = zeros(n, n);
    for i    = 0:n
        pA   = pA + p_coeffs(i+1) * A^(n-i);
    end
    en       = zeros(1, n);
    en(end)  = 1;
    K        = en * inv(Co) * pA;  %#ok
end

function ki = prefilter(A, B, C, K)
    % DC gain of closed-loop: ki = 1 / (C * inv(-(A-BK)) * B)
    % same as 1/dcgain(ss(A-BK, B, C, 0)) but no toolbox needed
    Acl  = A - B*K;
    dcg  = -C * (Acl \ B);   % C * inv(-Acl) * B
    ki   = 1 / dcg(1);
end

% SS1 - Altitude

K1     = real(ackermann(A1, B1, poles1));
ki1    = prefilter(A1, B1, C1(1,:), K1);

% SS2 - Lateral-Roll

K2     = real(ackermann(A2, B2, poles2));
ki2    = prefilter(A2, B2, C2(1,:), K2);

% SS3 - Lateral-Pitch

K3     = real(ackermann(A3, B3, poles3));
ki3    = prefilter(A3, B3, C3(1,:), K3);

% SS4 - Yaw

K4     = real(ackermann(A4, B4, poles4));
ki4    = prefilter(A4, B4, C4(1,:), K4);

fprintf('Closed-loop eigenvalues:\n');
fprintf('  SS1 (altitude)      : '); disp(real(eig(A1-B1*K1)).');
fprintf('  SS2 (lateral-roll)  : '); disp(real(eig(A2-B2*K2)).');
fprintf('  SS3 (lateral-pitch) : '); disp(real(eig(A3-B3*K3)).');
fprintf('  SS4 (yaw)           : '); disp(real(eig(A4-B4*K4)).');
fprintf('Pre-filter gains:\n');
fprintf('  ki1=%.4f  ki2=%.4f  ki3=%.4f  ki4=%.4f\n', ki1, ki2, ki3, ki4);

%% 5. Reference setpoints (regulate to origin)
z_ref   = 4;
y_ref   = 1;
x_ref   = 2;
phi_ref = 0.5;

%% 6. Initial condition sets
% x0_1: [r3; v3]
% x0_2: [r2; th1; v2; w1]
% x0_3: [r1; th2; v1; w2]
% x0_4: [th3; w3]
ic_sets = {
%    x0_1          x0_2                  x0_3                  x0_4
    [0.5; 0],       [0; 0; 0; 0],         [0;   0;   0; 0],     [0;   0];
    [0;   0],     [0; 0; 0; 0],         [1.0; 0;   0; 0],     [0;   0];
    [0.5; 0],     [0; 0.1; 2; 0.2],         [1.0; 0.1; 0; 0],     [0.1; 0];
};

ic_names = { ...
    'IC: r_3 = 0.5 m (altitude)', ...
    'IC: r_1 = 1 m (longitudinal)', ...
    'IC: r_3=0.5 m, r_1=1 m, v_2 = 2m/s, theta_1=0.1 rad, theta_2=0.1 rad, theta_3= 0.1 w1 = 0.2 rad/s'};

%% 7. Run Simulink for each IC set
% IMPORTANT: In Simulink, enable output logging once:
% The SS blocks must have Initial conditions set to x0_1/x0_2/x0_3/x0_4

if bdIsLoaded(model_name)
    close_system(model_name, 0);
end
load_system(model_name);

c_rgb = [0.00 0.45 0.70;
         0.85 0.33 0.10;
         0.47 0.67 0.19];
lw = 1.8;  fs = 10;  fs_t = 11;

results = cell(size(ic_sets,1), 1);

for idx = 1:size(ic_sets,1)
    fprintf('\nRunning %s ...\n', ic_names{idx});

    % Write ICs to workspace - Simulink SS blocks read these directly
    x0_1 = ic_sets{idx,1};
    x0_2 = ic_sets{idx,2};
    x0_3 = ic_sets{idx,3};
    x0_4 = ic_sets{idx,4};

    set_param('Linear_model/SS2', 'X0', mat2str(x0_2));

    try
        out = sim(model_name, t_end);
        results{idx} = out;
        fprintf('  Done.\n');
        if idx == 1
            fprintf('  Available output fields:\n');
            disp(fieldnames(out));
        end
    catch ME
        fprintf('  ERROR: %s\n', ME.message);
        for k = 1:length(ME.cause)
            fprintf('    Cause %d: %s\n', k, ME.cause{k}.message);
        end
        results{idx} = [];
    end
end

%% 8. Plot results  (style matching last year's report)
% Colours: blue=x, orange=y, black=z  (same as report Figure 42)
c_x   = [0.00 0.45 0.70];   % blue
c_y   = [0.85 0.33 0.10];   % orange
c_z   = [0.47 0.67 0.19];   % black
c_phi = [0.47 0.67 0.19];   % green (for phi only plot)

for idx = 1:size(ic_sets,1)
    out = results{idx};

    out_linear = out;
    if isempty(out); continue; end

    % Extract states from each SS block output
    % Each SS block output is the full state vector via C=eye
    %   z   -> [r3, v3]
    %   y   -> [r2, th1, v2, w1]
    %   x   -> [r1, th2, v1, w2]
    %   phi -> [th3, w3]
    try
        % yout columns: z(2) | y(4) | x(4) | phi(2)  = 12 total
        yout  = out.yout;
        t_out = out.tout;

        Dz   = yout(:, 1:2);    % SS1: r3, v3
        Dy   = yout(:, 3:6);    % SS2: r2, th1, v2, w1
        Dx   = yout(:, 7:10);   % SS3: r1, th2, v1, w2
        Dphi = yout(:, 11:12);  % SS4: th3, w3

        % Positions:  r1=Dx(:,1),  r2=Dy(:,1),  r3=Dz(:,1)
        r1 = Dx(:,1);   r2 = Dy(:,1);   r3 = Dz(:,1);
        % Velocities: v1=Dx(:,3),  v2=Dy(:,3),  v3=Dz(:,2)
        v1 = Dx(:,3);   v2 = Dy(:,3);   v3 = Dz(:,2);
        % Orientations: th1=Dy(:,2), th2=Dx(:,2), th3=Dphi(:,1)
        th1 = Dy(:,2);  th2 = Dx(:,2);  th3 = Dphi(:,1);
        % Angular velocities: w1=Dy(:,4), w2=Dx(:,4), w3=Dphi(:,2)
        w1 = Dy(:,4);   w2 = Dx(:,4);   w3 = Dphi(:,2);

    catch ME
        warning('Could not extract states for IC%d: %s', idx, ME.message);
        continue;
    end

    figure('Name', sprintf('Linear Model IC%d', idx), ...
           'NumberTitle','off','Color','white','Position',[50+idx*25 50 900 800]);
    sgtitle(sprintf('Linear Model  |  %s', ic_names{idx}), ...
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

save('linear_data.mat')
fprintf('\nQ14 linear complete.\n');
