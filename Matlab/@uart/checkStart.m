function [ start ] = checkStart(obj)

read = '';
start = 0;
while ~strcmp(read,obj.StartString)
    read = fscanf(obj.Device, '%s\n');
end
start = 1;

end

