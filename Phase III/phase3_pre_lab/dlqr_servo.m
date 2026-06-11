function [Kd, Kid] = dlqr_servo(Ad, Bd, Cout, Q, R, Ts)
    n  = size(Ad,1);
    Aa = [Ad,        zeros(n,1);
          -Ts*Cout,  1         ];
    Ba = [Bd; 0];
    P  = my_dare(Aa, Ba, Q, R);
    Ka = (R + Ba'*P*Ba) \ (Ba'*P*Aa);
    Kd  = Ka(1:n);
    Kid = Ka(n+1:end);
end