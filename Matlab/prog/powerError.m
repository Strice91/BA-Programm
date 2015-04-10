function [ ] = powerError(Data,Pref)
%close all;

if nargin < 2
Pref = [0.00, 1.27, 10.16, 11.32, 19.26, 20.40, 27.80, 28.74, 35.70,...
        36.60, 46.10, 47.10];
end

[PErr, PRel] = powerEval(Data,0,Pref);

meanErr = mean(PErr,2);
meanRel = mean(PRel,2);

figure;
plotyy(Pref,meanErr,Pref,meanRel);
text(-4,0.4,'Fehler [W]','rotation',90,'color','b')
text(54,0.4,'Fehler [%]','rotation',90,'color',[0 0.502 0])
xlabel('Wirkleistung [W]');
grid on;
end

