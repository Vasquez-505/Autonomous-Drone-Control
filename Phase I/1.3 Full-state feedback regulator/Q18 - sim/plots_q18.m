%% Q18_plot_combined.m
% Loads Q18_linear_data.mat and Q18_nonlinear_data.mat
% Plots Linear (solid) vs Nonlinear (dashed) for every pole case.
% Produces 2 figures per IC set:
%   Fig A: r1, r3, v1, v3  (the varied subsystems)
%   Fig B: theta2, omega2  (pitch - driven by SS3)
%
% Run order:
%   1. Q18_poles_linear.m      -> Q18_linear_data.mat
%   2. Q18_poles_nonlinear.m   -> Q18_nonlinear_data.mat
%   3. This script

clear all
clc

%% 1. Load
lin  = load('Q18_linear_data.mat');
nlin = load('Q18_nonlinear_data.mat');

n_cases = lin.n_cases;   % 6
n_ic    = lin.n_ic;      % 2

%% 2. Colour and line-style scheme
%  Colour  -> wn:   orange = 1.5,  blue = 3.0
%  Style   -> zeta: solid = 0.3,   dashed = 0.7,   dotted = 1.0
%  Width   -> model: thick = linear,  thin = nonlinear

col_wn  = containers.Map([1.5, 3.0], ...
              {[0.85 0.33 0.10], [0.00 0.45 0.70]});   % orange / blue
ls_zeta = containers.Map([0.3, 0.7, 1.0], {'-','--',':'});
lw_lin  = 2.0;
lw_nlin = 1.2;
fs = 10;  fs_t = 11;

%% 3. Extract helpers
function S = get_linear(results, idx, c)
    out  = results{idx,c};
    yout = out.yout;
    S.t  = out.tout;
    Dz   = yout(:,1:2);    % SS1: r3, v3
    Dy   = yout(:,3:6);    % SS2: r2,th1,v2,w1
    Dx   = yout(:,7:10);   % SS3: r1,th2,v1,w2
    S.r1 = Dx(:,1);  S.r3 = Dz(:,1);
    S.v1 = Dx(:,3);  S.v3 = Dz(:,2);
    S.th2= Dx(:,2);  S.w2 = Dx(:,4);
end

function S = get_nonlinear(results, idx, c)
    out  = results{idx,c};
    S.t  = out.tout;
    S.r1 = out.position.Data(:,1);
    S.r3 = out.position.Data(:,3);
    S.v1 = out.lin_v.Data(:,1);
    S.v3 = out.lin_v.Data(:,3);
    S.th2= out.orientation.Data(:,2);
    S.w2 = out.ang_v.Data(:,2);
end

%% 4. Plot
for idx = 1:n_ic

    %% --- Figure A: positions and velocities ---
    fA = figure('Name', sprintf('Q18 IC%d - Pos & Vel', idx), ...
                'NumberTitle','off','Color','white', ...
                'Position',[40+idx*25 40 1100 860]);
    sgtitle(sprintf('Q18 — Linear (thick) vs Nonlinear (thin) | %s', ...
            lin.ic_names{idx}), ...
            'FontSize',12,'FontWeight','bold','Color',[0.15 0.15 0.15]);

    sp(1)=subplot(4,1,1); hold on;
    title('r_1 — Longitudinal position [m]','FontSize',fs_t,'FontWeight','bold');
    sp(2)=subplot(4,1,2); hold on;
    title('r_3 — Vertical position [m]','FontSize',fs_t,'FontWeight','bold');
    sp(3)=subplot(4,1,3); hold on;
    title('v_1 — Longitudinal velocity [m/s]','FontSize',fs_t,'FontWeight','bold');
    sp(4)=subplot(4,1,4); hold on;
    title('v_3 — Vertical velocity [m/s]','FontSize',fs_t,'FontWeight','bold');

    for c = 1:n_cases
        zeta = lin.pole_cases(c,1);
        wn   = lin.pole_cases(c,2);
        col  = col_wn(wn);
        ls   = ls_zeta(zeta);
        lbl  = lin.case_labels{c};

        L=[]; NL=[];
        try; L  = get_linear(lin.results,   idx, c); catch; end
        try; NL = get_nonlinear(nlin.results, idx, c); catch; end

        vars_L  = {};  vars_NL = {};
        if ~isempty(L);  vars_L  = {L.r1,  L.r3,  L.v1,  L.v3 }; end
        if ~isempty(NL); vars_NL = {NL.r1, NL.r3, NL.v1, NL.v3}; end

        for s = 1:4
            if ~isempty(L)
                plot(sp(s), L.t,  vars_L{s},  ls, 'Color',col, ...
                     'LineWidth',lw_lin,  'DisplayName',['Lin '  lbl]);
            end
            if ~isempty(NL)
                plot(sp(s), NL.t, vars_NL{s}, ls, 'Color',col, ...
                     'LineWidth',lw_nlin, 'DisplayName',['NLin ' lbl]);
            end
        end
    end

    ylbls = {'[m]','[m]','[m/s]','[m/s]'};
    for s = 1:4
        hold(sp(s),'off');
        ylabel(sp(s), ylbls{s}, 'FontSize',fs);
        xlabel(sp(s), 'Time [s]', 'FontSize',fs);
        grid(sp(s),'on'); grid(sp(s),'minor');
        legend(sp(s),'Location','eastoutside','FontSize',fs-2,'Box','off');
        set(sp(s),'Color','white','GridAlpha',0.15,'MinorGridAlpha',0.05, ...
                  'Box','on','FontSize',fs);
    end
    annotation('textbox',[0.01 0.002 0.75 0.022], ...
        'String', ...
        'Colour: orange=\omega_n=1.5 rad/s, blue=\omega_n=3.0 rad/s   |   Style: — \zeta=0.3   -- \zeta=0.7   \cdot\cdot \zeta=1.0   |   Thick=Linear, Thin=Nonlinear', ...
        'EdgeColor','none','FontSize',8.5,'Color',[0.3 0.3 0.3]);

    %% --- Figure B: orientation and angular velocity ---
    fB = figure('Name', sprintf('Q18 IC%d - Orientation', idx), ...
                'NumberTitle','off','Color','white', ...
                'Position',[60+idx*25 60 1100 480]);
    sgtitle(sprintf('Q18 — Linear (thick) vs Nonlinear (thin) | %s | Pitch', ...
            lin.ic_names{idx}), ...
            'FontSize',12,'FontWeight','bold','Color',[0.15 0.15 0.15]);

    sp2(1)=subplot(2,1,1); hold on;
    title('\theta_2 — Pitch angle [rad]','FontSize',fs_t,'FontWeight','bold');
    sp2(2)=subplot(2,1,2); hold on;
    title('\omega_2 — Pitch rate [rad/s]','FontSize',fs_t,'FontWeight','bold');

    for c = 1:n_cases
        zeta = lin.pole_cases(c,1);
        wn   = lin.pole_cases(c,2);
        col  = col_wn(wn);
        ls   = ls_zeta(zeta);
        lbl  = lin.case_labels{c};

        L=[]; NL=[];
        try; L  = get_linear(lin.results,   idx, c); catch; end
        try; NL = get_nonlinear(nlin.results, idx, c); catch; end

        if ~isempty(L)
            plot(sp2(1), L.t,  L.th2, ls, 'Color',col,'LineWidth',lw_lin,  'DisplayName',['Lin '  lbl]);
            plot(sp2(2), L.t,  L.w2,  ls, 'Color',col,'LineWidth',lw_lin,  'DisplayName',['Lin '  lbl]);
        end
        if ~isempty(NL)
            plot(sp2(1), NL.t, NL.th2,ls, 'Color',col,'LineWidth',lw_nlin, 'DisplayName',['NLin ' lbl]);
            plot(sp2(2), NL.t, NL.w2, ls, 'Color',col,'LineWidth',lw_nlin, 'DisplayName',['NLin ' lbl]);
        end
    end

    ylbls2 = {'[rad]','[rad/s]'};
    for s = 1:2
        hold(sp2(s),'off');
        ylabel(sp2(s), ylbls2{s}, 'FontSize',fs);
        xlabel(sp2(s), 'Time [s]', 'FontSize',fs);
        grid(sp2(s),'on'); grid(sp2(s),'minor');
        legend(sp2(s),'Location','eastoutside','FontSize',fs-2,'Box','off');
        set(sp2(s),'Color','white','GridAlpha',0.15,'MinorGridAlpha',0.05, ...
                   'Box','on','FontSize',fs);
    end
end

fprintf('Q18 combined plot complete.\n');