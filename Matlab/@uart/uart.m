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
        read(obj)
        checkStart(obj)
    end
    
end

