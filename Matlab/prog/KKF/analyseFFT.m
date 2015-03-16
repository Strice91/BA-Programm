clear; close all;
fs = 500;
t = 0:1/fs:1;
f = 50; % moeglich bis 12kHz

sigsoll=sin(2*pi*f*t);
n=length(sigsoll);

figure
plot(abs(fft(sigsoll)),'.-')

nn=512; % mit zwei 512er FFTs
d=1;
wind=kaiser(nn,16).'; % 3e-7

sp1=fft(sigsoll(1   : nn).*wind);
sp2=fft(sigsoll(1+d:nn+d).*wind);


figure
plot(20*log10(abs(sp1)),'.-')
[m,ind] = max(abs(sp1(1:length(sp1)/2)));
% ind ist der Index, an dem das Betragsspektrum maximal wird


%angle(sp1(ind))
dw=angle(sp2(ind)/sp1(ind));
% dw ist der Differenzwinkel, um den sich der komplexe
% Frequenzzeiger bei einer
% Verschiebung um d Abtastwerte gedreht hat


%wb=ff/2*2*pi/512
fg=(dw/d/(2*pi));
            % dw/d ist der Drehwinkel bezogen auf einen Abtastwert.
            % Haette man einen Differenzwinkel von pi, wäre man genau auf der
            % Nyquistfrequenz (2 Abtastwerte für 2*pi)
            % Bei 2*pi Differenzwinkel wäre man genau auf der Abtastfrequenz.
            % fg normiere ich entgegen der Konvention auf 2*pi, also auf
            % die Abtastfrequenz

freque = fg * fs

