function imgMaximum()
close all;
u = genSinus(3.2, 2, 100, 0, 1, 0);
i = genSinus(1.76, 2, 100, pi/3, 1, 0);

[peakU,indexU] = findpeaks(u);
[peakI,indexI] = findpeaks(i);

u(end) = [];
i(end) = [];
indexU = indexU * 0.4;
indexI = indexI * 0.4;
x = (1:length(u)) * 0.4;

figure;
hold on
plot(x,u,'r','LineWidth',2);
plot(x,i,'g--','LineWidth',2);
ylim([-3.5 3.5])
plot(indexU,peakU,'r*')
plot(indexI,peakI,'g*')
box on
legend('u(t)','i(t)');
text(indexU+2, peakU+0.1, 'Max U')
text(indexI+2, peakI+0.1, 'Max I')
text(indexU,mean([peakU,peakI]),'\leftarrow  \Deltat  \rightarrow', 'FontSize', 10);
ylabel('Signalverlauf [V]');
xlabel('t [ms]');

matlab2tikz('../../../../tex/Dok/img/maximum.tikz');
end