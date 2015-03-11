function [SX,PX,Ur,Ir,Dif] = digitShift(U,I)

smp_cnt = length(U);

[Usq,Isq,Psum] = getSums(U,I);

%Urms = zeros(9,1);
%Irms = zeros(9,1);

for i = 0:2:10
    Ur((i/2)+1) = uint32(sqrt(double(Usq/smp_cnt)));
    Ir((i/2)+1) = uint32(sqrt(double(bitshift(Isq,i)/smp_cnt)));
    PX((i/2)+1) = int32(bitshift(Psum,i/2)/smp_cnt);
end

SX = uint32(uint64(Ur) .* uint64(Ir));
%PX = int32(Psum./smp_cnt);
Dif = int32(SX)-PX;

figure;
subplot(3,1,1);
plot(0:2:10,SX,0:2:10,PX)
legend('S','P');
subplot(3,1,2);
plot(0:2:10,Ur,0:2:10,Ir)
legend('Urms','Irms');
subplot(3,1,3);
plot(0:2:10,Dif);
legend('S-P');
end