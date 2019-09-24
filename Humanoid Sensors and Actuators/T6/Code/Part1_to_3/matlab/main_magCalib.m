clear all
close all

data = importImuData('../build','magCalib');

n = data.n;
mx = data.mag(:,1);
my = data.mag(:,2);
mz = data.mag(:,3);


figure
plot3(mx,my,mz,'o')
title('Un-calibrated')

% Define the Unknown variables
m_meas = [mx.^2, my.^2, mz.^2, 2*mx.*my 2*mx.*mz 2*my.*mz,2*mx 2*my 2*mz];
d = ones(size(mx, 1), 1);
[U,S,V] = svd(m_meas, 'econ');% To let the S be a n*n matrix
p = V*inv(S)*U'*d;

A_delta = zeros(3,3);
A_delta(1,1) = p(1, :);
A_delta(2,2) = p(2, :);
A_delta(3,3) = p(3, :);

A_delta(2,1) = p(4, :);
A_delta(3,1) = p(5, :);
A_delta(3,2) = p(6, :);

A_delta(1,2) = p(4, :);
A_delta(1,3) = p(5, :);
A_delta(2,3) = p(6, :);

b_delta = [2*p(7, :); 2*p(8, :); 2*p(9, :)];

% T2.4
[U,S,V] = svd(-2*A_delta, 'econ');
w = V*inv(S)*U'*b_delta;

%T2.5
A_pure=A_delta;
b_pure=0.5*b_delta;
c=-1;
F1=horzcat(A_pure,b_pure);
F2=horzcat(b_pure',c);
A_bar=vertcat(F1,F2);
T=(vertcat(horzcat(diag([1 1 1]),w),[0 0 0 1]));
A_hat=T'*A_bar*T;
A_fit=-1/A_hat(4,4)*[A_hat(1,1),A_hat(1,2),A_hat(1,3);A_hat(2,1),A_hat(2,2),A_hat(2,3);A_hat(3,1),A_hat(3,2),A_hat(3,3)];

%T2.6
[U,S,V]=svd(A_fit, 'econ');
M=(sqrt(S)*V');

x = [mx';my';mz'];
x_cal=M*(x-w);
y = x_cal;


figure
plot3(y(1,:),y(2,:),y(3,:),'o')
title('Calibrated')
hold on


