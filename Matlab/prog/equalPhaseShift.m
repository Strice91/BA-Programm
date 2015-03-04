function [ R_out, M_out ] = equalPhaseShift( R, M )

R = double(R);
M = double(M);

[peaksR,locationsR] = findpeaks(R);
[peaksM,locationsM] = findpeaks(M);

firstPeakR = locationsR(1);
firstPeakM = locationsM(1);

R_out = R;
M_out = M;

if firstPeakR > firstPeakM
   peakDist = firstPeakR - firstPeakM + 1;
   R_out = R(peakDist:end-1);
   M_out = M(1:end-peakDist);
else
   peakDist = firstPeakM - firstPeakR + 1;
   M_out = M(peakDist:end-1);
   R_out = R(1:end-peakDist);
end


end

