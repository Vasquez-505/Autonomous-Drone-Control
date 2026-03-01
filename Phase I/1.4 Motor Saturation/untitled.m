%% Q20_motor_saturation.m
% Q20 - Motor Saturation: plots matching report Figures 60-65
%
%  Figure 60: Input force & moments — NO saturation
%  Figure 61: Input force & moments — WITH saturation  (diverging F3)
%  Figure 62: Position + linear velocity — NO saturation  (converges)
%  Figure 63: Orientation + angular velocity — NO saturation
%  Figure 64: Position + linear velocity — WITH saturation  (diverges)
%  Figure 65: Orientation + angular velocity — WITH saturation  (unstable)
%
% SATURATION TOGGLE (zero Simulink changes):
%   Block 2.16 reads u_imax from workspace via parameters(10).
%   sat OFF -> u_imax = 1e9   (clamp never fires)
%   sat ON  -> u_imax = 500   (real hardware limit)
%
% SATURATING POLES (matching report Section 20):
%   One non-dominant pole is placed on the RIGHT half of the s-plane (+2),
%   which makes the controller demand inputs >> 500, causing saturation
%   and loss of stability (positions diverge to infinity as in Fig 64).
% =========================================================================

clear all; clc;

model_name = 'Non_Linear_model';

%% =========================================================================
%  1. PARAMETERS
% =========================================================================
drone_model_parameters
% Loads: m, J11, J22, J33, L, g, K_T, K_tau, K_u, u_imax
% Also loads: zeta, wn, sigma, wd, p_dom, poles1..poles4

%% =========================================================================
%  2. STATE-SPACE MATRICES  (identical to Q14)
% =========================================================================
A1=[0,1;0,0];             B1=[0;1/m];        C1=eye(2);   D1=zeros(2,1);
A2=[0,0,1,0;0,0,0,1;0,g,0,0;0,0,0,0];
B2=[0;0;0;1/J11];         C2=eye(4);         D2=zeros(4,1);
A3=[0,0,1,0;0,0,0,1;0,-g,0,0;0,0,0,0];
B3=[0;0;0;1/J22];         C3=eye(4);         D3=zeros(4,1);
A4=[0,1;0,0];             B4=[0;1/J33];      C4=eye(2);   D4=zeros(2,1);

%% =========================================================================
%  3. SIMULATION SETUP
% =========================================================================
t_end = 20;          % match report x-axis (0 to 20 s)
dt    = 0.01;
t_vec = (0:dt:t_end)';
N     = length(t_vec);

F3_hover  = -m * g;
u_input   = [t_vec, F3_hover*ones(N,1), zeros(N,3)];
ext_input = [t_vec, zeros(N,3)];

% Reference setpoints (Table 2 of report)
x_ref = 2;   y_ref = 1;   z_ref = 0.5;   phi_ref = 0.5;

%% =========================================================================
%  4. HELPER FUNCTIONS  (identical to Q14)
% =========================================================================
function K = ackermann(A, B, poles)
    n  = size(A,1);
    Co = zeros(n,n);
    for i = 1:n; Co(:,i) = (A^(i-1))*B; end
    p_coeffs = real(poly(poles));
    pA = zeros(n,n);
    for i = 0:n; pA = pA + p_coeffs(i+1)*A^(n-i); end
    en = zeros(1,n); en(end)=1;
    K  = en * inv(Co) * pA; %#ok
end

function ki = prefilter(A, B, C, K)
    Acl = A - B*K;
    dcg = -C*(Acl\B);
    ki  = 1/dcg(1);
end

%% =========================================================================
%  5. NOMINAL GAINS  (from drone_model_parameters poles)
% =========================================================================
K1_nom=real(ackermann(A1,B1,poles1));  ki1_nom=prefilter(A1,B1,C1(1,:),K1_nom);
K2_nom=real(ackermann(A2,B2,poles2));  ki2_nom=prefilter(A2,B2,C2(1,:),K2_nom);
K3_nom=real(ackermann(A3,B3,poles3));  ki3_nom=prefilter(A3,B3,C3(1,:),K3_nom);
K4_nom=real(ackermann(A4,B4,poles4));  ki4_nom=prefilter(A4,B4,C4(1,:),K4_nom);

%% =========================================================================
%  6. SATURATING GAINS
%     Report Section 20: "changing one non-dominant pole to the RIGHT side
%     of the s-plane made the inputs saturate."
%     Keep dominant pair of SS3 identical; move one non-dominant to +2.
% =========================================================================
poles3_sat = [p_dom(1), p_dom(2), -4*sigma, +2];
%              dominant pair (same)  fast left  UNSTABLE -> forces saturation

K3_sat =real(ackermann(A3,B3,poles3_sat)); ki3_sat=prefilter(A3,B3,C3(1,:),K3_sat);
K1_sat=K1_nom; ki1_sat=ki1_nom;
K2_sat=K2_nom; ki2_sat=ki2_nom;
K4_sat=K4_nom; ki4_sat=ki4_nom;

fprintf('--- Nominal  SS3 CL eigenvalues: ');
fprintf('%+.3f  ', real(eig(A3-B3*K3_nom))); fprintf('\n');
fprintf('--- Saturating SS3 CL eigenvalues: ');
fprintf('%+.3f  ', real(eig(A3-B3*K3_sat))); fprintf('\n\n');

%% =========================================================================
%  7. INITIAL CONDITIONS  (zero — report starts from rest)
% =========================================================================
r_n0=zeros(3,1); v0=zeros(3,1); theta0=zeros(3,1); omega0=zeros(3,1);

%% =========================================================================
%  8. RUN TWO SIMULATIONS
% =========================================================================
load_system(model_name);

% --- Case A: NO saturation (nominal poles, u_imax disabled) ---------------
fprintf('Running sim 1/2: No saturation ...\n');
K1=K1_nom; K2=K2_nom; K3=K3_nom; K4=K4_nom;
ki1=ki1_nom; ki2=ki2_nom; ki3=ki3_nom; ki4=ki4_nom;
u_imax = 1e9; %#ok<NASGU>
try
    out_nosat = sim(model_name, t_end); fprintf('  Done.\n');
catch ME
    fprintf('  ERROR: %s\n', ME.message); out_nosat = [];
end

% --- Case B: WITH saturation (sat poles, u_imax=500) ----------------------
fprintf('Running sim 2/2: With saturation ...\n');
K1=K1_sat; K2=K2_sat; K3=K3_sat; K4=K4_sat;
ki1=ki1_sat; ki2=ki2_sat; ki3=ki3_sat; ki4=ki4_sat;
u_imax = 500; %#ok<NASGU>
try
    out_sat = sim(model_name, t_end); fprintf('  Done.\n');
catch ME
    fprintf('  ERROR: %s\n', ME.message); out_sat = [];
end

u_imax = 500; %#ok<NASGU>  % restore

%% =========================================================================
%  9. RECONSTRUCT GENERALISED FORCE INPUTS  (F3, M1, M2, M3)
%     Computed from logged states using the feedback law, then passed
%     through Block 2.16 (T_matrix) and saturation, then Block 2.15.
%     This gives the actual generalised forces delivered to the drone.
% =========================================================================
C_pi_4   = cos(pi/4);
T_mat    = [-1/K_T,   1/(K_T*L*C_pi_4),   1/(K_T*L*C_pi_4),  -1/K_tau;
            -1/K_T,  -1/(K_T*L*C_pi_4),   1/(K_T*L*C_pi_4),   1/K_tau;
            -1/K_T,  -1/(K_T*L*C_pi_4),  -1/(K_T*L*C_pi_4),  -1/K_tau;
            -1/K_T,   1/(K_T*L*C_pi_4),  -1/(K_T*L*C_pi_4),   1/K_tau];
K_mat    = [-K_T,  -K_T,  -K_T,  -K_T;
             L*C_pi_4*K_T, -L*C_pi_4*K_T, -L*C_pi_4*K_T,  L*C_pi_4*K_T;
             L*C_pi_4*K_T,  L*C_pi_4*K_T, -L*C_pi_4*K_T, -L*C_pi_4*K_T;
            -K_tau,  K_tau, -K_tau,  K_tau];

function [F3o,M1o,M2o,M3o] = get_inputs(out, K1,K2,K3,K4, ...
        ki1,ki2,ki3,ki4, xr,yr,zr,pr, mg, ulim, T_mat, K_mat, Ku)
    r1=out.position.Data(:,1);  r2=out.position.Data(:,2);  r3=out.position.Data(:,3);
    v1=out.lin_v.Data(:,1);     v2=out.lin_v.Data(:,2);     v3=out.lin_v.Data(:,3);
    th1=out.orientation.Data(:,1); th2=out.orientation.Data(:,2); th3=out.orientation.Data(:,3);
    w1=out.ang_v.Data(:,1);     w2=out.ang_v.Data(:,2);     w3=out.ang_v.Data(:,3);

    x1=[r3,v3]; x2=[r2,th1,v2,w1]; x3=[r1,th2,v1,w2]; x4=[th3,w3];

    % Feedback control law (output = generalised force reference)
    F3_ref = ki1*zr - (x1*K1') - mg;   % note: F3 is negative (downward thrust convention)
    M1_ref = ki2*yr - (x2*K2');
    M2_ref = ki3*xr - (x3*K3');
    M3_ref = ki4*pr - (x4*K4');
    Fgen   = [F3_ref, M1_ref, M2_ref, M3_ref];   % [N x 4]

    % Block 2.16: motor commands
    u_mot  = ((1/(4*Ku)) * T_mat * Fgen')';       % [N x 4]
    % Upper saturation
    u_sat  = min(u_mot, ulim);                     % [N x 4]
    % Block 2.15: effective generalised forces
    Feff   = (Ku * K_mat * u_sat')';               % [N x 4]

    F3o=Feff(:,1); M1o=Feff(:,2); M2o=Feff(:,3); M3o=Feff(:,4);
end

if ~isempty(out_nosat)
    [F3_ns,M1_ns,M2_ns,M3_ns] = get_inputs(out_nosat, ...
        K1_nom,K2_nom,K3_nom,K4_nom, ki1_nom,ki2_nom,ki3_nom,ki4_nom, ...
        x_ref,y_ref,z_ref,phi_ref, m*g, 1e9, T_mat,K_mat,K_u);
end
if ~isempty(out_sat)
    [F3_s,M1_s,M2_s,M3_s] = get_inputs(out_sat, ...
        K1_sat,K2_sat,K3_sat,K4_sat, ki1_sat,ki2_sat,ki3_sat,ki4_sat, ...
        x_ref,y_ref,z_ref,phi_ref, m*g, 500, T_mat,K_mat,K_u);
end

%% =========================================================================
%  10. FIGURE STYLE  (matches report colour scheme)
% =========================================================================
cx=[0.00 0.45 0.70]; cy=[0.85 0.33 0.10]; cz=[0.47 0.67 0.19];  % blue/orange/green
lw=1.5; fs=9; fst=10;

function style_ax(ax, fs)
    set(ax,'Color','white','FontSize',fs,'GridAlpha',0.2,...
        'MinorGridAlpha',0.05,'Box','on');
    grid(ax,'on');
end

%% =========================================================================
%  FIGURE 60 — Input: NO saturation  (two panels: force | moments)
% =========================================================================
if ~isempty(out_nosat)
    t_ns = out_nosat.tout;
    figure('Name','Input No Sat','NumberTitle','off',...
           'Color','white','Position',[40 40 860 300]);

    subplot(1,2,1); hold on;
    plot(t_ns, F3_ns,'k','LineWidth',lw,'DisplayName','F3');
    xlabel('Time (s)','FontSize',fs); ylabel('Input force (N)','FontSize',fs);
    title('Input force over time','FontSize',fst,'FontWeight','bold');
    legend('Location','northeast','FontSize',fs,'Box','off');
    style_ax(gca,fs); xlim([0 t_end]);

    subplot(1,2,2); hold on;
    plot(t_ns,M1_ns,'Color',cx,'LineWidth',lw,'DisplayName','M1');
    plot(t_ns,M2_ns,'Color',cy,'LineWidth',lw,'DisplayName','M2');
    plot(t_ns,M3_ns,'Color',[0 0 0],'LineWidth',lw,'DisplayName','M3');
    xlabel('Time (s)','FontSize',fs); ylabel('Input moment (Nm)','FontSize',fs);
    title('Input moments over time','FontSize',fst,'FontWeight','bold');
    legend('Location','northeast','FontSize',fs,'Box','off');
    style_ax(gca,fs); xlim([0 t_end]);
    sgtitle('No Saturation: Input','FontSize',fst+1,'FontWeight','bold');
end

%% =========================================================================
%  FIGURE 61 — Input: WITH saturation  (F3 diverges, moments plateau)
% =========================================================================
if ~isempty(out_sat)
    t_s = out_sat.tout;
    figure('Name','Input With Sat','NumberTitle','off',...
           'Color','white','Position',[40 380 860 300]);

    subplot(1,2,1); hold on;
    plot(t_s,F3_s,'k','LineWidth',lw,'DisplayName','F3');
    xlabel('Time (s)','FontSize',fs); ylabel('Input force (N)','FontSize',fs);
    title('Input force over time','FontSize',fst,'FontWeight','bold');
    legend('Location','northeast','FontSize',fs,'Box','off');
    style_ax(gca,fs); xlim([0 t_end]);

    subplot(1,2,2); hold on;
    plot(t_s,M1_s,'Color',cx,'LineWidth',lw,'DisplayName','M1');
    plot(t_s,M2_s,'Color',cy,'LineWidth',lw,'DisplayName','M2');
    plot(t_s,M3_s,'Color',[0 0 0],'LineWidth',lw,'DisplayName','M3');
    xlabel('Time (s)','FontSize',fs); ylabel('Input moment (Nm)','FontSize',fs);
    title('Input moments over time','FontSize',fst,'FontWeight','bold');
    legend('Location','northeast','FontSize',fs,'Box','off');
    style_ax(gca,fs); xlim([0 t_end]);
    sgtitle('With Saturation: Input','FontSize',fst+1,'FontWeight','bold');
end

%% =========================================================================
%  FIGURE 62 — Linear displacements: NO saturation  (converges)
% =========================================================================
if ~isempty(out_nosat)
    t_ns=out_nosat.tout;
    r1ns=out_nosat.position.Data(:,1); r2ns=out_nosat.position.Data(:,2); r3ns=out_nosat.position.Data(:,3);
    v1ns=out_nosat.lin_v.Data(:,1);    v2ns=out_nosat.lin_v.Data(:,2);    v3ns=out_nosat.lin_v.Data(:,3);

    figure('Name','Linear No Sat','NumberTitle','off',...
           'Color','white','Position',[920 40 540 600]);
    subplot(2,1,1); hold on;
    plot(t_ns,r1ns,'Color',cx,'LineWidth',lw,'DisplayName','x');
    plot(t_ns,r2ns,'Color',cy,'LineWidth',lw,'DisplayName','y');
    plot(t_ns,r3ns,'Color',cz,'LineWidth',lw,'DisplayName','z');
    ylabel('Position (m)','FontSize',fs); xlabel('Time (s)','FontSize',fs);
    title('Position over time','FontSize',fst,'FontWeight','bold');
    legend('Location','eastoutside','FontSize',fs,'Box','off');
    style_ax(gca,fs); xlim([0 t_end]);

    subplot(2,1,2); hold on;
    plot(t_ns,v1ns,'Color',cx,'LineWidth',lw,'DisplayName','\dot{x}');
    plot(t_ns,v2ns,'Color',cy,'LineWidth',lw,'DisplayName','\dot{y}');
    plot(t_ns,v3ns,'Color',cz,'LineWidth',lw,'DisplayName','\dot{z}');
    ylabel('Linear velocity (m/s)','FontSize',fs); xlabel('Time (s)','FontSize',fs);
    title('Linear velocity over time','FontSize',fst,'FontWeight','bold');
    legend('Location','eastoutside','FontSize',fs,'Box','off');
    style_ax(gca,fs); xlim([0 t_end]);
    sgtitle('No Saturation: Linear Displacements','FontSize',fst+1,'FontWeight','bold');
end

%% =========================================================================
%  FIGURE 63 — Angular displacements: NO saturation
% =========================================================================
if ~isempty(out_nosat)
    t_ns=out_nosat.tout;
    th1ns=out_nosat.orientation.Data(:,1); th2ns=out_nosat.orientation.Data(:,2); th3ns=out_nosat.orientation.Data(:,3);
    w1ns=out_nosat.ang_v.Data(:,1);        w2ns=out_nosat.ang_v.Data(:,2);        w3ns=out_nosat.ang_v.Data(:,3);

    figure('Name','Angular No Sat','NumberTitle','off',...
           'Color','white','Position',[1470 40 540 600]);
    subplot(2,1,1); hold on;
    plot(t_ns,th1ns,'Color',cx,'LineWidth',lw,'DisplayName','\phi');
    plot(t_ns,th2ns,'Color',cy,'LineWidth',lw,'DisplayName','\theta');
    plot(t_ns,th3ns,'Color',cz,'LineWidth',lw,'DisplayName','\psi');
    ylabel('Orientation (rad)','FontSize',fs); xlabel('Time (s)','FontSize',fs);
    title('Orientation over time','FontSize',fst,'FontWeight','bold');
    legend('Location','eastoutside','FontSize',fs,'Box','off');
    style_ax(gca,fs); xlim([0 t_end]);

    subplot(2,1,2); hold on;
    plot(t_ns,w1ns,'Color',cx,'LineWidth',lw,'DisplayName','\dot{\phi}');
    plot(t_ns,w2ns,'Color',cy,'LineWidth',lw,'DisplayName','\dot{\theta}');
    plot(t_ns,w3ns,'Color',cz,'LineWidth',lw,'DisplayName','\dot{\psi}');
    ylabel('Angular velocity (rad/s)','FontSize',fs); xlabel('Time (s)','FontSize',fs);
    title('Angular velocity over time','FontSize',fst,'FontWeight','bold');
    legend('Location','eastoutside','FontSize',fs,'Box','off');
    style_ax(gca,fs); xlim([0 t_end]);
    sgtitle('No Saturation: Angular Displacements','FontSize',fst+1,'FontWeight','bold');
end

%% =========================================================================
%  FIGURE 64 — Linear displacements: WITH saturation  (diverges)
% =========================================================================
if ~isempty(out_sat)
    t_s=out_sat.tout;
    r1s=out_sat.position.Data(:,1); r2s=out_sat.position.Data(:,2); r3s=out_sat.position.Data(:,3);
    v1s=out_sat.lin_v.Data(:,1);    v2s=out_sat.lin_v.Data(:,2);    v3s=out_sat.lin_v.Data(:,3);

    figure('Name','Linear With Sat','NumberTitle','off',...
           'Color','white','Position',[920 680 540 600]);
    subplot(2,1,1); hold on;
    plot(t_s,r1s,'Color',cx,'LineWidth',lw,'DisplayName','x');
    plot(t_s,r2s,'Color',cy,'LineWidth',lw,'DisplayName','y');
    plot(t_s,r3s,'Color',cz,'LineWidth',lw,'DisplayName','z');
    ylabel('Position (m)','FontSize',fs); xlabel('Time (s)','FontSize',fs);
    title('Position over time','FontSize',fst,'FontWeight','bold');
    legend('Location','eastoutside','FontSize',fs,'Box','off');
    style_ax(gca,fs); xlim([0 t_end]);

    subplot(2,1,2); hold on;
    plot(t_s,v1s,'Color',cx,'LineWidth',lw,'DisplayName','\dot{x}');
    plot(t_s,v2s,'Color',cy,'LineWidth',lw,'DisplayName','\dot{y}');
    plot(t_s,v3s,'Color',cz,'LineWidth',lw,'DisplayName','\dot{z}');
    ylabel('Linear velocity (m/s)','FontSize',fs); xlabel('Time (s)','FontSize',fs);
    title('Linear velocity over time','FontSize',fst,'FontWeight','bold');
    legend('Location','eastoutside','FontSize',fs,'Box','off');
    style_ax(gca,fs); xlim([0 t_end]);
    sgtitle('With Saturation: Linear Displacements (UNSTABLE)','FontSize',fst+1,'FontWeight','bold');
end

%% =========================================================================
%  FIGURE 65 — Angular displacements: WITH saturation  (theta diverges)
% =========================================================================
if ~isempty(out_sat)
    t_s=out_sat.tout;
    th1s=out_sat.orientation.Data(:,1); th2s=out_sat.orientation.Data(:,2); th3s=out_sat.orientation.Data(:,3);
    w1s=out_sat.ang_v.Data(:,1);        w2s=out_sat.ang_v.Data(:,2);        w3s=out_sat.ang_v.Data(:,3);

    figure('Name','Angular With Sat','NumberTitle','off',...
           'Color','white','Position',[1470 680 540 600]);
    subplot(2,1,1); hold on;
    plot(t_s,th1s,'Color',cx,'LineWidth',lw,'DisplayName','\phi');
    plot(t_s,th2s,'Color',cy,'LineWidth',lw,'DisplayName','\theta');
    plot(t_s,th3s,'Color',cz,'LineWidth',lw,'DisplayName','\psi');
    ylabel('Orientation (rad)','FontSize',fs); xlabel('Time (s)','FontSize',fs);
    title('Orientation over time','FontSize',fst,'FontWeight','bold');
    legend('Location','eastoutside','FontSize',fs,'Box','off');
    style_ax(gca,fs); xlim([0 t_end]);

    subplot(2,1,2); hold on;
    plot(t_s,w1s,'Color',cx,'LineWidth',lw,'DisplayName','\dot{\phi}');
    plot(t_s,w2s,'Color',cy,'LineWidth',lw,'DisplayName','\dot{\theta}');
    plot(t_s,w3s,'Color',cz,'LineWidth',lw,'DisplayName','\dot{\psi}');
    ylabel('Angular velocity (rad/s)','FontSize',fs); xlabel('Time (s)','FontSize',fs);
    title('Angular velocity over time','FontSize',fst,'FontWeight','bold');
    legend('Location','eastoutside','FontSize',fs,'Box','off');
    style_ax(gca,fs); xlim([0 t_end]);
    sgtitle('With Saturation: Angular Displacements (UNSTABLE)','FontSize',fst+1,'FontWeight','bold');
end

%% =========================================================================
%  SAVE
% =========================================================================
save('Q20_saturation_data.mat','out_nosat','out_sat',...
     'K3_nom','K3_sat','poles3_sat','u_imax');
fprintf('\nQ20 complete. Figures 60-65 generated.\n');