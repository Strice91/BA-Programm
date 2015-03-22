% Dieses Script analysiert die Signaleigenschaften wie, snr, thd, sinad, sfdr 
% und enob.
% load JitterCorrectedData_0.txt;
signal = double(U{10}');
numberOfSamples = length(signal);
samplingRate = 500;
maxNumberOfHarmonics = 5;
harmonicWidth = 9; % breite der Peaks

% Spektrum berechen
window = blackman(numberOfSamples);
signal = signal(:,1);
signal = signal .* window;
signal = abs(fft(signal));
signal = signal(1:numberOfSamples/2);

% DC und erste Harmonische suchen. Der grösste Wert, ausser DC, wird als erste 
% Harmonische gedeutet.
levels = signal(1);
positions = 0;
[level, positionH1] = max(signal(2:numberOfSamples/2));
positionH1 = positionH1;
levels = [levels level];
positions = [positions positionH1];

% Alle anderen Harmonischen finden.
currentPosition = 2 * positionH1;
while currentPosition-2 < numberOfSamples/2 && length(levels) < maxNumberOfHarmonics
  [level, lastPosition] = max(signal(currentPosition-1:min(currentPosition+2, numberOfSamples/2)));
  lastPosition = lastPosition + currentPosition - 3;
  levels = [levels level];
  positions = [positions lastPosition];
  currentPosition = currentPosition + positionH1;
end;

% Pegels skalieren damit die 1. Harmonische eins beträgt.
levelScalingFactor = 1 / levels(2);
levels = levels * levelScalingFactor;
signal = signal * levelScalingFactor;

% Noise vom Signal trennen und Leistungen der Harmonischen berechnen.
noiseMasked = signal;
harmonicWidth2 = ceil(harmonicWidth/2);
noiseMasked(1:harmonicWidth2) = zeros(1,harmonicWidth2)*-1;
powers = sum(signal(1:harmonicWidth2).^2);
for i=2:length(positions)
  from = positions(i) - harmonicWidth2 + 2;
  to = from + harmonicWidth - 1;
  noiseMasked(from:to) = zeros(1,harmonicWidth)*-1;
  power = sum(signal(from:to).^2);
  powers = [powers power];
end;

% Lehrstellen aus dem noiseMasked Vektor entfernen.
noiseContinuous = [];
for i=1:length(noiseMasked)
  if noiseMasked(i) ~= 0
    noiseContinuous = [noiseContinuous; noiseMasked(i)];
  end;
end;

% snr, thd, sinad, sfdr und enob berechnen.
noisePower = sum(noiseContinuous.^2);
signalPower = powers(2);
harmonicsPower = sum(powers(3:end));

snr = 10*log10(signalPower/noisePower);
thd = 10*log10(harmonicsPower/signalPower);
sinad = 10*log10(signalPower/(noisePower+harmonicsPower));

[highestHarmonicsLevel highestHarmonicsPosition] = max(levels(3:end));
[highestNoiseLevel highestNoisePosition] = max(noiseMasked);
sfdr = mag2db(levels(2)/max([highestHarmonicsLevel highestNoiseLevel]));
enob = (sinad - 1.76) / 6.02;

% Resultate ausgeben.
disp(['SNR    = ' num2str(snr) ' dB']);
disp(['THD    = ' num2str(thd) ' dB']);
disp(['SINAD  = ' num2str(sinad) ' dB']);
disp(['SFDR   = ' num2str(sfdr) ' dB']);
disp(['ENOB   = ' num2str(enob) ' bit']);

% Plotten.
xScalingFactor = samplingRate/numberOfSamples;
x = linspace(0,samplingRate/2-xScalingFactor,numberOfSamples/2);
plot(x, mag2db(signal));
hold on
plot(x, mag2db(noiseMasked), 'LineWidth', 3);
plot(0, mag2db(levels(1)), 'rs');
plot(positions(2)*xScalingFactor, mag2db(levels(2)), 'rv');
plot(positions(3:end)*xScalingFactor, mag2db(levels(3:end)), 'ro');
plot((highestNoisePosition-1)*xScalingFactor, mag2db(highestNoiseLevel), 'rd');
hold off;

legendText = num2str(round(mag2db(1/levels(3))));
for i=4:length(levels)
  legendText = [legendText  ', ' num2str(round(mag2db(1/levels(i))))];
end;

legend('signal', ...
       'noise', ...
       ['dc component ' num2str(round(mag2db(1/levels(1)))) ' dBc'], ...
       'fundamental signal', ...
       ['harmonics ' legendText ' dBc'], ...
       ['highest spur ' num2str(round(mag2db(1/highestNoiseLevel(1)))) ' dBc']);

title('Frequency Domain Analysis');
xlabel('Frequency [Hz]');
ylabel('Level [dB]');
set(gca,'YLim',[-80 20]);

