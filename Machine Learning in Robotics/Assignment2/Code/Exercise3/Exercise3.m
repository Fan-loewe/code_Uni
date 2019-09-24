clear;
num_st=16;
iterations=zeros(1,num_st);
states_whole=zeros(num_st,num_st);
 for s=1:num_st
     % policy iteration
     [policy,iterations(s)]=WalkPolicyIteration(s);
     %Q-learning
     [states]=WalkQLearning(s);
     states_whole(:,s)=states;
 end

 % check how many steps are necessary for the Q-learning algorithm to find an optimal policy
flag=1;
standseq=[9,13,14,2,3,4,8,5];%optimal policy
 for j=1:num_st
     % for 16 starting state, check if the sequence 5-9-13-14-2-3-4-8-5 correct
     oneseq=states_whole(:,j);
     index=find(oneseq==5,1);
     if(index>9|index<1)
         flag=0;
         break;
     end        
     for a=1:8
         nowseq(a)=oneseq(index+a);
     end
     for a=1:8
         if(nowseq(a)~=standseq(a))
             flag=0; % if flag is 0, it means there is one starting state didn't find optimal policy
         end
     end
     if(flag==0)
         break;
     end
 end
% if flag==1, it means in such steps can find optimal policy



