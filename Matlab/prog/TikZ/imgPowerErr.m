function imgPowerErr()
close all;
load('data/W01.mat');
ua = I{1}; ua = ua(1:700);
ia = U{1}; ia = ia(1:700);
ib = U{6}; ib = ib(1:700);
ic = U{11}; ic = ic(1:700);
x = (1:length(ua)) * 5e-5;

load('data/W02.mat');
u2 = I{1};
i2 = U{1};
u2 = u2(1:700);
i2 = i2(1:700);
i3 = U{6};
i3 = i3(1:700);
i4 = U{10};
i4 = i4(1:700);

figure;
plot(x,ua,x,ia,x,ib,x,ic);
legend('x_u(t)','x_i(t) 0W','x_i(t) 21W','x_i(t) 46W',...
     'Location','northwest')
xlabel('t [s]')
ylabel('[V] (AC)')
matlab2tikz('../../../../tex/Dok/img/Err/leistungssufenX.tikz');

load('data/D19.mat');
powerError(Data);
matlab2tikz('../../../../tex/Dok/img/Err/PErr0.tikz');
powerEval(Data,1);
box on;
xlim([1,20]);
matlab2tikz('../../../../tex/Dok/img/Err/messwerteP.tikz');

load('data/D20.mat');
powerError(Data);
matlab2tikz('../../../../tex/Dok/img/Err/PErr40.tikz');


end

