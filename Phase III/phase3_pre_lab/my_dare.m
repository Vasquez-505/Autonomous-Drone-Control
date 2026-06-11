function P = my_dare(A, B, Q, R)
    P = Q;
    for i = 1:10000
        K  = (R + B'*P*B) \ (B'*P*A);
        Pn = A'*P*A - A'*P*B*K + Q;
        if norm(Pn - P, 'fro') < 1e-12 * (1 + norm(P,'fro'))
            break
        end
        P = Pn;
    end
    P = Pn;
end