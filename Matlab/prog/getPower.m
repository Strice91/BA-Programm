function [ S,P,cosPhi ] = getPower(U,I)

smp_cnt = length(U);
[ UsqSum, IsqSum, Psum] = getSums(U,I);
[ Urms, Irms ] = getRMS(U,I);

S = uint32(uint64(Urms) * uint64(Irms));
%S = Urms * Irms;
P = int32(Psum/smp_cnt)*100;

if P > S
    P = int32(S);
elseif P < -S
    P = - int32(S);
end
    
%cosPhi = double(P) / double(S);
cosPhi = int16(1000*double(P)/double(S));

end

