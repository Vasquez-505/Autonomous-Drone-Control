%% Q18_poles_linear.m
% Q18 - Vary zeta and wn for SS1 (vertical) and SS3 (longitudinal)
% on the LINEAR model. SS2 and SS4 keep the Q17 baseline poles.
% Saves Q18_linear_data.mat for use by Q18_plot_combined.m

clear all
clc

model_name = 'Linear_model';

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

%% 4. Fixed Q17 baseline poles for SS2 and SS4
zeta_base  = 0.7;   wn_base = 3.0;
sigma_base = zeta_base * wn_base;
wd_base    = wn_base * sqrt(1 - zeta_base^2);
p_dom_base = [-sigma_base+1j*wd_base, -sigma_base-1j*wd_base];

poles2_fix = [p_dom_base, -4*sigma_base, -4*sigma_base-1];
poles4_fix = [-2, -2.5];

K2_fix  = real(ackermann(A2, B2, poles2_fix));
ki2_fix = prefilter(A2, B2, C2(1,:), K2_fix);
K4_fix  = real(ackermann(A4, B4, poles4_fix));
ki4_fix = prefilter(A4, B4, C4(1,:), K4_fix);

%% 5. Pole combinations
zeta_list  = [0.3, 0.7, 1.0];
wn_list    = [1.5, 3.0];
pole_cases = [];
for z = zeta_list
    for w = wn_list
        pole_cases = [pole_cases; z, w]; %#ok
    end
end
n_cases = size(pole_cases,1);

case_labels = cell(n_cases,1);
for c = 1:n_cases
    case_labels{c} = sprintf('\\zeta=%.1f, \\omega_n=%.1f', ...
                              pole_cases(c,1), pole_cases(c,2));
end

%% 6. Simulation settings
t_end = 10;

%% 7. Reference setpoints
z_ref=0; y_ref=0; x_ref=0; phi_ref=0;

%% 8. IC sets
lin_ic = {
    [0.5; 0],  [0;0;0;0],  [0;0;0;0],  [0;0];   % IC1: altitude
    [0;   0],  [0;0;0;0],  [1;0;0;0],  [0;0];   % IC2: longitudinal
};
ic_names = {'IC1: r_3 = 0.5 m (altitude)'; ...
            'IC2: r_1 = 1 m (longitudinal)'};
n_ic = size(lin_ic,1);

%% 9. Load model
if bdIsLoaded(model_name); close_system(model_name,0); end
load_system(model_name);

%% 10. Run all combinations
results = cell(n_ic, n_cases);

for c = 1:n_cases
    zeta  = pole_cases(c,1);
    wn    = pole_cases(c,2);
    sigma = zeta * wn;
    wd    = wn * sqrt(max(0, 1 - zeta^2));

    if zeta < 1
        p_dom = [-sigma+1j*wd, -sigma-1j*wd];
    else
        p_dom = [-wn, -wn];
    end

    poles1 = p_dom;
    poles3 = [p_dom, -4*sigma, -4*sigma-1];

    K1  = real(ackermann(A1, B1, poles1));  ki1 = prefilter(A1,B1,C1(1,:),K1);
    K3  = real(ackermann(A3, B3, poles3));  ki3 = prefilter(A3,B3,C3(1,:),K3);
    K2  = K2_fix;  ki2 = ki2_fix;
    K4  = K4_fix;  ki4 = ki4_fix;

    fprintf('\nCase %d/%d: %s\n', c, n_cases, case_labels{c});

    for idx = 1:n_ic
        x0_1 = lin_ic{idx,1};  x0_2 = lin_ic{idx,2};
        x0_3 = lin_ic{idx,3};  x0_4 = lin_ic{idx,4};

        set_param([model_name '/SS1'], 'InitialCondition', mat2str(x0_1));
        set_param([model_name '/SS2'], 'InitialCondition', mat2str(x0_2));
        set_param([model_name '/SS3'], 'InitialCondition', mat2str(x0_3));
        set_param([model_name '/SS4'], 'InitialCondition', mat2str(x0_4));

        try
            out = sim(model_name, t_end);
            results{idx,c} = out;
            fprintf('  IC%d done.\n', idx);
        catch ME
            fprintf('  IC%d ERROR: %s\n', idx, ME.message);
            for k=1:length(ME.cause)
                fprintf('    Cause: %s\n', ME.cause{k}.message);
            end
            results{idx,c} = [];
        end
    end
end

save('Q18_linear_data.mat', 'results', 'pole_cases', 'case_labels', ...
     'ic_names', 'n_ic', 'n_cases');
fprintf('\nSaved Q18_linear_data.mat\nQ18 linear complete.\n');