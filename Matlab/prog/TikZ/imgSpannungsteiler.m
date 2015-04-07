function imgSpannungsteiler()
close all;
load('data\W01.mat');
u1 = I{1}; u1 = u1(200:end-201); 
u2 = I{12};  u2 = u2(200:end-201);
x = (1:length(u1)) * 5.0e-05;
figure;
plot(x,u1,x,u2);
legend('Leerlauf','Volllast');
xlabel('t [s]');
ylabel('u [V]');
%matlab2tikz('../../../../tex/Dok/img/hallwave.tikz');
end

