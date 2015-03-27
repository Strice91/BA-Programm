function imgUREFumschalten()
close all;
V1 = load('data\VREF05.mat');
V1 = V1.VREF;
V2 = load('data\VREF06.mat');
V2 = V2.VREF;

% Values from 0 to 1
x = (1:length(V1)-1)/length(V1);
% 100 values where done in 0.001 sec => 1Khz
% one value lasts for 0.001 / 100 sec
x = x * 1E-05;

figure;
plot(x,V1(1:end-1),x,V2(1:end-1));
legend('Mit Kondensator','Ohne Kondensator');
xlabel('t [s]')
ylabel('U_{REF} [V]')
end