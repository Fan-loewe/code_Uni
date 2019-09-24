function [states] = WalkQLearning(s)
num_st=16;
num_act=4;
discount=0.95;  %discount reward
epsilon=0.2;    %random policy for exploration
%epsilon=0      %pure policy
alpha=0.8;      %learning rate
T=40000;        %iterations

%initialization
Q=zeros(16,4);
policy=zeros(16,1);
state=s;

while(T)
    T=T-1;
    % epsilon-greedy policy
    pro = rand();
    if pro<1-epsilon
    %take optimal action
        maxvalue = -inf;
        % find action which can achieves maximal Q(s,a)
        for a=1:num_act
            if(Q(state,a) > maxvalue)
                maxvalue = Q(state,a);
                best_action = a;                
            end    
        end
        % use best action to generate new state and reward
        [state_new, reward]=SimulateRobot(state,best_action);
        % update Q(s,a)
        Q(state,best_action)=Q(state,best_action)+alpha*(reward+discount*max(Q(state_new,:))-Q(state,best_action));        
    else
    %take random action(exploration step)
        % generate random action
        action = ceil(rand()*num_act);
        % use random action to generate new state and reward
        [state_new, reward]=SimulateRobot(state,action);
        % update Q(s,a)
        Q(state,action)=Q(state,action)+alpha*(reward+discount*max(Q(state_new,:))-Q(state,action)); 
    end    
    % update state
    state=state_new;   
end

% after training, find the best policy
for i=1:num_st
    [~,policy(i)]=max(Q(i,:));
end

%% Simulation
states = zeros(num_st,1);
states(1) = s;
figure
for i = 2:num_st
    [states(i),~] = SimulateRobot(states(i-1),policy(states(i-1)));
end
walkshow(states.');
title(strcat("WalkQlearning starting from state ", num2str(s)));
end