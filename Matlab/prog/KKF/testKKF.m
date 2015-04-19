%clear all;
%close all;
function testKKF(fsfaktor,color)
%=================
%   Einstellungen
%=================
n=1;                %Anzahl Perioden
f=50;               %Signalfrequenz
fs=f*fsfaktor;      %Abtastfrequenz
phiGRAD = 40;       %Gewuenschte Phasenverschiebung in GRAD

%=================
%   Konstanten
%=================
radToGrad = 180/pi;
gradToRad = 1/radToGrad;
%=================
%   Berechnungen
%=================
T=1/f;              %Periodendauer
ts=1/fs;            %Abtastdauer
t=0:ts:(T*n - ts);
phiRAD = phiGRAD * gradToRad;

x1=sin(2*pi*f*t);
x2=sin(2*pi*f*t - phiRAD);

corr = conv(x1,x2);             %Faltung
tCorr = [fliplr(-t(2:end)) t];  %Zeitvektor fuer Faltung

%h=figure('Name','Kreuzkorreltation zweier Signale');
maxCorrAmp = max(abs(corr));                %Absoluter Maximalwert der Kreuzkorrelation
[i,j,v] = find(abs(corr) == maxCorrAmp);    %Verschiebung suchen
deltaT = tCorr(j+1);                          %Verschiebung berechnen

phiCalcRad = 2*pi*f*deltaT;                  %aus KK berechnete Phase
phiCalcGrad = phiCalcRad * radToGrad;        %in Grad
phiErr = abs(phiCalcGrad-phiGRAD);            %Phasen-Fehler

%=================
%   Plots
%=================
%subplot(2,1,1);
%plot(t,x1,t, x2); 
%legend('Input signal 1',' Input signal 2');
%grid on;

%subplot(2,1,2);
plot(tCorr*1000,corr,color,'LineWidth',2);
err= phiErr/phiGRAD;
text(tCorr(j)*1000, corr(j), strcat('\leftarrow \Deltat = ', num2str(deltaT,'%.4f'),...
    ' Err=', num2str(err*100,'%2.0f'), '%'), 'FontSize', 10);
%legend('Crosscorrelation');
%grid on;
ylim([-60,30]);
%=================
%   Cmd
%=================
fprintf('delta_T =  %f s\n',deltaT);
fprintf('phiCalcGrad =  %f °\n',phiCalcGrad);
fprintf('phiErr =  %f °\n',phiErr);
end