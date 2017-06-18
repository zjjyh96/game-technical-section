function digits = hack(img_name)
%HACK Recognize a CAPTCHA image
%   Inputs:
%       img_name: filename of image
%   Outputs:
%       digits: 1x5 matrix, 5 digits in the input CAPTCHA image.

load('hack_data');
% YOUR CODE HERE

X_test=im2double(X_test);
X_train=im2double(X_train);
K = [1 10 100];
for i = 1:length(K)
    y=knn(X_test, X_train, y_train, K);
    fprintf('K=%d, numbers are:',K(i));
    for j=1:25
        fprintf('%d',y(j));
        if mod(j,5)==0
           fprintf(' '); 
        end
    end
    fprintf('\n');
end

end