path='image/Train/CheckCode-';
post='.jpeg';
X_train=[];
y_train=zeros(1,250);
index_y=0;
for i=1:50
    
    pathi=strcat(path,int2str(i));
    pathi=strcat(pathi,post);
    X_temp=extract_image(pathi);
    X_train=[X_train,X_temp];
    show_image(X_temp);
    
    prompt = strcat('What number is this?',int2str(i));
    prompt = strcat(prompt,'\n');
    result = input(prompt,'s');
    for j=1:5
        index_y=index_y+1;
        y_train(index_y)=result(j)-'0';
    end
end

path='image/Test/CheckCode-';
post='.jpeg';
X_test=[];

for i=1:5
  
    pathi=strcat(path,int2str(i));
    pathi=strcat(pathi,post);
    X_temp=extract_image(pathi);
    X_test=[X_test,X_temp];

end

save('hack_data.mat','X_train','y_train','X_test');


