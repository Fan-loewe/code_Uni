function Exercise3_nubs(ges_l,ges_o,ges_x,k)
v=[0.08,0.05,0.02];
label_l=nub(ges_l,k,v);
label_o=nub(ges_o,k,v);
label_x=nub(ges_x,k,v);
%plot nubs
plcluster(ges_l,label_l,'nubs-l',k)
plcluster(ges_o,label_o,'nubs-o',k)
plcluster(ges_x,label_x,'nubs-x',k)
end
%% Non-Uniform Binary Split Implementation
function label=nub(samples,K,v)
center=zeros(K,3);

%initailization: set all data as class1,calculate center for all datapoints
center(1,:)=mean(samples);
label=ones(size(samples,1),1);

for k=1:K-1   %after first round, only K-1 iterations left
    J=zeros(k,1);     %distortion for each cluster
    %calculate distortion among current classes
    for i=1:k    
        for j=1:size(samples,1)
            if(label(j)==i)
                d=sqrt(sum((samples(j,:)-center(i,:)).^2));
                J(i)=J(i)+d;
            end
        end
    end        
    %Split the worst class into two subclasses 
    [~,maxdistortion_index]=max(J);
    temp1=(center(maxdistortion_index,:)+v);
    temp2=(center(maxdistortion_index,:)-v);
    for j=1:size(samples,1)
        if(label(j)==maxdistortion_index)
            d1=sqrt(sum((samples(j,:)-temp1).^2));
            d2=sqrt(sum((samples(j,:)-temp2).^2));
            if d1<=d2
                label(j)=k+1;
            end    
        end
    end    
    %Update the code vectors
    center(maxdistortion_index,:) = mean(samples(label==maxdistortion_index,:));
    center(k+1,:) = mean(samples(label==k+1,:));  
    
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

