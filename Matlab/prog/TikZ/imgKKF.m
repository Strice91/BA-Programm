function imgKKF()
close all;
f = figure;
testKKF(20,'r')
hold on
testKKF(100,'b')
legend('fs = 20*f','fs = 100*f','Location','southwest')
text(-15,-10,'\Deltat ref = 0.0022');
text(-15,-15,'phi = 40deg')
ylabel('Kreuzkorrelation')
xlabel('t [ms]')
%matlab2tikz('../../../../tex/Dok/img/kkf.tikz');
print(f,'-dpng','KKF.png')
end

