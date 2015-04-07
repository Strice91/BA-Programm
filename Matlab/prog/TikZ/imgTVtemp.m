function imgTVtemp()

close all;
temp = xlsread('TV Temperatur.xlsx');
figure;
plot(temp,'r','LineWidth',2)
hold on
plot(ones(139,1)*217,21:159,'b--')
plot(316:349,ones(34,1)*100,'r:','LineWidth',2)
text(140,147,'L\"ufter AUS');
text(230,147,'L\"ufter AN');
xlabel('t [s]');
ylabel('T [Celsius]');

end

