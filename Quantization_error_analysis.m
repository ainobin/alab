%{
Problem 8: Quantization Error Analysis
• Compute quantization error 
• Plot error signal 
• Calculate Mean Squared Error (MSE)
%}

% Problem 8: Quantization Error Analysis
% Compute quantization error and Mean Squared Error (MSE)

clc;
clear;
close all;

% Generate sine wave
fs = 1000;
t = 0:1/fs:1;
f = 5;
x = sin(2*pi*f*t);

% Uniform quantizer
L = 8;
xmin = -1;
xmax = 1;
delta = (xmax - xmin)/L;

% Quantization
xq = delta * round(x/delta);
xq(xq > xmax) = xmax;
xq(xq < xmin) = xmin;

% Quantization error
error = x - xq;

% Mean Squared Error (MSE)
MSE = mean(error.^2);

% Display MSE
fprintf('Mean Squared Error (MSE) = %.6f\n', MSE);

% Plot using subplots
figure;

subplot(2,1,1);
plot(t, x, 'b', 'LineWidth', 1.5);
hold on;
stairs(t, xq, 'r', 'LineWidth', 1.2);
title('Original and Quantized Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(2,1,2);
plot(t, error, 'k', 'LineWidth', 1.5);
title(['Quantization Error (MSE = ', num2str(MSE), ')']);
xlabel('Time (s)');
ylabel('Error');
grid on;