function [ sig ] = genTestSignal( w, amp, phase, n )

sig = amp*sin(w*(0:n)+phase);

end

