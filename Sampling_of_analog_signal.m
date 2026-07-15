%{
Problem 4: Sampling of Analog Signal
Sample a sine wave at:
• Nyquist rate 
• Above Nyquist 
• Below Nyquist
Plot and compare.
%}

clc;
clear;
close all;

% Signal parameters
f = 5;              % Signal frequency (Hz)
t = 0:0.001:1;      % Continuous time
x = sin(2*pi*f*t);  % Analog sine wave

% Sampling frequencies
Fs1 = 10;   % Nyquist rate
Fs2 = 20;   % Above Nyquist
Fs3 = 6;    % Below Nyquist

% Sampled signals
t1 = 0:1/Fs1:1;
x1 = sin(2*pi*f*t1);

t2 = 0:1/Fs2:1;
x2 = sin(2*pi*f*t2);

t3 = 0:1/Fs3:1;
x3 = sin(2*pi*f*t3);

% Plotting
figure;

% Nyquist Rate
subplot(3,1,1);
plot(t, x, 'b', 'LineWidth', 1.5);
hold on;
stem(t1, x1, 'r', 'filled');
grid on;
title('Sampling at Nyquist Rate (Fs = 10 Hz)');
xlabel('Time (s)');
ylabel('Amplitude');


% Above Nyquist
subplot(3,1,2);
plot(t, x, 'b', 'LineWidth', 1.5);
hold on;
stem(t2, x2, 'r', 'filled');
grid on;
title('Sampling Above Nyquist Rate (Fs = 20 Hz)');
xlabel('Time (s)');
ylabel('Amplitude');


% Below Nyquist
subplot(3,1,3);
plot(t, x, 'b', 'LineWidth', 1.5);
hold on;
stem(t3, x3, 'r', 'filled');
grid on;
title('Sampling Below Nyquist Rate (Fs = 6 Hz)');
xlabel('Time (s)');
ylabel('Amplitude');
