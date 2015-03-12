function [ UsqSum, IsqSum, Psum] = getSums(U,I)

smp_cnt = length(U);

UsqSum = 0;
IsqSum = 0;
Psum = 0;

U_mean = int16(mean(U));
I_mean = int16(mean(I));

AInv = 0.9376;
Betha = 0.1022;
u_old = int32(U_mean);

for i = 1:smp_cnt
   u_temp = int32(int16(U(i)) - U_mean);
   i_temp = int32(int16(I(i)) - I_mean);
   u_temp = int32(AInv * (double(u_temp) + Betha * double(u_old)));
   
   %u_temp = int32(int16(U(i)));
   %i_temp = int32(int16(I(i)));
   
   p_temp = int64(u_temp) * int64(i_temp);
   
   UsqSum = UsqSum + uint64(u_temp * u_temp);
   IsqSum = IsqSum + uint64(i_temp * i_temp);
   Psum = Psum + p_temp;
end

