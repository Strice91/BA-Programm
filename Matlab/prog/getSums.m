function [ UsqSum, IsqSum, Psum] = getSums(U,I)

smp_cnt = length(U);

UsqSum = 0;
IsqSum = 0;
Psum = 0;

U_mean = int16(mean(U));
I_mean = int16(mean(I));


for i = 1:smp_cnt
   u_temp = int32(int16(U(i)) - U_mean);
   i_temp = int32(int16(I(i)) - I_mean);
   
   p_temp = int64(u_temp) * int64(i_temp);
   
   UsqSum = UsqSum + uint64(u_temp * u_temp);
   IsqSum = IsqSum + uint64(i_temp * i_temp);
   Psum = Psum + p_temp;
end

