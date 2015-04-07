function imgHallWave()
close all;
load('data\W08.mat');
i1 = I{1}; i1 = i1(1:800); 
i2 = I{8};  i2 = i2(1:800);
i3 = I{12};  i3 = i3(1:800);
x = (1:length(i1)) * timediff{12};
figure;
plot(x,i1,x,i2,x,i3);
legend('0A','1.34A','1.76A');
xlabel('t [s]');
ylabel('u_H [V]');
%matlab2tikz('../../../../tex/Dok/img/hallwave.tikz');
end

