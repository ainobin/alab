%{
Problem 22: Speech Signal Analysis (Optional Advanced)
• Load audio file (audioread) 
• Apply: 
o STFT 
o Filtering
Observe real-world signal behavior
%}
% Problem 22: Speech Signal Analysis
% STFT and filtering of a speech-like signal

clc;
clear;
close all;

% Generate speech-like signal
fs = 8000;
t = 0:1/fs:1-1/fs;

x = sin(2*pi*150*t).*(1+0.5*sin(2*pi*3*t));
x = x + 0.3*sin(2*pi*800*t).*exp(-3*t);

% Add noise
noisy = x + 0.15*randn(size(t));

% Design FIR low-pass filter
b = fir1(100,1000/(fs/2));

% Filter the noisy signal
filtered = filter(b,1,noisy);

% Spectrogram
figure;
subplot(2,1,1);
spectrogram(noisy,256,200,256,fs,'yaxis');
title('STFT of Noisy Signal');

subplot(2,1,2);
spectrogram(filtered,256,200,256,fs,'yaxis');
title('STFT of Filtered Signal');

% Time-domain comparison
figure;

subplot(2,1,1);
plot(t,noisy,'LineWidth',1.2);
title('Noisy Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(2,1,2);
plot(t,filtered,'LineWidth',1.5);
title('Filtered Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;