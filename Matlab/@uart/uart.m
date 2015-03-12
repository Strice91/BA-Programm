classdef uart < handle
    
    properties
        Port
        StopBits
        InputBufferSize
        BaudRate
        MaxRead
        Device
        StartString
        EndString
    end
    
    methods
        open(obj,Port)
        close(obj)
        configure(obj,property,value)
        [U,I] = readUI(obj)
        [Data] = readDataString(obj,samples)
        checkStart(obj)
    end
    
end

