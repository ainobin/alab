%{
Problem 16: Low-Pass Filter Design
• Design FIR low-pass filter using fir1
• Apply on noisy signal
Show before/after filtering
%}
% Problem 16: Low-Pass Filter Design
% Design an FIR low-pass filter and apply it to a noisy signal

clc;
clear;
close all;

% Generate signal
fs = 1000;
t = 0:1/fs:1;
x = sin(2*pi*10*t);              % Original signal

% Add noise
noisy = x + 0.5*randn(size(x));

% Design FIR low-pass filter
order = 30;
cutoff = 20/(fs/2);              % Normalized cutoff frequency
b = fir1(order, cutoff);

% Filter the noisy signal
filtered = filter(b, 1, noisy);

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