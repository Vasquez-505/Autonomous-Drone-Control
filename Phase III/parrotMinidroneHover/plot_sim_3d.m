%% 3D Trajectory Visualization (Flipped Z-Axis for Positive Altitude)
% This script extracts drone telemetry and flips the Z data by -1 so that 
% 'Up' appears as a positive value on the plot.

% 1. Extract Positional Data (Actual Simulation States)
r1 = out.measuredStates.signals.values(:,1); % X position
r2 = out.measuredStates.signals.values(:,2); % Y position
r3 = out.measuredStates.signals.values(:,3); % Z position

% 2. Extract Reference Data (Target Path)
r1_ref = out.posOriRef.signals.values(:,1); % X reference
r2_ref = out.posOriRef.signals.values(:,2); % Y reference
r3_ref = out.posOriRef.signals.values(:,3); % Z reference

% --- FLIP Z-AXIS FOR VISUALIZATION ONLY ---
r3_plot = -r3; 
r3_ref_plot = -r3_ref;

%% Generate 3D Plot
figure('Name', 'Simulation 3D Trajectory Analysis', 'NumberTitle', 'off');

% Plot the simulated flight trajectory (Solid blue line) using inverted Z
plot3(r1, r2, r3_plot, 'b-', 'LineWidth', 2);
hold on;

% Plot the reference trajectory (Dashed red line) using inverted Z
plot3(r1_ref, r2_ref, r3_ref_plot, 'r--', 'LineWidth', 1.5);

% Mark the starting position (Green diamond)
plot3(r1(1), r2(1), r3_plot(1), 'gd', 'MarkerSize', 10, 'MarkerFaceColor', 'g');

% Mark the final position reached (Red circle)
plot3(r1(end), r2(end), r3_plot(end), 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');

hold off;

%% Aesthetics, Mapping & View Angle
grid on;
box on;
axis equal; % Crucial to prevent geometric warping of the figure-eight shape

% Labels
xlabel('X Position - r_1 (m)', 'FontWeight', 'bold');
ylabel('Y Position - r_2 (m)', 'FontWeight', 'bold');
zlabel('Altitude (m) [Positive Up]', 'FontWeight', 'bold'); % Updated Label
title('Simulated Drone Flight Path: Take-Off & Figure-Eight', 'FontSize', 12);

% Legend
legend('Simulated Flight Path', 'Reference Path', 'Start / Take-off Point', 'Final Position', ...
       'Location', 'best');

% Auto-rotate camera to a clean isometric view
view(3);