function [Xlp] = lp_filt(X,a,b)

smp_cnt = length(X);
x_old = mean(X);
Xlp = zeros(size(X));
for i = 1:smp_cnt
    x_temp = X(i);
    x_temp = a * (x_temp + b * x_old);
    %x_temp = (x_temp + x_old) / 2;
    x_old = x_temp;
    Xlp(i) = x_temp;
end


end

