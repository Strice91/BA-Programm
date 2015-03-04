function [ X ] = genRefSine(M,Fs,f,N)

t = 0:N-1;
t = t';
Ts = 1/Fs;
w = 2*pi*f;

peaksM = findpeaks(abs(double(M)));
A = mean(peaksM);

X = A * sin(w*t*Ts);

end

