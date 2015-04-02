function imgMinMax()
close all;
u = genSinus(3.2, 2, 100, 0, 1, 0);
i = genSinus(1.76, 2, 100, pi/3, 1, 0);

[peakU,indexU] = findpeaks(u);
[peakI,indexI] = findpeaks(i);

figure;
hold on
plot(u,'r');
plot(i,'g--');
ylim([-3.5 3.5])
plot(indexU,peakU,'r*')
plot(indexI,peakI,'g*')
box on
legend('u(t)','i(t)');
text(indexU+2, peakU+0.1, 'Max U')
text(indexI+2, peakI+0.1, 'Max I')
text(indexU,mean([peakU,peakI]),'\leftarrow  \Deltat  \rightarrow', 'FontSize', 10);
end