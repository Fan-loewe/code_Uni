clf;
%t = [0:0.001:2];
t= linspace(0,2,2000);

f = 0 : 1000/length(t) : 1000 - 1000/length(t); % Frequency vector
f1= 50;
f2= 120;

sin1= sin(2*pi*f1*t);
sin2= 0.5*sin(2*pi*f2*t);
noise_sig = rand(1,length(t));
Sig= sin1+sin2+noise_sig;
fft_Sig = abs(fft(Sig));
fft_Sig = fft_Sig ./ 1000;

f_axis= linspace(0 , 1, fix(length(t)/2))*500;

Iv = 1:length(f_axis);

subplot(3,1,1),plot(t,sin1)
subplot(3,1,2),plot(t,sin2)
subplot(3,1,3),plot(t,Sig)
figure(2)
plot(f_axis,fft_Sig(Iv))
