function [ S,P,cosPhi ] = getPower(U,I)

smp_cnt = length(U);
[ UsqSum, IsqSum, Psum] = getSums(U,I);
[ Urms, Irms ] = getRMS(U,I);

S = uint32(uint64(Urms) * uint64(Irms));
%S = Urms * Irms;
P = int32(Psum/smp_cnt);

cosPhi = double(P) / double(bitsra(S,6));

end

