function [ data, timediff ] = readWaveform(channels)

% Find a VISA-USB object.
obj1 = instrfind('Type', 'visa-usb', 'RsrcName', 'USB0::0x1AB1::0x04CE::DS1ZA165260837::0::INSTR', 'Tag', '');

% Create the VISA-USB object if it does not exist
% otherwise use the object that was found.
if isempty(obj1)
    obj1 = visa('NI', 'USB0::0x1AB1::0x04CE::DS1ZA165260837::0::INSTR');
else
    fclose(obj1);
    obj1 = obj1(1);
end

% Configure instrument object, obj1

set(obj1, 'InputBufferSize', 650000);

% Configure instrument object, obj1

set(obj1, 'OutputBufferSize', 512);

% Connect to instrument object, obj1.
fopen(obj1);

fprintf(obj1, ':STOP');
fprintf(obj1, ':WAV:FORM ASC');
fprintf(obj1, ':WAV:SOUR CHAN2');
%fprintf(obj1, ':WAV:MODE NROM');

chan_num = length(channels);

for c = 1:chan_num
    switch channels(c)
        case 1
            chanName = 'CHAN1';
        case 2
            chanName = 'CHAN2';
        case 3
            chanName = 'CHAN3';
        case 4
            chanName = 'CHAN4';
    end
    fprintf(obj1, [':WAV:SOUR ',chanName]);
    
    read = query(obj1, ':WAV:DATA?');
    read = read(12:end);
    array = strsplit(read,',');
    readNum = length(array);
    
    d = zeros(readNum,1);
    for i = 1:readNum
        d(i) = str2double(array{i});
    end
    
    
    data{c} = d;
end

% Read Time difference between x values
timediff = str2num(query(obj1, ':WAV:XINC?'));

fprintf(obj1, ':RUN');

% Disconnect from instrument object, obj1.
fclose(obj1);

end

