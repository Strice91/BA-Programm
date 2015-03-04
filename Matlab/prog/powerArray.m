data_set_vec = 1:length(U);

P = zeros(length(U),1);
S = zeros(length(U),1);
cosPhi = zeros(length(U),1);

for i = data_set_vec
   [S(i), P(i), cosPhi(i)] = getPower(U{i},I{i});  
end

Phi = acosd(cosPhi);

figure;

subplot(2,3,[1;4]);
plot(data_set_vec,P)
title('P');
subplot(2,3,[2;5]);
plot(data_set_vec,S)
title('S');
subplot(2,3,3);
plot(data_set_vec,cosPhi);
title('cosPhi');
subplot(2,3,6);
plot(data_set_vec,Phi);
title('Phi');