%{
Problem 11: Frequency Spectrum Analysis
• Generate composite signal (multiple sinusoids) 
• Plot magnitude spectrum
Identify frequency components
%}
% Problem 11: Frequency Spectrum Analysis
% Generate a composite signal and plot its magnitude spectrum

clc;
clear;
close all;

% Generate composite signal
fs = 500;
t = 0:1/fs:1-1/fs;
x = sin(2*pi*20*t) + 0.7*sin(2*pi*50*t) + 0.4*sin(2*pi*80*t);

% Compute FFT
X = fft(x);
N = length(x);
f = (0:N/2-1) * fs / N;

% Plot
figure;

subplot(2,1,1);
plot(t, x, 'LineWidth', 1.5);
title('Composite Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(2,1,2);
plot(f, abs(X(1:N/2)), 'LineWidth', 1.5);
title('Magnitude Spectrum');
xlabel('Frequency (Hz)');
ylabel('Magnitude');
xlim([0 120]);
grid on;