function imgMessalgoritmen()
close all;
% criteria = {'Komplexitaet','Robustheit','Genauigkeit',...
%             'Speicherlast','Rechenzeit','Features'};
% names = {   'Verfahren1','Verfahren2','Verfahren3',...
%             'Verfahren4','Verfahren5','Verfahren6'};
% %data = [ 1 2 3 4 5 6;
% %         7 8 9 10 11 12.5;];
%      
% data = rand(6,6)*10;     
% bordercolor = {'m','c','r','g','b','y'};
% %fillcolor = {'b','r'};
% fillcolor = bordercolor;
% 
% radarplot(data,criteria,bordercolor,fillcolor,{'b','.'},5);
% set(gcf,'color','w');
% legend(names{:});

criteria = {'Umsetzbarkeit','Robustheit','Genauigkeit','Speichernutzung','Geschwindigkeit','Ergebnisse'};
names = {   'Maximum','Goerzel','KKF','RMS'};

mm = [ 7, 3, 1, 9, 9, 2];
go = [ 1, 7, 4, 3, 1, 5];
kk = [ 5, 7, 3, 1, 1, 1];
rm = [ 7, 5, 6, 9, 8, 3];

data = [mm',go',kk',rm'];

%data = rand(6,4)*10 - 5;     
color = {'r','y','g','b'};
tle = 'Messalgorithmen';
rng = [10;10;10;10;10;10];
f = spider(data,tle,rng,criteria,names,color);
%matlab2tikz('../../../../tex/Dok/img/Messalgorithmen.tikz');
print(f,'-dpng','Messalgorithmen.png')
end