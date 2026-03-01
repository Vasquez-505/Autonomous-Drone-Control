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

save('drone_model_parameters.mat')