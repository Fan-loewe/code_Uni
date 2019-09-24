[y,Fs] = audioread('chimes.wav');

n1=1000*rand(1);
n2=1000*rand(1);
n=fix(13921*rand(1));
ch1 = n1*y(:, 1);
ch2 =n2*y(:, 2);
t = linspace(0 , 0.631, length(ch1));%13921/22050Hz

ch1_delay=[zeros(n,1); ch1];
t_delay=linspace(0 , 0.631 + n/Fs , length(ch1_delay));
ch2_nodelay=[ch2;zeros(n,1)];
ch2_fft = abs(fft(ch2))./max(abs(fft(ch2)));
f_axis= linspace(0 , 1, fix(length(t)/2))*Fs/2;
Iv = 1:length(f_axis);
noise1=100*normrnd(0,1,size(ch1_delay));%??????????????
noise2=100*normrnd(0,1,size(ch2_nodelay));
ch1_noisy=ch1_delay+noise1;
ch2_noisy=ch2_nodelay+noise2;
% sound(y,Fs);
figure(1)
plot(t, ch2, t_delay, ch1_delay)

figure(2)
plot(f_axis, ch2_fft(Iv))
y=[ch1_delay ch2_nodelay];
% sound(y,Fs);
%blue=right=ch2

figure(3)
[c1, lags1] = xcorr(ch2_nodelay, ch1_delay);
plot(lags1, c1);

figure(4)
[c2, lags2] = xcorr(ch2, ch1);
plot(lags2, c2);

figure(5)
[c3, lags3] = xcorr(ch2_noisy, ch1_noisy);%?/////?????????????/
plot(lags3, c3);
