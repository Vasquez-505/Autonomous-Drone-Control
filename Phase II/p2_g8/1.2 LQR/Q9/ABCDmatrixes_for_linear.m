%% Load the drone parameters.
run drone_model_parameters.m

%% Create the state space matrices and the state space model.

% Create the A matrices.
A1 = [0, 1; 0, 0];
A2 = [0, 0, 1, 0; 0, 0, 0, 1; 0, g, 0, 0; 0, 0, 0, 0];
A3 = [0, 0, 1, 0; 0, 0, 0, 1; 0, -g, 0, 0; 0, 0, 0, 0];
A4 = [0, 1; 0, 0];

% Create the B matrices.
B1 = [0; 1/m];
B2 = [0; 0; 0; 1/J11];
B3 = [0; 0; 0; 1/J22];
B4 = [0; 1/J33];

% Create the C matrices.
C1 = eye(2);
C2 = eye(4);
C3 = eye(4);
C4 = eye(2);

% Create the D matrices.
D1 = zeros(2, 1);
D2 = zeros(4, 1);
D3 = zeros(4, 1);
D4 = zeros(2, 1);

%% Coupled system
A = zeros(12);
A(1 : 2, 1 : 2) = A1; 
A(3 : 6, 3 : 6) = A2; 
A(7 : 10, 7 : 10) = A3; 
A(11 : 12, 11 : 12) = A4;

B = zeros(12, 4);
B(1 : 2 ,1) = B1; 
B(3 : 6, 2) = B2; 
B(7 : 10, 3) = B3; 
B(11 : 12, 4) = B4;

C = eye(12);
D = zeros(12, 4);


