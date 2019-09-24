clear all
clf
%%Task 4
%part a,b
Fs = 10000;                   % samples per second
dt = 1/Fs;                   % seconds per sample
StopTime = 0.1;             % seconds
t = (0:dt:StopTime-dt)';     % seconds
F1 = 50;
F2 = 500;
s1 = 1*sin(2*pi*F1*t);
s2 = 0.5*sin(2*pi*F2*t);
sig = s1+s2;
ts=-1;
figure(1);
plot(t,sig);
xlabel('time');
title('Signal');


%part c
Fc = 50;
numerator3 = 1;
denominator3 = [1/(2*pi*Fc),1];
Zc3 = tf(numerator3,denominator3)

%part d
numerator3d = (pi*Fc*dt)/(pi*Fc*dt-1)*[1, 1];
denominator3d = [(pi*Fc*dt+1)/(pi*Fc*dt-1),1];
Zc3d = tf(numerator3d,denominator3d, ts)
sf = filter(numerator3d,denominator3d,sig);

%part e
figure(2);
plot(t,sig);hold on;plot(t,sf,'r');
legend('signal','signal after low-pass filter');

%part f
Fc2 = 500;
numerator4 = [1/(2*pi*Fc2), 0];
denominator4 = [1/(2*pi*Fc2),1];
Zcf = tf(numerator4,denominator4)

%part g
numerator4d = 1/(pi*Fc2*dt-1)*[1, -1];
denominator4d = [(pi*Fc2*dt+1)/(pi*Fc2*dt-1),1];
Zc3d = tf(numerator4d,denominator4d, ts)
sfg = filter(numerator4d,denominator4d,sig);

%part h
figure(3);
plot(t,sig);hold on;plot(t,sfg,'g');
legend('signal','signal after high-pass filter');

%part i
F3 = 1000;
s3 = 1*sin(2*pi*F3*t);
sigi = sig+s3;

%part j
%low-pass filter
Fch = 500.00001;
%high-pass filter
Fcl = 499.99999;

numeratorbw = [-1,0];
denominatorbw = [1/(2*pi*Fcl*2*pi*Fch),1/(2*pi*Fch)+1/(2*pi*Fcl),1];
Zcbw = tf(numeratorbw,denominatorbw)

%part k
numeratorbwd = -2/dt*[1, -1]/1000;
denominatorbwd = 1/(dt*dt*pi*pi*Fch*Fcl)*[(1 + dt*dt*pi*pi*Fch*Fcl + dt*pi*Fch + dt*pi*Fcl), (2*dt*dt*pi*pi*Fch*Fcl - 2), (dt*dt*pi*pi*Fch*Fcl - dt*pi*Fch - dt*pi*Fcl + 1)];
Zcbwd = tf(numeratorbwd,denominatorbwd, ts)
sfbwd = filter(numeratorbwd,denominatorbwd,sigi);

fvtool(numeratorbwd,denominatorbwd)
figure(4);
plot(t,sfbwd);
legend('signal after band-pass filter');


