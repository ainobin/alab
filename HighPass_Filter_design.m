%{
Problem 17: High-Pass Filter Design
• Remove DC component from signal
Compare original and filtered
%}

% Problem 17: High-Pass Filter Design
% Remove DC component from a signal using an FIR high-pass filter

clc;
clear;
close all;

% Generate signal with DC offset
fs = 1000;
t = 0:1/fs:1;
x = sin(2*pi*10*t) + 2;      % Sine wave with DC offset

% Design FIR high-pass filter
order = 30;
cutoff = 5/(fs/2);           % Cutoff frequency = 5 Hz
b = fir1(order, cutoff, 'high');

% Filter the signal
y = filter(b, 1, x);

% Plot
figure;

subplot(2,1,1);
plot(t, x, 'LineWidth', 1.5);
title('Original Signal with DC Component');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(2,1,2);
plot(t, y, 'LineWidth', 1.5);
title('Filtered Signal (DC Removed)');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;