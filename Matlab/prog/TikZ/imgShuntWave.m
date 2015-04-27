function imgShuntWave()
close all;
load('data\W06.mat');
i1 = U{1}; i1 = i1(1:800); 
i2 = U{8};  i2 = i2(1:800);
i3 = U{12};  i3 = i3(1:800);
x = (1:length(i1)) * 5.0e-05;%* timediff{12};
f = figure;
plot(x,i1,x,i2,x,i3);
legend('0A','1.34A','1.76A');
xlabel('t [s]');
ylabel('u_s [V]');
%matlab2tikz('../../../../tex/Dok/img/hallwave.tikz');
print(f,'-dpng','shuntwave.png')
end

