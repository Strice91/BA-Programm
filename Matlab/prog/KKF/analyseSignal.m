function [ w, amp, phase ] = analyseSignal( sig )

n=length(sig);
%sig(n-1)+sig(n+1)=2*cos(w)*sig(n);
s1=sig(1:n-2)+sig(3:n);
s2=sig(2:n-1);
% Regression s1 auf s2
M= [s2.' ones(length(s1),1)];
coff=inv(M'*M)*M'*s1.';
w=acos(coff(1)/2);

M=[cos((0:n-1)*w).' sin((0:n-1)*w).'];
coff=inv(M'*M)*M'*sig.';

cc=coff(2)+j*coff(1);
amp=abs(cc);
phase=angle(cc);

end

