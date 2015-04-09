function [ Perr, Prel ] = powerEval(Data,do_plot,Pref)
close all;
max_Power = 47;
max_mean_P = mean(Data{12}.P);
set_cnt = length(Data);
x = 1:length(Data{12}.P);

if nargin < 3
Pref = [0.00, 1.27, 10.16, 11.32, 19.26, 20.40, 27.80, 28.74, 35.70,...
        36.60, 46.10, 47.10];
end

% Pref = [0.05, 1.32, 10.18, 11.33, 19.40, 20.53, 27.90, 28.90, 35.70,...
%         36.80, 46.40, 47.30];
    
P = zeros(set_cnt,length(Data{12}.P));   
Perr = zeros(size(P));
for i = 1:set_cnt
   P(i,:) = Data{i}.P / max_mean_P * max_Power;
   for j = x
      Perr(i,j) = P(i,j) - Pref(i);
   end
end

Prel = zeros(size(P));
for i = 2:set_cnt
   for j = x
       Prel(i,j) = (Perr(i,j) / Pref(i)) * 100;
   end
end

if(do_plot)
    figure;
    set(gca,'ColorOrder',jet(set_cnt)) 
    hold all
    for i = 1:set_cnt
        plot(x,P(i,:));
    end

    for i = 1:set_cnt
        plot(x,ones(size(x))*Pref(i),'k--');
    end

    figure;
    set(gca,'ColorOrder',jet(set_cnt)) 
    hold all
    for i = 1:set_cnt
        plot(x,Perr(i,:));
    end

    figure;
    set(gca,'ColorOrder',jet(set_cnt))
    hold all
    for i = 1:set_cnt
        plot(x,Prel(i,:));
    end    
end

end

