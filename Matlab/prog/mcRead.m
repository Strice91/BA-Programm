function [ Data,U,I ] = mcRead(PORT,samples,maxSet)

UART = uart();          % UART Object
UART.open(PORT);        % Open UART connection


for set_cnt = 1:maxSet
    while 1
        
        fprintf(sprintf('Measuring Data Set %d\n',set_cnt));
        input('Start Measurement with Enter');
        
        [Data{set_cnt},U{set_cnt},I{set_cnt}] = UART.readCompleteString(samples);
        
        fprintf('Measurement complete\n');
        
        
        if set_cnt ~= maxSet
            prompt = 'Type y for next Measurement: ';
        else
            prompt = 'Type y to exit: ';
        end
        result = input(prompt,'s');
        if strcmp(result,'y')
            break;
        end
    end
end


end

