function [ Urms, Irms ] = getRMS(U,I)

smp_cnt = length(U);

[UsqSum,IsqSum,Psum] = getSums(U,I);

Urms = uint32(sqrt(double(UsqSum/smp_cnt)));
Irms = uint32(sqrt(double(IsqSum/smp_cnt)));

end

