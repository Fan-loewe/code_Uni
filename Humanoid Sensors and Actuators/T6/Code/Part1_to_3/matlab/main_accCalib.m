clear all
close all

% T1.3
data1 = importImuData('../build','accCalib');


n1 = data1.n;
ax = data1.acc(:,1);
ay = data1.acc(:,2);
az = data1.acc(:,3);



figure
plot3(ax,ay,az,'o')
title('Un-calibrated')


% Define the Unknown variables
m_meas = [ax.^2, ay.^2, az.^2 2*ax 2*ay 2*az];
d = ones(size(ax, 1), 1);
[U,S,V] = svd(m_meas, 'econ');% To let the S be a n*n matrix
p = V*inv(S)*U'*d;


A_delta = zeros(3,3);
A_delta(1,1) = p(1, :);
A_delta(2,2) = p(2, :);
A_delta(3,3) = p(3, :);

b_delta = [2*p(4, :); 2*p(5, :); 2*p(6, :)];

% T1.4
[U,S,V] = svd(-2*A_delta, 'econ');
w = V*inv(S)*U'*b_delta ;

%T1.5
A_pure=A_delta;
b_pure=0.5*b_delta;
c=-1;
F1=horzcat(A_pure,b_pure);
F2=horzcat(b_pure',c);
A_bar=vertcat(F1,F2);
T=(vertcat(horzcat(diag([1 1 1]),w),[0 0 0 1]));
A_hat=T'*A_bar*T;
A_fit=-1/A_hat(4,4)*[A_hat(1,1),A_hat(1,2),A_hat(1,3);A_hat(2,1),A_hat(2,2),A_hat(2,3);A_hat(3,1),A_hat(3,2),A_hat(3,3)];

%T1.6
[V,D]=eig(A_fit);
M_temp=(sqrt(D)*V');
M(1,1) = sum(M_temp(:, 1));
M(2,2) = sum(M_temp(:, 2));
M(3,3) = sum(M_temp(:, 3));

x = [ax';ay';az'];
x_cal=M*(x-w);



% Plot the calibrated x
%x = [ax';ay';az'];
y = x_cal;


figure
plot3(y(1,:),y(2,:),y(3,:),'o')
title('Calibrated')
hold on

