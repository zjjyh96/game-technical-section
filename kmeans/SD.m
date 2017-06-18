function [ sd ] = SD( X, idx, ctrs )
%SD calculate the sum of distances from each point to its respective centroid
%   Input: X - data point features, n-by-p maxtirx.
%          idx  - cluster label
%          ctrs - cluster centers, K-by-p matrix.

[N,P]=size(X);
sd=0;
for i=1:N
    sd=sd+norm(X(i,:)-ctrs(idx(i),:));
end


end

