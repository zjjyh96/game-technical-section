function [idx, ctrs, iter_ctrs] = kmeans(X, K)
%KMEANS K-Means clustering algorithm
%
%   Input: X - data point features, n-by-p maxtirx.
%          K - the number of clusters
%
%   OUTPUT: idx  - cluster label
%           ctrs - cluster centers, K-by-p matrix.
%           iter_ctrs - cluster centers of each iteration, K-by-p-by-iter
%                       3D matrix.

[N,P]=size(X);
ctrs=zeros(K,P);

% random pick k-centers
uni_X=unique(X,'rows');
uni_size=size(uni_X,1);
% fprintf('%d\n',uni_size);
i_ctrs=ceil(uni_size*rand(1,K));
for i=1:K
    ctrs(i,:)=uni_X(i_ctrs(i),:);
end

iter=0;
while (1)
    iter=iter+1;
    iter_ctrs(:,:,iter)=ctrs;
%     fprintf('iter=%d\n',iter);
    
    idx=zeros(N,1);
    for i=1:N
        dis=zeros(K,1);
%         if i>1
%             if X(i,:)==X(i-1,:)
%                 idx(i)=idx(i-1);   
%                 continue;
%             end
%         end
        for j=1:K
            dis(j)=norm(X(i,:)-ctrs(j,:));
        end
        [M,I]=min(dis);
        idx(i)=I;     
    end
    
    center=zeros(K,P);
    
    num=zeros(K,1);
    for i=1:N
        num(idx(i))=num(idx(i))+1;
        center(idx(i),:)=center(idx(i),:)+X(i,:);
    end
    for i=1:K
        center(i,:)=center(i,:)./num(i);
    end
%      fprintf('K1=(%f,%f),K2=(%f,%f),K3=(%f,%f),K4=(%f,%f)\n',center(1,1),center(1,2),center(2,1),center(2,2),center(3,1),center(3,2),center(4,1),center(4,2));

    if sum(norm(center-ctrs))==0
        break;
    end
    
    ctrs=center;

    
end

end
