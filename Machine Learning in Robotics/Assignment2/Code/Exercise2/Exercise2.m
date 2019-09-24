%% Load probability matrix and the observation sequences to be classified
clear;
% load transition probability matrix
A=load('A.txt');
% load observation probability matrix
B=load('B.txt');
B=B';
% N=12 is number of states, M=8 is number of observations
[N,M]=size(B);
% load initial state probability vector
pi=load('pi.txt');

Test=load('Test.txt');
% T=60 is length of each sequence, there are 10 observation sequences
[T,sequence]=size(Test);

%% Forward procedure
alpha=zeros(T,N);
pro=zeros(sequence,1);
% classify each sequence
for l=1:sequence
    % Initialization
    % For each state in the sequence
    for i=1:N       
        alpha(1,i)=pi(i)*B(i,Test(1,l));
    end
    % Induction
    for t=1:T-1
       for j=1:N
           sum=0;
           for i=1:N
             temp=alpha(t,i)*A(i,j);
             sum=sum+temp;           
           end
           alpha(t+1,j)=sum*B(j,Test(t+1,l));
       end
    end
    % Termination
    for i =1:N
        pro(l)=pro(l)+alpha(T,i);
    end   
end
likelihood=log(pro);
for l=1:sequence
    if(likelihood(l))>-115
    classification(l)="gesture1";
    else 
         classification(l)="gesture2";
    end   
end
classification=classification';

