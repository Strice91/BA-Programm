function [Data] = readDataString(obj,samples)

% Flush the data in the input buffer.
flushinput(obj.Device);

    fprintf('Read Set:  ')
    for s = 1:samples
        fprintf(sprintf('\b\b%2d',s));
        
        % Read the Serial Port
        read = fscanf(obj.Device, '%s\n');
        % Split Array after each |
        raw_array = strsplit(read,'|');
        % Odd strings are names
        names = raw_array(1:2:end-1);
        % Even strings are values
        values = raw_array(2:2:end-1);

        len = length(names);
        % make Vectors for each name
        % Data.NAME = [V1,V2,V3, ...]
        for i = 1:len
            Data.(names{i})(s) = str2num(values{i});
        end
    end
    fprintf('\n')
end