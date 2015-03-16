clear;
Fs = 500;
Ts = 1/Fs;
N = 512;
f1 = 50;
t = (0:N-1)*Ts;
LSD = 0.01;
noise = sqrt(LSD/Ts)*randn(1,length(t));
sig = 1.2345*sin(2*pi*f1*t) + 1*0.01*noise;

% Frequenzbestimmung durch Bildung von analytischem Signal
sigc=hilbert(sig);
phdiff=angle(sigc(2:end)./sigc(1:end-1));
phdiffmean=mean(phdiff);
f_calc1=Fs*phdiffmean/2/pi
return