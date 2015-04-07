function imgVREF1()
close all;
load('data\VREF01.mat');
VREF1 = VREF(200:499);
load('data\VREF02.mat');
VREF2 = VREF(100:399);
x = (1:length(VREF1))* 5.0e-05;

figure('Position',[0, 0, 1500, 500]);
subplot(1,2,1);
plot(x,VREF1)
ylabel('U_{REF} (AC) [V]')
xlabel('t [s]');
title('U_{REF} ATmega644');
subplot(1,2,2);
plot(x,VREF2)
ylim([-0.02,0.015]);
ylabel('U_{REF} (AC) [V]')
xlabel('t [s]');
title('U_{REF} LM317');


%matlab2tikz('../../../../tex/Dok/img/hallwave.tikz');
end

