%{
Problem 3: Even and Odd Decomposition
Take any discrete signal and:
• Decompose into even and odd components 
• Verify: x[n]=xe[n]+xo[n]
%}

clc;
clear;
close all;

% Original signal
n = -2:2;
x = [-2 -1 0 1 2];

% Time-reversed signal
x_rev = fliplr(x);

% Even component
xe = (x + x_rev)/2;

% Odd component
xo = (x - x_rev)/2;

% Verification
x_verify = xe + xo;

% Plotting
figure;

% Original Signal
subplot(4,1,1);
plot(n, x, 'blue', 'LineWidth', 1.5);
hold on;
stem(n, x, 'blue','filled');
grid on;
title('Original Signal x[n]');
xlabel('n');
ylabel('Amplitude');


% Even Component
subplot(4,1,2);
plot(n, xe, 'blue', 'LineWidth', 1.5);
hold on;
stem(n, xe, 'blue','filled');
grid on;
title('Even Component x_e[n]');
xlabel('n');
ylabel('Amplitude');


% Odd Component
subplot(4,1,3);
plot(n, xo, 'blue', 'LineWidth', 1.5);
hold on;
stem(n, xo, 'blue','filled');
grid on;
title('Odd Component x_o[n]');
xlabel('n');
ylabel('Amplitude');


% Verification
subplot(4,1,4);
plot(n, x_verify, 'blue', 'LineWidth', 1.5);
hold on;
stem(n, x_verify, 'blue','filled');
grid on;
title('Verification: x[n] = x_e[n] + x_o[n]');
xlabel('n');
ylabel('Amplitude');
