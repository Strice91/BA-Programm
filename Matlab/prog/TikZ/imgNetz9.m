function imgNetz9()

close all;
csv = xlsread('data\Netzdaten\Kurvenform EMA BAU 9.CSV');

U = csv(:,1:3);
I = csv(:,4:6);
x = (1:length(U(:,1))) / 250 * 40;
mU = mean(U(:,1));
mI = mean(I(:,1));

for i = 1:3
    U(:,i) = (U(:,i) - mean(U(:,i))) * 2.3;
    I(:,i) = (I(:,i) - mean(I(:,i)));
    I(:,i) = I(:,i) / max(max(I(:,i))) * 160;
end

I(:,3) = -I(:,3);


figure;
hold all;
plot(x,U(:,2),'b')
plot(x,U(:,1),'r')
plot(x,U(:,3),'g')
plot(x,I(:,2),'b:','LineWidth',2)
plot(x,I(:,1),'r:','LineWidth',2)
plot(x,I(:,3),'g:','LineWidth',2)
legend('U1','U2','U3','I1','I2','I3');
xlabel('t [ms]')
ylabel('[V] | [A]');

matlab2tikz('../../../../tex/Dok/img/TUM9.tikz');
end

