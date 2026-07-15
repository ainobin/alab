%{
Problem 13: Statistical Measures
For a given signal:
• Mean 
• Variance 
• Standard deviation 
• Skewness 
• Kurtosis
Use MATLAB built-ins and manual formulas
%}

% Problem 13: Statistical Measures
% Calculate statistical measures using built-in functions and manual formulas

clc;
clear;
close all;

% Generate random signal
x = 2*randn(1,1000) + 3;
N = length(x);

% Built-in functions
mean1 = mean(x);
var1 = var(x);
std1 = std(x);
skew1 = skewness(x);
kurt1 = kurtosis(x);

% Manual calculations
mean2 = sum(x)/N;
var2 = sum((x-mean2).^2)/(N-1);
std2 = sqrt(var2);
skew2 = sum((x-mean2).^3)/(N*std2^3);
kurt2 = sum((x-mean2).^4)/(N*std2^4);

% Display results
fprintf('Built-in Mean = %.2f\n', mean1);
fprintf('Manual Mean   = %.2f\n\n', mean2);

fprintf('Built-in Variance = %.2f\n', var1);
fprintf('Manual Variance   = %.2f\n\n', var2);

fprintf('Built-in Std Dev = %.2f\n', std1);
fprintf('Manual Std Dev   = %.2f\n\n', std2);

fprintf('Built-in Skewness = %.2f\n', skew1);
fprintf('Manual Skewness   = %.2f\n\n', skew2);

fprintf('Built-in Kurtosis = %.2f\n', kurt1);
fprintf('Manual Kurtosis   = %.2f\n', kurt2);

% Plot histogram
figure;
histogram(x,30);
title('Histogram of Random Signal');
xlabel('Amplitude');
ylabel('Frequency');
grid on;