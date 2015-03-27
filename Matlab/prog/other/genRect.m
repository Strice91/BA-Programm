x = 1;
out = zeros(500,1);
for i = 1:500
    if x < 13
        out(i) = 2.52;
    elseif x < 100
        out(i) = 1.1;
    else
        x = 1;
        out(i) = 1.1;
    end
    x = x + 1;
end
out = out + 0.1 * (0.5 - rand(size(out)));