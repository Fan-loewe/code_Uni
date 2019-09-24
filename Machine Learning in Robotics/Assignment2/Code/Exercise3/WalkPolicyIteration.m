function [policy,iterations]=WalkPolicyIteration(s)
%% Task 1: Policy iteration for determinisitic system
% State transition function s'=theta(s, a)
st_tr = [2,4,5,13;%1
    1,3,6,14;     %2
    4,2,7,15;     %3
    3,1,8,16;     %4
    6,8,1,9 ;     %5
    5,7,2,10;     %6
    8,6,3,11;     %7
    7,5,4,12;     %8
    10,12,13,5;   %9
    9,11,14,6;    %10
    12,10,15,7;   %11
    11,9,16,8;    %12
    14,16,9,1;    %13
    13,15,10,2;   %14
    16,14,11,3;   %15
    15,13,12,4];  %16

%% Task 2: Reward matrix.
% according to the state transition function and optimal state transition 
% sequence 5-9-13-14-2-3-4-8-5 to generate reward function
rew = [ 0, 1, 0, 1;  %1  
    0, 1, -1, 0;     %2  
    1, 0, -1, 0;     %3  
    0, -1, 1, -1;    %4
    -1, 0, -1, 1;    %5
    1, -1, 1, -1;    %6
    1, -1, 0, -1;    %7
    -1, 1, 0, 0;     %8
    -1, 0, 1, 0;     %9
    0, -1, 1, -1;    %10
    1, -1, 0, -1;    %11
    -1, 0, -1, 1;    %12
    1, -1, 0, -1;    %13
    0, 0, -1, 1;     %14
    -1, 1, -1, 0;    %15
    0, 1, 0, 0];     %16

%% Task3: Policy iteration
num_st=16;
num_act=4;
discount=0.9;

% Initialize policy randomly
policy = ceil(rand(num_st,1)*num_act);
policy_new = zeros(16,1);
Vpi = zeros(16,1);
Vpi_new = zeros(16,1);
iterations=0;
% Repeat until convergence
while(1)
    iterations=iterations+1;
    % Policy evaluation
    while(1)   
        for i=1:num_st
            Vpi_new(i) = rew(i,policy(i)) + discount * Vpi(st_tr(i,policy(i)));
        end
        if(all(abs(Vpi_new-Vpi) <0.1))
            break;
        end
        Vpi = Vpi_new;
    end
    % Policy improvement
    for i=1:num_st
        max = -inf;
        for a = 1:num_act
            temp = rew(i,a) + discount * Vpi(st_tr(i,a));
            if(temp > max)
                policy_new(i) = a;
                max = temp;
            end
        end
    end   
    %check converge conditions
    if(all(policy == policy_new))
        break;
    end
    policy = policy_new;
end

%% Simulation
states = zeros(num_st,1);
states(1) = s;
figure
for i = 2:num_st
    states(i) = st_tr(states(i-1),policy(states(i-1)));
end
walkshow(states.');
title(strcat("WalkPolicyIteration starting from state ", num2str(s)));
end

