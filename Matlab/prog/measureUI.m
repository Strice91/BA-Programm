function [ U,I ] = measureUI(PORT,MeasRows)

UART = uart();          % UART Object
UART.open(PORT);        % Open UART connection
if nargin > 1
    max_read = MeasRows;
else
    max_read = 12;          % Number of Measurements
end



for i = 1:max_read

    while 1
        if i ~= max_read
            prompt = 'Type y for next Measurement: ';
        else
            prompt = 'Type y to exit: ';
        end
        
        fprintf(sprintf('Measuring Data Set %d\n',i));
        input('Start Measurement with Enter');
        
        [U{i},I{i}] = UART.read();      % Read Data from µC
        
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
        fprintf(sprintf('U_mean = %3.2f, I_mean = %3.2f\n',mean_U,mean_I));
        fprintf(sprintf('U_max  = %3.2f, U_min  = %3.2f\n',max_U,min_U));
        fprintf(sprintf('I_max  = %3.2f, I_min  = %3.2f\n',max_I,min_I));
        fprintf('\n');
        
        result = input(prompt,'s');
        if strcmp(result,'y')
            break;
        end
    end
end

% Information about the measurement conditions
info.Vref = 2.56;
info.smp_freq = 1000;
info.Dif_R1 = 18000;
info.Dif_R2 = 570;
info.date = datestr(date);

% Save measurement
prompt = 'Enter filename to save Measurement: ';
filename = input(prompt,'s');
path = fullfile('data',filename);
save(path,'U','I','info')

UART.close();       % Close the UART connection

end

