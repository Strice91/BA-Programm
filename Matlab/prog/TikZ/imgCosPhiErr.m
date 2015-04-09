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
ylabel('[V]')
matlab2tikz('../../../../tex/Dok/img/phasenverschiebung.tikz');

% load('data/D19.mat');
% powerError(Data);
% matlab2tikz('../../../../tex/Dok/img/PErr0.tikz');
% load('data/D20.mat');
% powerError(Data);
% matlab2tikz('../../../../tex/Dok/img/PErr40.tikz');
end

