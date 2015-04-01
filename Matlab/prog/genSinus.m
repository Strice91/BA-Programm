function [ sig ] = genSinus(A, f0, fa, phi, periods, offset )

T = 1/f0; %  Periodendauer 
T_end = T * periods;  
Ta = 1/fa; % Abtastzeit 
t = 0:Ta:T_end; % Zeitvektor 
sig = offset + A*sin(2*pi*t*f0-phi);

end

