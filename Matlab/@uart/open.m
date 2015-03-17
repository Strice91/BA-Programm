function open(obj,Port)

obj.Port = Port;

% Find a serial port object.
serial_obj = instrfind('Type', 'serial', 'Port', obj.Port, 'Tag', '');

% Create the serial port object if it does not exist
% otherwise use the object that was found.
if isempty(serial_obj)
    serial_obj = serial(obj.Port);
else
    fclose(serial_obj);
    serial_obj = serial_obj(1);
end

obj.Device = serial_obj;

obj.configure('StopBits', 2.0);
obj.configure('InputBufferSize', 65536);
obj.configure('BaudRate', 115200);

obj.StartString = 'S';
obj.DataIdentifier = 'D';
obj.EndString = 'E';

fopen(obj.Device);

end

