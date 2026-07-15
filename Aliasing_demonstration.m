%{
Problem 5: Aliasing Demonstration
Generate a continuous-time sinusoid and:
• Sample at different frequencies 
• Show aliasing effect visually
%}

clc;
clear;
close all;

% Original continuous-time signal
f = 10;                % Signal frequency (Hz)
t = 0:0.001:1;         % Continuous time axis
x = sin(2*pi*f*t);

% Sampling frequencies
Fs1 = 30;              % Above Nyquist
Fs2 = 20;              % Nyquist
Fs3 = 12;              % Below Nyquist (Aliasing)

% Sampled signals
t1 = 0:1/Fs1:1;
x1 = sin(2*pi*f*t1);

t2 = 0:1/Fs2:1;
x2 = sin(2*pi*f*t2);

t3 = 0:1/Fs3:1;
x3 = sin(2*pi*f*t3);

% Plotting
figure;

% Above Nyquist
subplot(3,1,1);
plot(t, x, 'b', 'LineWidth', 1.5);
hold on;
stem(t1, x1, 'filled');
grid on;
title('Sampling Above Nyquist Rate (Fs = 30 Hz)');
xlabel('Time (s)');
ylabel('Amplitude');

% Nyquist Rate
subplot(3,1,2);
plot(t, x, 'b', 'LineWidth', 1.5);
hold on;
stem(t2, x2, 'filled');
grid on;
title('Sampling at Nyquist Rate (Fs = 20 Hz)');
xlabel('Time (s)');
ylabel('Amplitude');

% Below Nyquist (Aliasing)
subplot(3,1,3);
plot(t, x, 'b', 'LineWidth', 1.5);
hold on;
stem(t3, x3, 'filled');
grid on;
title('Sampling Below Nyquist Rate (Fs = 12 Hz) - Aliasing');
xlabel('Time (s)');
ylabel('Amplitude');