function imgSampling1()

close all;
load('data/M19.mat')
u1 = U{1};
i1 = I{1};
u1 = u1(22:47);
i1 = i1(22:47);
x = (0:length(u1)-1)/500;
figure;
plot(x,u1,x,i1);
ylim([0,1024]);
xlabel('t [s]');
ylabel('ADC');
legend('x_u(t)','x_i(t)');
title('24V - 0A');
matlab2tikz('../../../../tex/Dok/img/sampling1.tikz'); 
end

