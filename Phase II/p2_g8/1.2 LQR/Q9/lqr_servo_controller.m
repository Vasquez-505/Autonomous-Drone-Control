clc
%% Load initial system dynamics
run ABCDmatrixes_for_linear
run drone_model_parameters

%% Augmented system - decoupled systems
c1 = [1 0];            %r3
c2 = [1 0 0 0];        %r2
c3 = [1 0 0 0];        %r1
c4 = [1 0];            %th3

A1_bar = [A1, zeros(2,1); -c1, 0];
A2_bar = [A2, zeros(4,1); -c2, 0];
A3_bar = [A3, zeros(4,1); -c3, 0];
A4_bar = [A4, zeros(2,1); -c4, 0];

B1_bar = [B1; 0];
B2_bar = [B2; 0];
B3_bar = [B3; 0];
B4_bar = [B4; 0];

C1_bar = [c1, 0];
C2_bar = [c2, 0];
C3_bar = [c3, 0];
C4_bar = [c4, 0];

D1_bar = zeros(1,1);
D2_bar = zeros(1,1);
D3_bar = zeros(1,1);
D4_bar = zeros(1,1);

% Dynamic model of each subsystem
ss1_augmented = ss(A1_bar, B1_bar, C1_bar, D1_bar);
ss2_augmented = ss(A2_bar, B2_bar, C2_bar, D2_bar);
ss3_augmented = ss(A3_bar, B3_bar, C3_bar, D3_bar);
ss4_augmented = ss(A4_bar, B4_bar, C4_bar, D4_bar);

%% LQR gains%%%%%%%%%
% Matrices Q and R

% (different balance between state error and control effort)%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%% dQ > 1 , dR = 1 : controll matters more than actuator intensity
%%%%%%%%%%%%%% dQ < 1 , dR = 1 : controll matters less than actuator intensity
dQ = 1e0; 

Q1 = diag([1,  1, 10]) * dQ;
Q2 = diag([1, 0.1, 0.1, 0.1, 10]) * dQ;
Q3 = diag([1, 0.1, 0.1, 0.1, 10]) * dQ;
Q4 = diag([1, 0.1, 10]) * dQ;

dR = 1e0; % Multiplier to change R%%%%%%%%%%

% Calculate LQR for each independent subsystem
[K1_lqr, P1, cl_poles1] = lqr(ss1_augmented, Q1, 1*dR);
[K2_lqr, P2, cl_poles2] = lqr(ss2_augmented, Q2, 1*dR);
[K3_lqr, P3, cl_poles3] = lqr(ss3_augmented, Q3, 1*dR);
[K4_lqr, P4, cl_poles4] = lqr(ss4_augmented, Q4, 1*dR);

% Extract Proportional (K) and Integral (ki) gains
K1  =  K1_lqr(1:2);
ki1 = -K1_lqr(3);

K2  =  K2_lqr(1:4);
ki2 = -K2_lqr(5);

K3  =  K3_lqr(1:4);
ki3 = -K3_lqr(5);

K4  =  K4_lqr(1:2);
ki4 = -K4_lqr(3);

%% --- CLEARLY PRESENTED GAINS ---
fprintf('\n==================================================\n');
fprintf('            DECOUPLED SUBSYSTEM GAINS\n');
fprintf('==================================================\n');

% Subsystem 1
fprintf('\n--- Subsystem 1 ---\n');
fprintf('K  gains: [ %s ]\n', num2str(K1, '%9.4f '));
fprintf('ki gains: [ %s ]\n', num2str(ki1, '%9.4f '));

% Subsystem 2
fprintf('\n--- Subsystem 2 ---\n');
fprintf('K  gains: [ %s ]\n', num2str(K2, '%9.4f '));
fprintf('ki gains: [ %s ]\n', num2str(ki2, '%9.4f '));

% Subsystem 3
fprintf('\n--- Subsystem 3 ---\n');
fprintf('K  gains: [ %s ]\n', num2str(K3, '%9.4f '));
fprintf('ki gains: [ %s ]\n', num2str(ki3, '%9.4f '));

% Subsystem 4
fprintf('\n--- Subsystem 4 ---\n');
fprintf('K  gains: [ %s ]\n', num2str(K4, '%9.4f '));
fprintf('ki gains: [ %s ]\n', num2str(ki4, '%9.4f '));
fprintf('\n==================================================\n');



