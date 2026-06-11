function [Ad, Bd] = zoh_disc(A, B, Ts)
    n  = size(A,1);
    m  = size(B,2);
    M  = expm([A, B; zeros(m, n+m)] * Ts);
    Ad = M(1:n,    1:n);
    Bd = M(1:n, n+1:end);
end