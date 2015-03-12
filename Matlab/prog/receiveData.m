function [ Data ] = receiveData(PORT,samples,MeasRows)

UART = uart();          % UART Object
UART.open(PORT);        % Open UART connection

if nargin > 2
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
        
        [Data{i}] = UART.readDataString(samples);      % Read Data from µC
        
        fprintf('Measurement complete\n');
        
        names = fieldnames(Data{i});
        name_cnt = length(names);
        
        l = zeros(name_cnt,1);
        for x = 1:name_cnt
            l(x) = length(Data{i}.(names{x}));
        end
        
        if all(l == samples)
            fprintf('Samples complete OK!\n');
        else
            fprintf('Samples incomplete FAIL!\n');
        end
        
        fprintf(sprintf('Received %d Set with %d Datatypes\n',min(l),name_cnt));
        fprintf('\n');
        
        result = input(prompt,'s');
        if strcmp(result,'y')
            break;
        end
    end
end

% Information about the measurement conditions
%info.Vref = 2.56;
%info.smp_freq = 1000;
%info.Dif_R1 = 18000;
%info.Dif_R2 = 570;
%info.date = datestr(date);

% Save measurement
prompt = 'Enter filename to save Measurement: ';
filename = input(prompt,'s');
if filename
    path = fullfile('data',filename);
    save(path,'Data')
end


UART.close();       % Close the UART connection

end

