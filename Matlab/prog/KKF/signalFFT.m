function [dw,fg] = signalFFT(U,I)

u = (double(U) - mean(U))';
i = (double(I) - mean(I))';

nn=124; % mit zwei 512er FFTs
d=2;
wind=kaiser(nn).'; % 3e-7

sp1=fft(u(1   : nn).*wind);
sp2=fft(i(1+d:nn+d).*wind);

[m,ind] = max(abs(sp1(1:length(sp1)/2)));

%angle(sp1(ind))
dw=angle(sp2(ind)/sp1(ind));

fg=(dw/d/(2*pi));
end