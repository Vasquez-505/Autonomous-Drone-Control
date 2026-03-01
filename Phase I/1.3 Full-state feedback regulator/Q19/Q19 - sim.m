%% Q19_nondominant_poles.m
% Influence of Non-Dominant Poles on Longitudinal Dynamics (SS3)
%
% Dominant pair fixed: zeta=0.7, wn=3 -> p_dom = -2.1 +/- 2.14j
% Three non-dominant pole locations tested (multiplier k of sigma_dom):
%   Case 1: k=2  -> p_nd = -4.2, -5.2   (close  - visible in response)
%   Case 2: k=4  -> p_nd = -8.4, -9.4   (Q17 baseline - barely visible)
%   Case 3: k=8  -> p_nd = -16.8,-17.8  (far    - invisible in response)
%
% SS1, SS2, SS4 keep Q17 baseline poles throughout.
% IC: r1(0)=1m to directly excite the longitudinal subsystem.
% Runs on BOTH linear and nonlinear models.
% Saves: Q19_linear_data.mat, Q19_nonlinear_data.mat

addpath('..') 
clear all
clc

%% 1. Parameters
drone_model_parameters

%% 2. State-space matrices
A1 = [0,1; 0,0];                               B1 = [0; 1/m];
A2 = [0,0,1,0; 0,0,0,1; 0,g,0,0; 0,0,0,0];   B2 = [0;0;0;1/J11];
A3 = [0,0,1,0; 0,0,0,1; 0,-g,0,0; 0,0,0,0];  B3 = [0;0;0;1/J22];
A4 = [0,1; 0,0];                               B4 = [0; 1/J33];
C1=eye(2); C2=eye(4); C3=eye(4); C4=eye(2);
D1 = zeros(2, 1);
D2 = zeros(4, 1);
D3 = zeros(4, 1);
D4 = zeros(2, 1);

%% 3. Ackermann + prefilter
function K = ackermann(A, B, poles)
    n=size(A,1); Co=zeros(n,n);
    for i=1:n; Co(:,i)=(A^(i-1))*B; end
    p=real(poly(poles)); pA=zeros(n,n);
    for i=0:n; pA=pA+p(i+1)*A^(n-i); end
    en=zeros(1,n); en(end)=1;
    K=en*inv(Co)*pA; %#ok
end
function ki=prefilter(A,B,C,K)
    Acl=A-B*K; dcg=-C*(Acl\B); ki=1/dcg(1);
end

%% 4. Fixed dominant pair
zeta_dom  = 0.7;
wn_dom    = 3.0;
sigma_dom = zeta_dom * wn_dom;                           % 2.1
wd_dom    = wn_dom * sqrt(1 - zeta_dom^2);               % 2.14
p_dom     = [-sigma_dom+1j*wd_dom, -sigma_dom-1j*wd_dom];

%% 5. Fixed baseline poles for SS1, SS2, SS4
poles1_fix = p_dom;
poles2_fix = [p_dom, -4*sigma_dom, -4*sigma_dom-1];     % -8.4, -9.4
poles4_fix = [-2, -2.5];

K1_fix  = real(ackermann(A1, B1, poles1_fix));  ki1_fix = prefilter(A1,B1,C1(1,:),K1_fix);
K2_fix  = real(ackermann(A2, B2, poles2_fix));  ki2_fix = prefilter(A2,B2,C2(1,:),K2_fix);
K4_fix  = real(ackermann(A4, B4, poles4_fix));  ki4_fix = prefilter(A4,B4,C4(1,:),K4_fix);

%% 6. Three non-dominant pole locations for SS3
%   k = multiplier of sigma_dom
k_list  = [2, 4, 8];
n_cases = length(k_list);    % exactly 3

nd_poles    = zeros(n_cases, 2);
case_labels = cell(n_cases, 1);
for c = 1:n_cases
    k = k_list(c);
    nd_poles(c,:)  = [-k*sigma_dom,  -(k*sigma_dom + 1)];
    case_labels{c} = sprintf('k=%d:  p_{3,4} = [%.1f,  %.1f]', ...
                              k, nd_poles(c,1), nd_poles(c,2));
end

fprintf('Dominant pair (fixed for all cases):\n');
fprintf('  p_{1,2} = %.2f +/- %.2fj\n\n', -sigma_dom, wd_dom);
fprintf('Non-dominant pole cases for SS3:\n');
for c = 1:n_cases
    fprintf('  Case %d: %s\n', c, case_labels{c});
end

%% 7. Simulation settings
t_end = 10;
dt    = 0.01;
t_vec = (0:dt:t_end)';
N     = length(t_vec);

%% 8. Reference setpoints
z_ref=0.5; y_ref=0; x_ref=2; phi_ref=0.5;

F3_hover  = -m*g;
u_input   = [t_vec, F3_hover*ones(N,1), zeros(N,3)];
ext_input = [t_vec, zeros(N,3)];

%% 9. IC: r1(0) = 1m  (longitudinal offset, directly excites SS3)
lin_x0_1 = [0; 0];
lin_x0_2 = [0; 0; 0; 0];
lin_x0_3 = [1; 0; 0; 0];
lin_x0_4 = [0; 0];

% Nonlinear: [r1 r2 r3  v1 v2 v3  th1 th2 th3  w1 w2 w3]
r_n0   = [1; 0; 0];
v0     = [0; 0; 0];
theta0 = [0; 0; 0];
omega0 = [0; 0; 0];

ic_name = 'r_1(0) = 1 m  (longitudinal offset)';

%% 10. ---- LINEAR MODEL ----
lin_model = 'Linear_model';
if bdIsLoaded(lin_model); close_system(lin_model,0); end
load_system(lin_model);

lin_results = cell(n_cases,1);

for c = 1:n_cases
    poles3_c = [p_dom, nd_poles(c,1), nd_poles(c,2)];

    K3  = real(ackermann(A3, B3, poles3_c));
    ki3 = prefilter(A3, B3, C3(1,:), K3);
    K1=K1_fix; ki1=ki1_fix;
    K2=K2_fix; ki2=ki2_fix;
    K4=K4_fix; ki4=ki4_fix;

    set_param([lin_model '/SS1'], 'InitialCondition', mat2str(lin_x0_1));
    set_param([lin_model '/SS2'], 'InitialCondition', mat2str(lin_x0_2));
    set_param([lin_model '/SS3'], 'InitialCondition', mat2str(lin_x0_3));
    set_param([lin_model '/SS4'], 'InitialCondition', mat2str(lin_x0_4));

    fprintf('\n[Linear] Case %d/%d: %s\n', c, n_cases, case_labels{c});
    try
        out = sim(lin_model, t_end);
        lin_results{c} = out;
        fprintf('  Done.\n');
    catch ME
        fprintf('  ERROR: %s\n', ME.message);
        for j=1:length(ME.cause)
            fprintf('    Cause: %s\n', ME.cause{j}.message);
        end
        lin_results{c} = [];
    end
end

save('Q19_linear_data.mat', 'lin_results', 'k_list', 'nd_poles', ...
     'case_labels', 'n_cases', 'ic_name', 'sigma_dom', 'wd_dom');
fprintf('\nSaved Q19_linear_data.mat\n');

%% 11. ---- NONLINEAR MODEL ----
nlin_model = 'Non_Linear_model';
if bdIsLoaded(nlin_model); close_system(nlin_model,0); end
load_system(nlin_model);

nlin_results = cell(n_cases,1);

for c = 1:n_cases
    poles3_c = [p_dom, nd_poles(c,1), nd_poles(c,2)];

    K3  = real(ackermann(A3, B3, poles3_c));
    ki3 = prefilter(A3, B3, C3(1,:), K3);
    K1=K1_fix; ki1=ki1_fix;
    K2=K2_fix; ki2=ki2_fix;
    K4=K4_fix; ki4=ki4_fix;

    fprintf('\n[Nonlinear] Case %d/%d: %s\n', c, n_cases, case_labels{c});
    try
        out = sim(nlin_model, t_end);
        nlin_results{c} = out;
        fprintf('  Done.\n');
    catch ME
        fprintf('  ERROR: %s\n', ME.message);
        for j=1:length(ME.cause)
            fprintf('    Cause: %s\n', ME.cause{j}.message);
        end
        nlin_results{c} = [];
    end
end

save('Q19_nonlinear_data.mat', 'nlin_results', 'k_list', 'nd_poles', ...
     'case_labels', 'n_cases', 'ic_name', 'sigma_dom', 'wd_dom');
fprintf('\nSaved Q19_nonlinear_data.mat\n');

%% 12. ---- PLOT ----
% Colours: one per case
cols = [0.85 0.33 0.10;   % orange  k=2
        0.00 0.45 0.70;   % blue    k=4  (baseline)
        0.47 0.67 0.19];  % green   k=8
lw_lin  = 2.0;
lw_nlin = 1.2;
fs = 10;  fs_t = 11;

figure('Name','Q19 - Non-dominant poles', ...
       'NumberTitle','off','Color','white','Position',[50 50 1100 860]);
sgtitle(sprintf('Q19 — Non-dominant pole influence on longitudinal dynamics\n%s | Linear (—) vs Nonlinear (- -)', ic_name), ...
        'FontSize',12,'FontWeight','bold','Color',[0.15 0.15 0.15]);

sp(1)=subplot(4,1,1); hold on;
title('r_1 — Longitudinal position [m]','FontSize',fs_t,'FontWeight','bold');
sp(2)=subplot(4,1,2); hold on;
title('v_1 — Longitudinal velocity [m/s]','FontSize',fs_t,'FontWeight','bold');
sp(3)=subplot(4,1,3); hold on;
title('\theta_2 — Pitch angle [rad]','FontSize',fs_t,'FontWeight','bold');
sp(4)=subplot(4,1,4); hold on;
title('\omega_2 — Pitch rate [rad/s]','FontSize',fs_t,'FontWeight','bold');

for c = 1:n_cases
    col = cols(c,:);
    lbl = case_labels{c};

    % Linear
    out = lin_results{c};
    if ~isempty(out)
        try
            yout = out.yout;
            t    = out.tout;
            Dx   = yout(:,7:10);        % SS3 output: r1,th2,v1,w2
            plot(sp(1), t, Dx(:,1), '-', 'Color',col,'LineWidth',lw_lin,  'DisplayName',['Lin '  lbl]);
            plot(sp(2), t, Dx(:,3), '-', 'Color',col,'LineWidth',lw_lin,  'DisplayName',['Lin '  lbl]);
            plot(sp(3), t, Dx(:,2), '-', 'Color',col,'LineWidth',lw_lin,  'DisplayName',['Lin '  lbl]);
            plot(sp(4), t, Dx(:,4), '-', 'Color',col,'LineWidth',lw_lin,  'DisplayName',['Lin '  lbl]);
        catch ME; warning('Lin case %d: %s',c,ME.message); end
    end

    % Nonlinear
    out = nlin_results{c};
    if ~isempty(out)
        try
            t   = out.tout;
            plot(sp(1), t, out.position.Data(:,1),    '--','Color',col,'LineWidth',lw_nlin,'DisplayName',['NLin ' lbl]);
            plot(sp(2), t, out.lin_v.Data(:,1),       '--','Color',col,'LineWidth',lw_nlin,'DisplayName',['NLin ' lbl]);
            plot(sp(3), t, out.orientation.Data(:,2), '--','Color',col,'LineWidth',lw_nlin,'DisplayName',['NLin ' lbl]);
            plot(sp(4), t, out.ang_v.Data(:,2),       '--','Color',col,'LineWidth',lw_nlin,'DisplayName',['NLin ' lbl]);
        catch ME; warning('NLin case %d: %s',c,ME.message); end
    end
end

ylbls = {'[m]','[m/s]','[rad]','[rad/s]'};
for s = 1:4
    hold(sp(s),'off');
    ylabel(sp(s), ylbls{s},'FontSize',fs);
    xlabel(sp(s),'Time [s]','FontSize',fs);
    grid(sp(s),'on'); grid(sp(s),'minor');
    legend(sp(s),'Location','eastoutside','FontSize',fs-2,'Box','off');
    set(sp(s),'Color','white','GridAlpha',0.15,'MinorGridAlpha',0.05, ...
              'Box','on','FontSize',fs);
end

annotation('textbox',[0.01 0.002 0.65 0.022], ...
    'String', ...
    'Orange: k=2 (close)   Blue: k=4 (Q17 baseline)   Green: k=8 (far)   |   — Linear   - - Nonlinear', ...
    'EdgeColor','none','FontSize',8.5,'Color',[0.3 0.3 0.3]);

fprintf('\nQ19 complete.\n');