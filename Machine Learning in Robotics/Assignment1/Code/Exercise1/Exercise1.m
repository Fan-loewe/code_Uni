function par = Exercise1(k)
    load('Data.mat');

    V = Input(1,:);
    W = Input(2,:);
    dX = Output(1,:);
    dY = Output(2,:);
    dag = Output(3,:);
    n= size(Input,2);
    p=6;
    minPosErr=inf;
    minOriErr=inf;

    for P=1:p
        for K=1:k
            % divide data to training data and testing data with K-fold
            test_ind = 1+(K-1)*(n/k):K*(n/k);
            train_ind = 1:n;
            train_ind(test_ind)=[];

            V_train = V(train_ind)';  
            W_train = W(train_ind)';
            dX_train = dX(train_ind)';
            dY_train = dY(train_ind)';
            dag_train = dag(train_ind)';

            V_test = V(test_ind)'; 
            W_test = W(test_ind)';
            dX_test = dX(test_ind)';
            dY_test = dY(test_ind)';
            dag_test = dag(test_ind)';

            %use training data to find the best parameter with linear regression
            
            VW_train = polynomial(V_train,W_train,P);
            A1 = (VW_train' * VW_train)\ VW_train' * dX_train; 
            A2 = (VW_train' * VW_train)\ VW_train' * dY_train; 
            A3 = (VW_train' * VW_train)\ VW_train' * dag_train; 

            %predict value with best parameter
            VW_test = polynomial(V_test,W_test,P);
            dX_pred = VW_test*A1;
            dY_pred = VW_test*A2;
            dag_pred = VW_test*A3;

            %calculate position and orientation error to find best p
            poserr(P,K) = (sum(sqrt((dX_pred-dX_test).^2+(dY_pred-dY_test).^2)))/size(test_ind,2);
            orierr(P,K) = (sum(sqrt((dag_pred-dag_test).^2)))/size(test_ind,2);        

        end
        
        Kposerr = sum(poserr,2);
        Korierr = sum(orierr,2); 
        
        if(Kposerr(P) < minPosErr)
        minPosErr=Kposerr(P);
        p1=P;
        par1=A1;
        par2=A2;
        end
        if(Korierr(P) < minOriErr)
        minOriErr=Korierr(P);
        p2=P;
        par3=A3;
        end
    end
    par={par1,par2,par3};
    save("params","par");
    
    simulate;
end

%% simulate robots
function simulate
    v=[0,1,1,-1];
    w=[0.05,0,0.05,-0.05];
    for i=1:4
        Simulate_robot(v(i),w(i));
    end
    %Simulate_robot(0.5,-0.03);
end

%%
function VW = polynomial(V,W,p)
    VW = ones(size(V,1),1+3*p);
    for i=1:p
        VW(:,(3*i-1):(3*i+1))= [V.^i,W.^i,(V.*W).^i];
    end
end





