clear all
close all

data = importImuData('../logs','kalmanTest');

scale = 1;

data.gyro = data.gyro * scale;


figure
plot(data.t,data.acc(:,1),'r');
grid on
hold on
plot(data.t,data.acc(:,2),'g');
plot(data.t,data.acc(:,3),'b');

figure
plot(data.t,data.gyro(:,1),'r');
grid on
hold on
plot(data.t,data.gyro(:,2),'g');
plot(data.t,data.gyro(:,3),'b');


n=data.n;

gPhi = zeros(1,n);
aPhi = zeros(1,n);

gTheta = zeros(1,n);
aTheta = zeros(1,n);

for k=2:n
    dt = data.t(k)-data.t(k-1);

    gPhi(k) = gPhi(k-1)+data.gyro(k,1)*dt;
    aPhi(k) = atan2(data.acc(k,2),data.acc(k,3))/pi*180;

    gTheta(k) = gTheta(k-1)+data.gyro(k,2)*dt;
    aTheta(k) = -atan2(data.acc(k,1),data.acc(k,3))/pi*180;

end




a_rot_p = zeros(3,n);
a_rot_u = zeros(3,n);
a_net 	= data.acc';
a_lin 	= zeros(3,n);

phi_fb		= zeros(1,n);
theta_fb	= zeros(1,n);
phi_p		= zeros(1,n);
theta_p		= zeros(1,n);
phi_u		= zeros(1,n);
theta_u		= zeros(1,n);

dPhi	= data.gyro(:,1)';
dTheta	= data.gyro(:,2)';

c_A = 1;
c_S = 1;

k1	= 1;
k2 	= 1;

k=1;
phi_u(k) 		= atan2(a_net(2,k),a_net(3,k));
theta_u(k)		= -atan2(a_net(1,k),a_net(3,k));

for k=2:n
	dt = data.t(k)-data.t(k-1);

	a_rot_p(:,k) = a_net(:,k) - c_A * a_lin(:,k-1);

	phi_fb(k) 	= atan2(a_rot_p(2,k),a_rot_p(3,k));
	theta_fb(k) = -atan2(a_rot_p(1,k),a_rot_p(3,k));

	phi_p(k) 	= phi_u(k-1) + dPhi(k)*dt/180*pi;
	theta_p(k) 	= theta_u(k-1) + dTheta(k)*dt/180*pi;

	phi_u(k)	= phi_p(k) + k1*(phi_fb(k) - phi_p(k));
	theta_u(k)	= theta_p(k) + k2*(theta_fb(k) - theta_p(k));

	a_rot_u(1,k) = -sin(theta_u(k));
	a_rot_u(2,k) = sin(phi_u(k))*cos(theta_u(k));
	a_rot_u(3,k) = cos(phi_u(k))*cos(theta_u(k));

	a_lin(:,k) = a_net(:,k) - c_S*a_rot_u(:,k);
end



figure
plot(data.t,aPhi(1,:),'b');
grid on
hold on
plot(data.t,gPhi(1,:),'g');
plot(data.t,phi_u/pi*180,'r');


figure
plot(data.t,aTheta,'b');
grid on
hold on
plot(data.t,gTheta,'g');
plot(data.t,theta_u/pi*180,'r');


figure
plot(data.t,a_lin(1,:),'r');
grid on
hold on
plot(data.t,a_lin(2,:),'g');
plot(data.t,a_lin(3,:),'b');
title('a_lin')


