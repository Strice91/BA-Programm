function [ ] = cosPhiError(Data,Kap)
close all;


[PFErr, PFRel, PFref] = cosPhiEval(Data,0,Kap);

meanErr = mean(PFErr,2);
meanRel = mean(PFRel,2);

figure;
[AX,H1,H2] = plotyy(PFref,meanErr,PFref,meanRel);
set(H1,'Color','b','Marker','x') 
set(H2,'Color','g','Marker','x') 
text(-0.1,0.,'Err Absolut','rotation',90,'color','b')
text(1.05,0,'Err [%]','rotation',90,'color',[0 0.502 0])
xlabel('Wirkfaktor');
grid on;
end

