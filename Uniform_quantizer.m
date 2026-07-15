%{
Problem 7: Uniform Quantizer
• Implement a uniform quantizer 
• Quantize a sine wave 
• Plot input vs quantized output
%}


clc;
clear;
close all;

% Generate sine wave
fs = 1000;
t = 0:1/fs:1;
f = 5;
x = sin(2*pi*f*t);

% Uniform quantizer
L = 8;                 % Number of quantization levels
xmin = -1;
xmax = 1;
delta = (xmax - xmin)/L;

% Quantization
xq = delta * round(x/delta);

% Limit values within range
xq(xq > xmax) = xmax;
xq(xq < xmin) = xmin;

% Plot using subplots
figure;

subplot(2,1,1);
plot(t, x, 'b', 'LineWidth', 1.5);
title('Original Sine Wave');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(2,1,2);
stairs(t, xq, 'r', 'LineWidth', 1.5);
title('Quantized Sine Wave');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

% Comparison plot
figure;
subplot(1,1,1);
plot(t, x, 'b', 'LineWidth', 1.5);
hold on;
stairs(t, xq, 'r', 'LineWidth', 1.2);
title('Original vs Quantized Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;