function [out_sensitivity] = relu_backprop(in_sensitivity, in)
%The backpropagation process of relu
%   input paramter:
%       in_sensitivity  : the sensitivity from the upper layer, shape: 
%                       : [number of images, number of outputs in feedforward]
%       in              : the input in feedforward process, shape: same as in_sensitivity
%   
%   output paramter:
%       out_sensitivity : the sensitivity to the lower layer, shape: same as in_sensitivity

% TODO

[N,J]=size(in_sensitivity);
out_sensitivity=in_sensitivity;

for i=1:N
    for j=1:J
        if in(i,j)<0
            out_sensitivity(i,j)=0;
        end
    end
end

end

