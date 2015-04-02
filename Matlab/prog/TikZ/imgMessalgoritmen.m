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

criteria = {'Komplexitaet','Robustheit','Genauigkeit','Speicherlast','Rechenzeit','Features'};
names = {   'Min/Max','Goerzel','KKF','RMS'};

mm = [ -3, 3, 1, -1, -1, 2];
go = [ -9, 7, 4, -7, -9, 5];
kk = [ -5, 7, 3, -9, -9, 1];
rm = [ -3, 5, 6, -1, -2, 3];

data = [mm',go',kk',rm'];

%data = rand(6,4)*10 - 5;     
color = {'r','y','g','b'};
tle = 'Messalgorithmen';
rng = [0;10;10;0;0;10];
spider(data,tle,rng,criteria,names,color);
end