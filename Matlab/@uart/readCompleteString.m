function [Data,U,I] = readCompleteString(obj,samples)

% Flush the data in the input buffer.
flushinput(obj.Device);

    fprintf('Read Set:  ')
    for s = 1:samples
        fprintf(sprintf('\b\b%2d',s));
        
        obj.checkStart();
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
        
        input_cnt = 0;
        
        while 1
            read = fscanf(obj.Device, '%s\n');
            if strcmp(read,obj.EndString)
                break;
            else
                input_cnt = input_cnt + 1;
                read_array{input_cnt} = read;
            end
        end 
        
        if input_cnt
            data = zeros(input_cnt,1);
            for x = 1:input_cnt
                data(x) = str2num(read_array{x});
            end
            U{s} = uint16(data(1:input_cnt/2));
            I{s} = uint16(data(input_cnt/2 + 1:end));
        else
            data = 0;
        end
        
    end
    fprintf('\n')
end