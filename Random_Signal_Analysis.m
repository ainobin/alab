%{
Problem 15: Random Signal Analysis
• Generate white Gaussian noise 
• Analyze statistical properties
Verify theoretical expectations
%}
% Problem 15: Random Signal Analysis
% Generate white Gaussian noise and analyze its statistical properties

clc;
clear;
close all;

% Generate white Gaussian noise
N = 1000;
x = randn(1,N);

% Statistical properties
m = mean(x);
v = var(x);
s = std(x);

% Display results
fprintf('Mean = %.4f\n', m);
fprintf('Variance = %.4f\n', v);
fprintf('Standard Deviation = %.4f\n', s);

% Plot
figure;

subplot(2,1,1);
plot(x,'LineWidth',1);
title('White Gaussian Noise');
xlabel('Sample');
ylabel('Amplitude');
grid on;

subplot(2,1,2);
histogram(x,30);
title('Histogram of White Gaussian Noise');
xlabel('Amplitude');
ylabel('Frequency');
grid on;