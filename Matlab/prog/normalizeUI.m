function [ Unorm, Inorm ] = normalizeUI(U,I)

U = U(1:end-10);
I = I(1:end-10);

U_mean = mean(U);
I_mean = mean(I);

U = double(U) - U_mean;
I = double(I) - I_mean;

U_max = max(abs(double(U)));
I_max = max(abs(double(I)));

U = U / U_max;
I = I / I_max;

a = 0.8376;
b = 0.2022;

Ulp = lp_filt(U,a-0.03,b+0.03);
Ilp = lp_filt(I,a,b);

t = 1:length(U);

plot(U,'r');
hold on;
plot(Ulp,'r--')
plot(I,'b');
plot(Ilp,'b--')

end

