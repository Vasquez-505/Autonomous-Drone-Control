%% 3D Trajectory Visualization
% This script loads the drone telemetry data and plots the actual 3D 
% flight trajectory against the reference path.

% 1. Load the data
load('RSdata.mat')

% 2. Extract Positional Data (Actual)
r1 = rt_measuredStates.signals.values(:,1); % X position
r2 = rt_measuredStates.signals.values(:,2); % Y position
r3 = rt_measuredStates.signals.values(:,3); % Z position

% 3. Extract Reference Data (Target Path)
r1_ref = rt_posOriRef.signals.values(:,1); % X reference
r2_ref = rt_posOriRef.signals.values(:,2); % Y reference
r3_ref = rt_posOriRef.signals.values(:,3); % Z reference

%% Generate 3D Plot
figure('Name', 'Drone 3D Trajectory Analysis', 'NumberTitle', 'off');

% Plot the actual flight trajectory (Solid blue line)
plot3(r1, r2, r3, 'b-', 'LineWidth', 2);
hold on;

% Plot the reference trajectory (Dashed red line)
plot3(r1_ref, r2_ref, r3_ref, 'r--', 'LineWidth', 1.5);

% Mark the starting/takeoff position (Green diamond)
plot3(r1(1), r2(1), r3(1), 'gd', 'MarkerSize', 10, 'MarkerFaceColor', 'g');

% Mark the final position (Red circle)
plot3(r1(end), r2(end), r3(end), 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');

hold off;

%% Aesthetics and Labels
grid on;
box on;
axis equal; % Ensures scale proportions (1m vertical looks like 1m horizontal)

% Labels
xlabel('X Position - r_1 (m)', 'FontWeight', 'bold');
ylabel('Y Position - r_2 (m)', 'FontWeight', 'bold');
zlabel('Altitude - r_3 (m)', 'FontWeight', 'bold');
title('Drone Flight Path: Take-Off & Figure-Eight Evaluation', 'FontSize', 12);

% Legend
legend('Actual Flight Path', 'Reference Path', 'Start / Take-off Point', 'Final Position', ...
       'Location', 'best');

% Adjust the viewing angle to see the 3D spiral nicely
view(3);