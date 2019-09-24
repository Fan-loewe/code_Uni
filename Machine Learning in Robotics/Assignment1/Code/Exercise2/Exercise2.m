function [opt_d,err,conf_matr]=Exercise2(dmax)
%import data
train_images = loadMNISTImages('train-images.idx3-ubyte');
train_labels = loadMNISTLabels('train-labels.idx1-ubyte');
test_images = loadMNISTImages('t10k-images.idx3-ubyte');
test_labels = loadMNISTLabels('t10k-labels.idx1-ubyte');
%imshow(reshape(images(:,1),28,28));

for d=1:dmax
    %%PCA
    mu = mean(train_images,2);
    train_images = train_images - mu;
    test_images = test_images - mu;
    C = cov(train_images');
    [V,~] = eig(C);  %eigenvectors from left ro right with eigenvalues from smallest to largest
    V = fliplr(V);   %let largest eigenvectors on the left, smallest on the right
    W = V(:,1:d);
    %project training and testing dataset to the basis with d principal components 
    Pro_train = W'* train_images;
    Pro_test = W'* test_images;
    %%Gaussian classifier for digital class 0-9
    for i=1:10
        ea_train = Pro_train(:,train_labels==(i-1));
        ea_mu{i} = mean(ea_train,2);
        ea_C{i} = cov((ea_train-ea_mu{i})');
        likeli(i,:) = mvnpdf(Pro_test',ea_mu{i}',ea_C{i});
    end
    %predict labels of testing data with largest likelihood 
    [~, row] = max(likeli);
    test_predict = (row-1)';
    %calculate error and confusion matrix of the prediction
    error(d) = (sum(test_labels~=test_predict))/size(test_images,2)*100;
    confusion_mat{d} = confusionmat(test_labels,test_predict);
end

%plot classification error when varying d from 1 to dmax
fig=figure('Name','Classification error when varying d from 1 to dmax');
plot(error);
ylabel('classfication error');
xlabel('d'); 

%optimal value of d and its classification error and the confusion matrix. 
[err,opt_d]=min(error);
conf_matr=confusion_mat{opt_d};
disp(['optimal value d: ', num2str(opt_d)]);
disp(['corresponding error: ', num2str(err), ' %']);
disp('corresponding ConfusionMatrix:');
helperDisplayConfusionMatrix(conf_matr);
print(fig,'Classification error','-dpng');
end
