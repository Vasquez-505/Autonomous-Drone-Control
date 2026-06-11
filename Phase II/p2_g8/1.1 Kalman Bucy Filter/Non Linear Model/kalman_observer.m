%% kalman_observer.m
% Phase II - Q8: Kalman-Bucy Observer
% Computes observer gains L1-L4 for all 4 subsystems.
% These gains are used in both the linear (Q8 test) and nonlinear models.
%
% CONVENTION (matches Phase I):
%   SS1 - Altitude:       x = [r3;  v3]
%   SS2 - Lateral-Roll:   x = [r2;  th1; v2;  w1]
%   SS3 - Lateral-Pitch:  x = [r1;  th2; v1;  w2]
%   SS4 - Yaw:            x = [th3; w3]

%% 1. Load drone parameters (sets m, J11, J22, J33, g, poles1-4)
drone_model_parameters

clc


%% 2. State-space matrices (same as Phase I)
A1 = [0, 1; 0, 0];
B1 = [0; 1/m];
C1 = eye(2);

A2 = [0, 0, 1, 0; 0, 0, 0, 1; 0, g, 0, 0; 0, 0, 0, 0];
B2 = [0; 0; 0; 1/J11];
C2 = eye(4);

A3 = [0, 0, 1, 0; 0, 0, 0, 1; 0, -g, 0, 0; 0, 0, 0, 0];
B3 = [0; 0; 0; 1/J22];
C3 = eye(4);

A4 = [0, 1; 0, 0];
B4 = [0; 1/J33];
C4 = eye(2);

%% 3. Process noise covariance Q0 (from Table 2.2)
% State order per subsystem:
%   SS1: [r3,  v3]
%   SS2: [r2,  th1, v2,  w1]
%   SS3: [r1,  th2, v1,  w2]
%   SS4: [th3, w3]

Q0multiplier = 1;  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5

Q0_1 = Q0multiplier* diag([1e-1,   1e-2]);                    % r3, v3
Q0_2 = Q0multiplier* diag([9e-1,   3e-1,  2e-1,  1e-3]);      % r2, th1, v2, w1
Q0_3 = Q0multiplier* diag([9e-1,   2e-1,  2e-1,  1e-3]);      % r1, th2, v1, w2
Q0_4 = Q0multiplier* diag([1e-1,   1e-3]);                    % th3, w3

%% 4. Measurement noise covariance R0 (from Table 2.1)
% Same state order - C=eye so measurements = states directly

R0multiplier = 1;  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

R0_1 = R0multiplier* diag([1.8010e-3,  1.8271e-4]);                           % r3, v3
R0_2 = R0multiplier* diag([4.2821e-1,  3.4817e-4,  2.2190e-3,  1.8271e-6]);  % r2, th1, v2, w1
R0_3 = R0multiplier* diag([7.3221e-1,  2.6060e-4,  2.2190e-3,  4.1449e-6]);  % r1, th2, v1, w2
R0_4 = R0multiplier* diag([3.8313e-2,  7.0775e-6]);                           % th3, w3

%% 5. Compute Kalman gains via lqe()
% lqe(A, G, C, Q0, R0) solves the continuous Riccati equation:
%   A*P + P*A' - P*C'*inv(R0)*C*P + G*Q0*G' = 0
%   L = P * C' * inv(R0)
% G = eye because process noise enters all states directly.

[L1, P1, E1] = my_lqe(A1, eye(2), C1, Q0_1, R0_1);
[L2, P2, E2] = my_lqe(A2, eye(4), C2, Q0_2, R0_2);
[L3, P3, E3] = my_lqe(A3, eye(4), C3, Q0_3, R0_3);
[L4, P4, E4] = my_lqe(A4, eye(2), C4, Q0_4, R0_4);

%% 6. Print results
fprintf('=== Kalman Observer Gains ===\n\n');

fprintf('L1 (Altitude, 2x2):\n');   disp(L1);
fprintf('Observer poles SS1: '); disp(E1.');

fprintf('L2 (Lateral-Roll, 4x4):\n'); disp(L2);
fprintf('Observer poles SS2: '); disp(E2.');

fprintf('L3 (Lateral-Pitch, 4x4):\n'); disp(L3);
fprintf('Observer poles SS3: '); disp(E3.');

fprintf('L4 (Yaw, 2x2):\n');       disp(L4);
fprintf('Observer poles SS4: '); disp(E4.');

% %% 7. Noise power for Simulink Band-Limited White Noise blocks
% % Simulink noise power = variance * sample_time
% dt = 0.01;
% 
% fprintf('\n=== Simulink Noise Power (variance * dt = variance * %.2f) ===\n', dt);
% fprintf('\n--- Measurement noise (add to model OUTPUTS) ---\n');
% fprintf('  r1  (pos X)  : %.6e\n', 7.3221e-1 * dt);
% fprintf('  r2  (pos Y)  : %.6e\n', 4.2821e-1 * dt);
% fprintf('  r3  (pos Z)  : %.6e\n', 1.8010e-3 * dt);
% fprintf('  th1 (roll)   : %.6e\n', 3.4817e-4 * dt);
% fprintf('  th2 (pitch)  : %.6e\n', 2.6060e-4 * dt);
% fprintf('  th3 (yaw)    : %.6e\n', 3.8313e-2 * dt);
% fprintf('  w1  (ang vx) : %.6e\n', 1.8271e-6 * dt);
% fprintf('  w2  (ang vy) : %.6e\n', 4.1449e-6 * dt);
% fprintf('  w3  (ang vz) : %.6e\n', 7.0775e-6 * dt);
% fprintf('  v1  (lin vx) : %.6e\n', 2.2190e-3 * dt);
% fprintf('  v2  (lin vy) : %.6e\n', 2.2190e-3 * dt);
% fprintf('  v3  (lin vz) : %.6e\n', 1.8271e-4 * dt);
% 
% fprintf('\n--- Process noise (add to model STATE DERIVATIVES) ---\n');
% fprintf('  r1  (pos X)  : %.6e\n', 9e-1 * dt);
% fprintf('  r2  (pos Y)  : %.6e\n', 9e-1 * dt);
% fprintf('  r3  (pos Z)  : %.6e\n', 1e-1 * dt);
% fprintf('  th1 (roll)   : %.6e\n', 3e-1 * dt);
% fprintf('  th2 (pitch)  : %.6e\n', 2e-1 * dt);
% fprintf('  th3 (yaw)    : %.6e\n', 1e-1 * dt);
% fprintf('  w1  (ang vx) : %.6e\n', 1e-3 * dt);
% fprintf('  w2  (ang vy) : %.6e\n', 1e-3 * dt);
% fprintf('  w3  (ang vz) : %.6e\n', 1e-3 * dt);
% fprintf('  v1  (lin vx) : %.6e\n', 2e-1 * dt);
% fprintf('  v2  (lin vy) : %.6e\n', 2e-1 * dt);
% fprintf('  v3  (lin vz) : %.6e\n', 1e-2 * dt);

fprintf('\nKalman gains computed. Ready to use in Simulink.\n');

function [L, P, E] = my_lqe(A, G, C, Q, R)
	n = size(A,1);
    
	% Hamiltonian matrix for the Filter ARE (Duality)
	H = [A'           -C'/R*C;
	     -G*Q*G'      -A];
         
	% Eigen decomposition
	[V,D] = eig(H);
    
	% Select stable eigenvalues
	idx = find(real(diag(D)) < 0);
	Vs = V(:,idx);
    
	% Partition
	V1 = Vs(1:n,:);
	V2 = Vs(n+1:end,:);
    
	% Solve Riccati
	P = real(V2 / V1);
    
	% Kalman gain
	L = P * C' / R;
    
	% Observer poles (same as lqe output E)
	E = eig(A - L*C);
end