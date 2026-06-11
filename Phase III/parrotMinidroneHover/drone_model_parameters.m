%% Parrot Mambo Fly Drone - Model Parameters.
m = 0.063; % Total drone mass [kg]

J11 = 5.8286e-5; % Moment of inertia X-axis (roll axis), J_11 [kg*(m^2)]
J22 = 7.1691e-5; % Moment of inertia Y-axis (pitch axis), J_22 [kg*(m^2)]
J33 = 3.0e-5; % Moment of inertia Z-axis (yaw axis), J_33 [kg*(m^2)]

L = 0.0624;         % Arm length - distance from center of mass to propeller [m]

g = 9.81;           % Gravitational acceleration [m/s^2]

K_T = 4.72e-08;     % Thrust constant - maps propeller speed squared to thrust force
                    % T_i = K_T * Omega_i^2 [N*(rad/s)^(-2)]

K_tau = 1.1393e-10; % Torque constant - maps propeller speed squared to reaction torque
                    % tau_i = K_tau * Omega_i^2 [N*m*(rad/s)^(-2)]

K_u = 13840.4;      % Input constant - maps motor command signal to propeller speed squared
                    % Omega_i^2 = K_u * u_i [(rad/s)^2 per command unit]

u_imax = 500;       % Maximum motor command signal - upper saturation limit for each
                    % motor input u_i in [0, u_imax] (dimensionless command units)


%1st Try for poles
% SS1 - Altitude (2nd order)
%poles1 = [-3, -4];

% SS2 - Lateral-Roll (4th order)
%poles2 = [-5, -4, -6, -7];

% SS3 - Longitudinal-Pitch (4th order)
%poles3 = [-3, -4, -5, -6];

% SS4 - Yaw (2nd order)
%poles4 = [-2, -3];

%   Dominant pair : zeta=0.7, wn=3  -> settling ~1.4s, overshoot ~5%
%   Non-dominant  : 4x further left -> invisible in response
zeta  = 0.7;  wn = 3;
sigma = zeta * wn;                        % = 2.1
wd    = wn * sqrt(1 - zeta^2);            % = 2.14
p_dom = [-sigma + 1j*wd, -sigma - 1j*wd]; % -2.1 +/- 2.14j
 

% SS1 - Altitude (2nd order): dominant pair only
poles1 = p_dom;

% SS2 - Lateral-Roll (4th order): dominant + 2 fast real poles
poles2 = [p_dom, -4*sigma,  -4*sigma - 1];   % fast: -8.4, -9.4

% SS3 - Lateral-Pitch (4th order): same structure
poles3 = [p_dom, -4*sigma,  -4*sigma - 1];

% SS4 - Yaw (2nd order): slightly slower is fine for yaw
poles4 = [-2, -2.5];

save('drone_model_parameters.mat')