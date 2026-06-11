%% In the Simulation environment, the logged variables 
% (from 'Scopes' and 'to Workspace' blocks) will go to a variable called 'out'
%% Get Measured states
tv = out.measuredStates.time; % time

r1 = out.measuredStates.signals.values(:,1); % r1 (m)
r2 = out.measuredStates.signals.values(:,2); % r2 (m)
r3 = out.measuredStates.signals.values(:,3); % r3 (m)

theta1 = out.measuredStates.signals.values(:,6); % theta1 (rad)
theta2 = out.measuredStates.signals.values(:,5); % theta2 (rad)
theta3 = out.measuredStates.signals.values(:,4); % theta3 (rad)

vb1 = out.measuredStates.signals.values(:,7); % vb1 (m/s)
vb2 = out.measuredStates.signals.values(:,8); % vb2 (m/s)
vb3 = out.measuredStates.signals.values(:,9); % vb3 (m/s)

wb1 = out.measuredStates.signals.values(:,10); % wb1 (rad/s)
wb2 = out.measuredStates.signals.values(:,11); % wb2 (rad/s)
wb3 = out.measuredStates.signals.values(:,12); % wb3 (rad/s)

%% Get computed control action (not saturated) and motor commands (saturated)
F3c = out.controlActionFM.signals.values(:,1); % F3 (total thrust)
M1c = out.controlActionFM.signals.values(:,4); % M1 (moment about X)
M2c = out.controlActionFM.signals.values(:,3); % M2 (moment about Y)
M3c = out.controlActionFM.signals.values(:,2); % M3 (moment about Z)

u1sat = out.motorCommandsOut.signals.values(:,1); % motor 1 (saturated)
u2sat = out.motorCommandsOut.signals.values(:,2); % motor 2 (saturated)
u3sat = out.motorCommandsOut.signals.values(:,3); % motor 3 (saturated)
u4sat = out.motorCommandsOut.signals.values(:,4); % motor 4 (saturated)

%% Get Reference Trajectory (in r1, r2, r3, theta3)
r1_ref = out.posOriRef.signals.values(:,1); % r1 ref
r2_ref = out.posOriRef.signals.values(:,2); % r2 ref
r3_ref = out.posOriRef.signals.values(:,3); % r3 ref
theta3_ref = out.posOriRef.signals.values(:,4); % theta3 ref

%% Plot the variables
% measured variables
figure(1)
sp_rm = subplot(2,2,1);
plot(tv, [r1 r2 r3])
hold on
set(sp_rm, 'ColorOrderIndex',1)
plot(tv, [r1_ref r2_ref r3_ref],':')
hold off
legend('r_1', 'r_2', 'r_3')
ylabel('r (m)')
xlabel('time (s)')

sp_thetam = subplot(2,2,2);
plot(tv, [theta1 theta2 theta3])
hold on
plot(tv, theta3_ref,':')
hold off
legend('\theta_1','\theta_2','\theta_3')
ylabel('\theta (rad)')
xlabel('time (s)')

sp_vm = subplot(2,2,3);
plot(tv, [vb1 vb2 vb3])
legend('v_{b1}', 'v_{b2}', 'v_{b3}')
ylabel('v_b (m/s)')
xlabel('time (s)')

sp_wm = subplot(2,2,4);
plot(tv, [wb1 wb2 wb3])
legend('\omega_{b1}', '\omega_{b2}', '\omega_{b3}')
ylabel('\omega_b (rad/s)')
xlabel('time (s)')


linkaxes([sp_rm sp_thetam sp_vm sp_wm],'x')

% control action F, M, and motor commands
figure(2)
sp_F3c = subplot(3,1,1);
plot(tv, F3c)
grid on
legend('F_3')
ylabel('F_3 (N)')
xlabel('time (s)')

sp_Mc=subplot(3,1,2);
plot(tv, [M1c M2c M3c])
grid on
legend('M_1', 'M_2','M_3')
ylabel('M (Nm)')
xlabel('time (s)')

sp_usat=subplot(3,1,3);
plot(tv, [u1sat u2sat u3sat u4sat])
grid on
legend('u_1', 'u_2','u_3', 'u_4')
ylabel('Saturated motor command')
xlabel('time (s)')


linkaxes([sp_F3c sp_Mc sp_usat],'x')

