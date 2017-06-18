nrep=500;

SDmin=9999;
SDmax=0;


for i=1:nrep

fprintf('rep=%d\n',i);
load('kmeans_data.mat');
[idx, ctrs, iter_ctrs]=kmeans(X,2);
sd=SD(X, idx, ctrs);

if sd>SDmax
    SDmax=sd;
    idx_max=idx;
    ctrs_max=ctrs;
    i_ctrs_max=iter_ctrs;
end

if sd<SDmin
    SDmin=sd;
    idx_min=idx;
    ctrs_min=ctrs;
    i_ctrs_min=iter_ctrs;
end

    


end

% kmeans_plot(X, idx_max, ctrs_max, i_ctrs_max);
kmeans_plot(X, idx_min, ctrs_min, i_ctrs_min);
