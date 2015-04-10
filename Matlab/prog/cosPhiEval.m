function [ PFerr, PFrel, PFref] = cosPhiEval(Data,do_plot,Kap)
%close all;
set_cnt = length(Data);
x = 1:length(Data{12}.cos);


switch Kap
    case 4
        PFref = [0.01, 0.75, 0.77, 0.80, 0.92, 0.93, 0.96, 0.96, 0.98, 0.98, 0.99, 0.99];
    case 3
        PFref = [0.01, 0.19, 0.84, 0.86, 0.95, 0.95, 0.97, 0.98, 0.99, 0.99, 1.00, 1.00];
    case 2
        PFref = [0.00, 0.26, 0.91, 0.92, 0.97, 0.98, 0.99, 0.99, 0.99, 0.99, 1.00, 1.00];
    case 1
        PFref = [0.00, 0.98, 0.98, 0.99, 0.99, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00];
    case 0
        PFref = ones(1, 12);
end

PF = zeros(set_cnt,length(Data{12}.cos));

PFerr = zeros(size(PF));

for i = 1:set_cnt
   PF(i,:) = Data{i}.cos / 1000;
   for j = x
      PFerr(i,j) = PF(i,j) - PFref(i);
   end
end

PFrel = ones(size(PF)) * Inf;
for i = 2:set_cnt
   for j = x
       PFrel(i,j) = (PFerr(i,j) / PFref(i)) * 100;
   end
end



if(do_plot)
    figure;
    set(gca,'ColorOrder',jet(set_cnt)) 
    hold all
    for i = 1:set_cnt
        plot(x,PF(i,:));
    end
    
    for i = 1:set_cnt
        plot(x,ones(size(x))*PFref(i),'k--');
    end
    xlabel('Messwert Nr.');
    ylabel('Wirkfaktor');
%     figure;
%     set(gca,'ColorOrder',jet(set_cnt)) 
%     hold all
%     for i = 1:set_cnt
%         plot(x,PFerr(i,:));
%     end
    
%     figure;
%     set(gca,'ColorOrder',jet(set_cnt)) 
%     hold all
%     for i = 1:set_cnt
%         plot(x,PFrel(i,:));
%     end
    
end

end

