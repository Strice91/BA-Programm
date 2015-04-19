function imgCosPhiErr()
close all;
load('data/W02.mat');
u2 = I{1};
i2 = U{1};
u2 = u2(1:700);
i2 = i2(1:700);
i3 = U{6};
i3 = i3(1:700);
i4 = U{10};
i4 = i4(1:700);
x = (1:length(u2)) * 5e-5;


figure;
plot(x,u2,x,i2,x,i3,x,i4);
legend('x_u(t)','x_i(t) 90^\circ','x_i(t) 22^\circ','x_i(t) 11^\circ',...
    'Location','northwest')
xlabel('t [s]')
ylabel('[V] (AC)')
matlab2tikz('../../../../tex/Dok/img/Err/phaseX.tikz');

load('data/D21')
cosPhiError(Data,3)
matlab2tikz('../../../../tex/Dok/img/Err/PFErr.tikz');

cosPhiEval(Data,1,3)
box on;
xlim([1,20]);
matlab2tikz('../../../../tex/Dok/img/Err/messwertePF.tikz');
end

