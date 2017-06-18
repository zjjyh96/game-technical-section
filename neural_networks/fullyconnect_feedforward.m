function [out] = fullyconnect_feedforward(in,  weight, bias)
%The feedward process of fullyconnect
%   input parameters:
%       in      : the intputs, shape: [number of images, number of inputs]
%       weight  : the weight matrix, shape: [number of inputs, number of outputs]
%       bias    : the bias, shape: [number of outputs, 1]
%
%   output parameters:
%       out     : the output of this layer, shape: [number of images, number of outputs]

% TODO
n_img=size(in,1);
n_out=size(weight,2);
out=zeros(n_img,n_out);

for i=1:n_img
    for j=1:n_out
        out(i,j)=in(i,:)*weight(:,j);   
        out(i,j)=out(i,j)+bias(j);
    end 
end

end

