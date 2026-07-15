%{
Problem 1: Basic Signal Generation
Generate and plot the following signals:
• Unit step u[n] 
• Unit impulse δ[n] 
• Ramp signal
• Sine wave
• Cosine wave
Plot them in separate subplots and explain differences.
%}

clc;
clear;
close all;

% Discrete-time index
n = -10:10;

% Continuous-time vector for sine and cosine
t = 0:0.01:7;

% 1. Unit Step Signal
u = double(n >= 0);

% 2. Unit Impulse Signal
delta = double(n == 0);

% 3. Ramp Signal
r = n .* (n >= 0);

% 4. Sine Wave
sine = sin(2*pi*t);

% 5. Cosine Wave
cosine = cos(2*pi*t);

% Plotting
figure;

% Unit Step
subplot(5,1,1);
stem(n, u, 'filled');
grid on;
title('Unit Step Signal u[n]');
xlabel('n');
ylabel('Amplitude');

% Unit Impulse
subplot(5,1,2);
stem(n, delta, 'filled');
grid on;
title('Unit Impulse Signal \delta[n]');
xlabel('n');
ylabel('Amplitude');

% Ramp Signal
subplot(5,1,3);
stem(n, r, 'filled');
hold on;
plot(n, r, 'blue', 'LineWidth',1);
grid on;
title('Ramp Signal');
xlabel('n');
ylabel('Amplitude');
hold off;

% Sine Wave
subplot(5,1,4);
plot(t, sine, 'LineWidth', 1.5);
grid on;
title('Sine Wave');
xlabel('Time');
ylabel('Amplitude');

% Cosine Wave
subplot(5,1,5);
plot(t, cosine, 'LineWidth', 1.5);
grid on;
title('Cosine Wave');
xlabel('Time');
ylabel('Amplitude');