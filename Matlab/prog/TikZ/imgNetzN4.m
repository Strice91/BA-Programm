function imgNetzN4()

close all;
csv = xlsread('data\Netzdaten\Kurvenform EMA N4.CSV');

U = csv(:,1:3);
I = csv(:,4:6);
x = (1:length(U(:,1))) / 250 * 40;
mU = mean(U(:,1));
mI = mean(I(:,1));

for i = 1:3
    U(:,i) = (U(:,i) - mean(U(:,i)));
    U(:,i) = U(:,i) / max(max(U(:,i))) * 230;
    I(:,i) = (I(:,i) - mean(I(:,i)));
    I(:,i) = I(:,i) / max(max(I(:,i))) * 206;
end


figure;
hold all;
plot(x,U(:,1),'b')
plot(x,U(:,2),'r')
plot(x,U(:,3),'g')
plot(x,I(:,1),'b:')
plot(x,I(:,2),'r:')
plot(x,I(:,3),'g:')
legend('U1','U2','U3','I1','I2','I3');
xlabel('t [ms]')
ylabel('[V] | [A]');
matlab2tikz
end

