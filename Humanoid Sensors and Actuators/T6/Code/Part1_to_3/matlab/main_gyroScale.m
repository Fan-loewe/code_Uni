clear all
close all

data = importImuData('../build','gyroScaleX');

scale = 1
data.gyro = data.gyro * scale;

% figure
% plot(data.t,data.acc(:,1),'r');
% grid on
% hold on
% plot(data.t,data.acc(:,2),'g');
% plot(data.t,data.acc(:,3),'b');
% 
% figure
% plot(data.t,data.gyro(:,1),'r');
% grid on
% hold on
% plot(data.t,data.gyro(:,2),'g');
% plot(data.t,data.gyro(:,3),'b');

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



figure
plot(data.t,aPhi(1,:),'b');
grid on
hold on
plot(data.t,gPhi(1,:),'g');
title('Rotating around X-Axis');


% 
% figure
% plot(data.t,aTheta,'b');
% grid on
% hold on
% plot(data.t,gTheta,'g');



data = importImuData('../build','gyroScaleY');

scale = 1
data.gyro = data.gyro * scale;
% 
% figure
% plot(data.t,data.acc(:,1),'r');
% grid on
% hold on
% plot(data.t,data.acc(:,2),'g');
% plot(data.t,data.acc(:,3),'b');
% 
% figure
% plot(data.t,data.gyro(:,1),'r');
% grid on
% hold on
% plot(data.t,data.gyro(:,2),'g');
% plot(data.t,data.gyro(:,3),'b');

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



% figure
% plot(data.t,aPhi(1,:),'b');
% grid on
% hold on
% plot(data.t,gPhi(1,:),'g');



figure
plot(data.t,aTheta,'b');
grid on
hold on
plot(data.t,gTheta,'g');
title('Rotating around Y-Axis');


