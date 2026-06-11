%% Noise model parameters for the linear drone Simulink model
% Requires Ts to exist in the caller workspace.

if ~exist('Ts', 'var')
    error('noise_model_parameters:MissingTs', ...
          'Ts must be defined before running noise_model_parameters.m');
end

% Measurement noise variances
var_M_r1  = 7.3221e-1;
var_M_r2  = 4.2821e-1;
var_M_r3  = 1.8010e-3;
var_M_th1 = 3.4817e-4;
var_M_th2 = 2.6060e-4;
var_M_th3 = 3.8313e-2;
var_M_om1 = 1.8271e-6;
var_M_om2 = 4.1449e-6;
var_M_om3 = 7.0775e-6;
var_M_v1  = 2.2190e-3;
var_M_v2  = 2.2190e-3;
var_M_v3  = 1.8271e-4;

% Process noise variances
var_P_r1  = 9e-1;
var_P_r2  = 9e-1;
var_P_r3  = 1e-1;
var_P_th1 = 3e-1;
var_P_th2 = 2e-1;
var_P_th3 = 1e-1;
var_P_om1 = 1e-3;
var_P_om2 = 1e-3;
var_P_om3 = 1e-3;
var_P_v1  = 2e-1;
var_P_v2  = 2e-1;
var_P_v3  = 1e-2;

% Noise power vectors for Simulink Band-Limited White Noise blocks
noise_M_vert = [var_M_r3,  var_M_v3]  * Ts;
noise_P_vert = [var_P_r3,  var_P_v3]  * Ts;

noise_M_lat  = [var_M_r2,  var_M_th1, var_M_v2,  var_M_om1] * Ts;
noise_P_lat  = [var_P_r2,  var_P_th1, var_P_v2,  var_P_om1] * Ts;

noise_M_lon  = [var_M_r1,  var_M_th2, var_M_v1,  var_M_om2] * Ts;
noise_P_lon  = [var_P_r1,  var_P_th2, var_P_v1,  var_P_om2] * Ts;

noise_M_yaw  = [var_M_th3, var_M_om3] * Ts;
noise_P_yaw  = [var_P_th3, var_P_om3] * Ts;

% Optimal covariance matrices per subsystem
Q0_vert = diag([var_P_r3,  var_P_v3]);
R0_vert = diag([var_M_r3,  var_M_v3]);

Q0_lat  = diag([var_P_r2,  var_P_th1, var_P_v2,  var_P_om1]);
R0_lat  = diag([var_M_r2,  var_M_th1, var_M_v2,  var_M_om1]);

Q0_lon  = diag([var_P_r1,  var_P_th2, var_P_v1,  var_P_om2]);
R0_lon  = diag([var_M_r1,  var_M_th2, var_M_v1,  var_M_om2]);

Q0_yaw  = diag([var_P_th3, var_P_om3]);
R0_yaw  = diag([var_M_th3, var_M_om3]);
