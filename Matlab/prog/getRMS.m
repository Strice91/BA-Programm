function [ Urms, Irms ] = getRMS(U,I)

smp_cnt = length(U);

[UsqSum,IsqSum,Psum] = getSums(U,I);

%Urms = uint32(sqrt(double(UsqSum/smp_cnt)));
%Irms = uint32(sqrt(double(IsqSum/smp_cnt)));

Urms = sqrt(double(bitshift(UsqSum,0)/smp_cnt));
Irms = sqrt(double(bitshift(IsqSum,0)/smp_cnt));

end

