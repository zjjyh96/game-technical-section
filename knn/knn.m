function y = knn(X, X_train, y_train, K)
%KNN k-Nearest Neighbors Algorithm.
%
%   INPUT:  X:         testing sample features, P-by-N_test matrix.
%           X_train:   training sample features, P-by-N matrix.
%           y_train:   training sample labels, 1-by-N row vector.
%           K:         the k in k-Nearest Neighbors
%
%   OUTPUT: y    : predicted labels, 1-by-N_test row vector.
%

N=size(X_train,2);
N_test=size(X,2);
dist=zeros(N,1);
class=unique(y_train);
y=zeros(1,N_test);
for i=1:N_test
    count=zeros(size(class,2),1);
    % calculate the distance
    for j=1:N
        dist(j)=norm(X(:,i)-X_train(:,j));
    end
    % find the k nearest neighbors 
    [d,index]=sort(dist);
    for j=1:K
        tempi=find(class==y_train(index(j)));
        count(tempi)=count(tempi)+1;
    end
    % choose the most-counted label
    [num,ind]=max(count);
    y(i)=class(ind);
end
end
