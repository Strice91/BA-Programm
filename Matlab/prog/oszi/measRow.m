function [U,I,timediff] = measRow(channels,rows)

for r = 1:rows
    while 1
        if r ~= rows
            prompt = 'Type y for next Measurement: ';
        else
            prompt = 'Type y to exit: ';
        end
        
        fprintf(sprintf('Measuring Data Set %d\n',r));
        input('Start Measurement with Enter');
        
        [d,timediff{r}] = readWaveform(channels);
        I{r} = d{1};
        U{r} = d{2};
        
        l = 1:length(U{r});
        plotyy(l,U{r},l,I{r});
        
        result = input(prompt,'s');
        if strcmp(result,'y')
            break;
        end
    end       
end

% Save measurement
prompt = 'Enter filename to save Measurement: ';
filename = input(prompt,'s');
if filename
path = fullfile('data',filename);
save(path,'U','I','timediff')
end

end

