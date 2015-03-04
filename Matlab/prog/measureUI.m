function [ U,I ] = measureUI(PORT)

UART = uart();
UART.open(PORT);

prompt = 'Type y for next Measurement: ';

for i = 1:7

    while 1
        if i ~= 7
            prompt = 'Type y for next Measurement: ';
        else
            prompt = 'Type y to exit: ';
        end
        
        fprintf(sprintf('Measuring Data Set %d\n',i));
        input('Start Measurement with Enter');
        
        [U{i},I{i}] = UART.read();
        
        fprintf('Measurement complete\n');
        
        l_U = length(U{i});
        l_I = length(I{i});
        
        mean_U = mean(U{i});
        mean_I = mean(I{i});
        
        max_U = max(U{i});
        max_I = max(I{i});
        
        min_U = min(U{i});
        min_I = min(I{i});
        
        fprintf(sprintf('%d values for U, %d values for I\n',l_U,l_I));
        fprintf(sprintf('U_mean = %.2f, I_mean = %.2f\n',mean_U,mean_I));
        fprintf(sprintf('U_max  = %.2f, I_max  = %.2f\n',max_U,max_I));
        fprintf(sprintf('U_min  = %.2f, I_min  = %.2f\n',min_U,min_I));
        fprintf('\n');
        
        result = input(prompt,'s');
        if strcmp(result,'y')
            break;
        end
    end
end

info.Vref = 2.56;
info.smp_freq = 1000;
info.Dif_R1 = 1000000;
info.Dif_R2 = 33000;
info.date = datestr(date);

prompt = 'Enter filename to save Measurement: ';
filename = input(prompt,'s');
path = fullfile('data',filename);
save(path,'U','I','info')



UART.close();

end

