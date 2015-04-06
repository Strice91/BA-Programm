function imgSignalPlot()

close all;

U1 = genSinus(33.9,50,10000,0,2,0);
I1 = genSinus(2.55,50,10000,0,2,0);
U1 = U1(1:end-1);
I1 = I1(1:end-1);
x1 = (1:length(U1)) * 1e-4;

U2 = genSinus(1.5,50,10000,0,2,0);
I2 = genSinus(0.255,50,10000,pi,2,0);
U2 = U2(1:end-1);
I2 = I2(1:end-1);
x2 = (1:length(U2)) * 1e-4;

U3 = genSinus(1.5,50,10000,0,2,1.55);
I3 = genSinus(1.4,50,10000,0,2,1.55);
U3 = U3(1:end-1);
I3 = I3(1:end-1);
x3 = (1:length(U3)) * 1e-4;

figure;
subplot(1,3,1);
[hAx,hLine1,hLine2] = plotyy(x1,U1,x1,I1);
ylabel(hAx(1),'u(t) [V]') % left y-axis
ylabel(hAx(2),'i(t) [A]') % right y-axis
% legend('u(t) [V]','i(t)  [A]')
xlabel('t [s]')
title('Eingangssignal');

subplot(1,3,2);
[hAx,hLine1,hLine2] = plotyy(x2,U2,x2,I2);
ylabel(hAx(1),'u(t) [V]') % left y-axis
ylabel(hAx(2),'u_s(t) [V]') % right y-axis
% legend('u(t)  [V]','u_s(t) [V]')
xlabel('t [s]')
title('Aufbereitung 1');

subplot(1,3,3);
[hAx,hLine1,hLine2] = plotyy(x3,U3,x3,I3);
% ylabel(hAx(1),'x_u(t) [V]') % left y-axis
% ylabel(hAx(2),'x_i(t) [V]') % right y-axis
% legend('x_u(t) [V]','x_i(t)  [V]')
xlabel('t [s]')
title('Aufbereitung 2');
ylim(hAx(1),[0,3.1])
ylim(hAx(2),[0,3.1])
% load('data\W01.mat');
% U2 = U{12};
% I2 = I{12};
% U2 = U2(165:2:950);
% I2 = I2(165:2:950);
% x2 = 1:length(U2);
% subplot(2,3,2);
% [hAx,hLine1,hLine2] = plotyy(x2,U2,x2,I2);




end

