% There are four help functions below for Intialization with K-means,
% Estep, Mstep, and Convergence Check.
clear;
load('dataGMM.mat');
n = size(Data,2);
mix_num = 4;
st_decre=1e-6;
notconverged=1;
iteration=0;

%% Initialize prior, mean and covariance with k-means
[prior,mu,sigma]=GMM_Initial(Data',mix_num,st_decre);
mu=mu';

%% Expectation-Maximization estimation of GMM parameters
if(iteration<100) % MaxSteps  
    %when not converged, repeat Estep and Mstep
    while(notconverged)          
    %E-step: Evaluate the responsibilities using the current parameters
    responsibility = zeros(n,mix_num);
    for j=1:size(Data,2)
        responsibility(j,:)=Estep(Data(:,j)',prior,mu,sigma,mix_num);
    end   
    %save data to check convergence
    mu_old = mu;
    sigma_old = sigma;
    prior_old = prior;   
    %M-step: Re-estimatetheparametersusingthecurrentresponsibilities
    [prior,mu,sigma]=Mstep(Data',responsibility,mix_num);
    %check for convergence
    notconverged=check(Data,prior_old,prior,mu_old,mu,sigma_old,sigma,mix_num);
    end
    iteration=iteration+1;
end

%% plot density values
x=linspace(-0.1,0.1,100);
[X,Y] = meshgrid(x,x);
Z1 = reshape(X,1,10000);
Z2 = reshape(Y,1,10000);
plotdata=[Z1;Z2]';
C = X.*Y;
for i=1:mix_num
     Z=prior(i)*mvnpdf(plotdata,mu(i,:),sigma{i});
     surf(X,Y,reshape(Z,100,100),C);
     hold on;  
end
title("Density values");
axis([-0.1 0.1 -0.1 0.1]);

%% function: k-means for initialization
function [pi0,mu0,Sigma0] = GMM_Initial(data,mix_num,st_decre)
J_before=inf;
decrement=inf;
[n,~]=size(data);
pi0=zeros(1,mix_num);
Sigma0=cell(0);
while(decrement>=st_decre)
    [label,mu,err]=kmeans(data,mix_num);
    J=sum(err);
    decrement=J_before-J;
    J_before=J;        
end
mu0=mu';
for i=1:mix_num
    data_each = data(label==i,:);
    Sigma0{i}=cov(data_each);
    pi0(i)=sum(label==i)/n;  
end
end

%% function: Estep
function responsibility=Estep(data,prior,mu,sigma,mix_num)
responsibility=zeros(1,mix_num);
numerator=zeros(mix_num);
denominator=0;
for k=1:mix_num 
    numerator(k)=prior(k)*mvnpdf(data,mu(k,:),sigma{k});
    denominator=denominator+numerator(k);
end 
for k=1:mix_num
    responsibility(k)=numerator(k)/denominator;
end
end

%% function: Mstep
function [priornew,munew,sigmanew]=Mstep(data,responsibility,mix_num)
 n=size(data,1);
sigmanew={zeros(2,2),zeros(2,2),zeros(2,2),zeros(2,2)};
for j=1:mix_num
    nk = sum(responsibility(:,j));
    munew(j,:) = 1/nk * responsibility(:,j)'*data;
    res_temp=repmat(responsibility(:,j),1,2);
    mu_temp=repmat(munew(j,:)',1,n);
    sigmanew{j} = 1/nk *(res_temp.*(data - mu_temp'))'*(data - mu_temp');
    priornew(j) = nk/n;
end
end

%% function: Check for convergence
function notconverged=check(data,prior,priornew,mu,munew,sigma,sigmanew,mix_num)
%Evaluate the log-likelihood
notconverged=1;
st_error=10e-7;
[n,~]=size(data);
sum1=0;
sum2=0;
loglike=0;
loglikenew=0;
for i=1:n
    for k=1:mix_num 
        sum1=sum1+prior(k)* mvnpdf(data(:,i)',mu(k,:),sigma{k});
        sum2=sum2+priornew(k)* mvnpdf(data(:,i)',munew(k,:),sigmanew{k});                    
    end
    loglike=loglike+log(sum1);
    loglikenew=loglikenew+log(sum2);
end

%Check the loglikelihood
if ((norm((loglikenew-loglike),2))<st_error)
    notconverged=0;
%Check the parameter
elseif ((norm((priornew-prior),2))<st_error || (norm((munew-mu),2))<st_error)
    notconverged=0;
elseif ((norm((sigmanew{1}-sigma{1}),2))<st_error && (norm((sigmanew{2}-sigma{2}),2))<st_error && (norm((sigmanew{3}-sigma{3}),2))<st_error && (norm((sigmanew{4}-sigma{4}),2))<st_error)
    notconverged=0; 
end
end