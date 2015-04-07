function imgVCC1()
close all;
load('data\VCC01.mat');
VCC1 = VCC(1:399);
load('data\VCC02.mat');
VCC2 = VCC(1:399)-0.014;
load('data\VCC03.mat');
VCC3 = VCC(1:399)*0.8;
load('data\VCC04.mat');
VCC4 = VCC(1:399);
x = (1:length(VCC1)) * 1.0e-05;

figure;
subplot(2,2,1);
plot(x,VCC1)
ylabel('V_{CC} (AC) [V]')
xlabel('t [s]');
title('Mit CPU, Ohne Kondensator');
subplot(2,2,2);
plot(x,VCC2)
ylabel('V_{CC} (AC) [V]')
xlabel('t [s]');
title('Ohne CPU, Ohne Kondensator');
subplot(2,2,3);
plot(x,VCC3)
ylabel('V_{CC} (AC) [V]')
xlabel('t [s]');
title('Mit CPU, Mit Kondensator');
subplot(2,2,4);
plot(x,VCC4)
ylabel('V_{CC} (AC) [V]')
xlabel('t [s]');
title('Ohne CPU, Mit Kondensator');

%matlab2tikz('../../../../tex/Dok/img/hallwave.tikz');
end

