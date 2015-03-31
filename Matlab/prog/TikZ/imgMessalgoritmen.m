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

criteria = {'Komplexitaet','Robustheit','Genauigkeit',...
            'Speicherlast','Rechenzeit','Features'};
names = {   'Min/Max','KKF','FFT',...
            'Regression','RMS','ZCD'};
     
data = rand(6,6)*9;     
color = {'m','c','r','g','b','y'};
tle = 'Messalgorithmen';
rng = [10;10;10;10;10;10];
spider(data,tle,rng,criteria,names,color);
end