function [U,I] = read(obj)

% Flush the data in the input buffer.
flushinput(obj.Device);

obj.checkStart();

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
    U = uint16(data(1:input_cnt/2));
    I = uint16(data(input_cnt/2 + 1:end));
else
    data = 0;
end



end