function [ out ] = relu_feedforward( in )
%The feedward process of relu
%   inputs:
%           in	: the input, shape: any shape of matrix
%   
%   outputs:
%           out : the output, shape: same as in

% TODO

[N,M]=size(in);
out=in;
for i=1:N
    for j=1:M
        if out(i,j)<0
            out(i,j)=0;
        end
    end
end

end

