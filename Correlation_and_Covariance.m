%{
Problem 14: Correlation & Covariance
• Compute: 
o Auto-correlation 
o Cross-correlation 
o Covariance
Interpret physical meaning
%}

clc;
clear;
close all;

% Generate signals
n = 0:199;
x = sin(2*pi*0.05*n);
y = [x(11:end) x(1:10)] + 0.1*randn(1,200);

% Auto-correlation
[auto,lags1] = xcorr(x);

% Cross-correlation
[cross,lags2] = xcorr(x,y);

% Covariance
C = cov(x,y);

% Display covariance matrix
disp('Covariance Matrix:');
disp(C);

% Plot
figure;

subplot(3,1,1);
plot(n,x,'b','LineWidth',1.5);
hold on;
plot(n,y,'r','LineWidth',1.2);
title('Signals x[n] and y[n]');
xlabel('Sample');
ylabel('Amplitude');
grid on;

subplot(3,1,2);
plot(lags1,auto,'LineWidth',1.5);
title('Auto-correlation of x[n]');
xlabel('Lag');
ylabel('Correlation');
grid on;

subplot(3,1,3);
plot(lags2,cross,'LineWidth',1.5);
title('Cross-correlation of x[n] and y[n]');
xlabel('Lag');
ylabel('Correlation');
grid on;