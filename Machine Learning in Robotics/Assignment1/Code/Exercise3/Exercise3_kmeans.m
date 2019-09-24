function Exercise3_kmeans(ges_l,ges_o,ges_x,ini_l,ini_o,ini_x,k)
%set parameter
decrement=1e-6;
%implement k-means to three positions and return the labels
label_l=k_me(ges_l,ini_l,k,decrement);
label_o=k_me(ges_o,ini_o,k,decrement);
label_x=k_me(ges_x,ini_x,k,decrement);
%plot kmeans
plcluster(ges_l,label_l,'k-means-l',k)
plcluster(ges_o,label_o,'k-means-o',k)
plcluster(ges_x,label_x,'k-means-x',k)
end
%% k_means implementation
function label=k_me(samples,cluster,k,st_decre)
label=zeros(size(samples,1),1);   %label for each sample
d=zeros(k,1);                     %distance of sample to each cluster
d_min=zeros(size(samples,1),1);   
J_before=inf;
decrement=inf;
%iteration until decrement under the threshold
while(decrement>=st_decre)
    N=zeros(k,1);    %number of 7 klusters
    %E-step For each data point, find the closest class and label them. 
    for i=1:size(samples,1)
        for j=1:k
            d(j)=sqrt(sum((samples(i,:)-cluster(j,:)).^2));
        end
        [d_min(i),label(i)]=min(d);
        N(label(i))= N(label(i))+1;
    end
    %M-step From the current clusters, update mean vectors   
    for i=1:k
        sum_cluster=0;
        for j=1:size(samples,1)
            if label(j)==i
                sum_cluster=sum_cluster+samples(j,:);
            end
        end
        cluster(i,:)=sum_cluster/N(i);
    end
    %Calculate the total distortion
    J=sum(d_min);
    decrement=J_before-J;
    J_before=J;
end
end

%% plot function
function plcluster(samples,label,name,k)
figure('name',name);
colors = ['b','k','r','g','m','y','c'];
for i=1:k
    plot3(samples((label ==i),1),samples((label ==i),2),samples((label ==i),3),'+','color',colors(i))
    hold on;
end
print(name,'-dpng')
end
