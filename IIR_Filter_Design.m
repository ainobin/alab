%{
Problem 18: IIR Filter Design
• Design Butterworth filter using butter
• Apply filtering using filter
%}

% Problem 18: IIR Butterworth Filter Design
% Design a Butterworth low-pass filter and apply it to a noisy signal

clc;
clear;
close all;

% Generate signal
fs = 1000;
t = 0:1/fs:1;
x = sin(2*pi*10*t);

% Add high-frequency noise
noisy = x + 0.5*randn(size(x));

% Design Butterworth low-pass filter
order = 4;
cutoff = 20/(fs/2);          % Normalized cutoff frequency
[b,a] = butter(order, cutoff);

% Filter the signal
filtered = filter(b, a, noisy);

% Plot
figure;

subplot(3,1,1);
plot(t, x, 'LineWidth', 1.5);
title('Original Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(3,1,2);
plot(t, noisy, 'LineWidth', 1.2);
title('Noisy Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(3,1,3);
plot(t, filtered, 'LineWidth', 1.5);
title('Filtered Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;