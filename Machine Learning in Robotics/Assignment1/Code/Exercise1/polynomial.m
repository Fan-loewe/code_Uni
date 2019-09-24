function VW = polynomial(V,W,p)
    VW = ones(size(V,1),1+3*p);
    for i=1:p
        VW(:,(3*i-1):(3*i+1))= [V.^i,W.^i,(V.*W).^i];
    end
end