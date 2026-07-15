%{
Problem 6: Reconstruction
• Sample a signal 
• Reconstruct using interpolation (interp1)
Compare original vs reconstructed.
%}

clc;
clear;
close all;

% Original continuous-time signal
f = 5;                    % Signal frequency (Hz)
t = 0:0.001:1;            % Continuous time axis
x = sin(2*pi*f*t);

% Sampling
Fs = 20;                  % Sampling frequency
ts = 0:1/Fs:1;            % Sampled time axis
xs = sin(2*pi*f*ts);

% Reconstruction using linear interpolation
xr = interp1(ts, xs, t, 'linear');

% Plotting
figure;

% Original Signal
subplot(3,1,1);
plot(t, x, 'LineWidth', 1.5);
grid on;
title('Original Continuous-Time Signal');
xlabel('Time (s)');
ylabel('Amplitude');

% Sampled Signal
subplot(3,1,2);
plot(t, x, 'LineWidth', 1.5);
hold on;
stem(ts, xs, 'filled');
grid on;
title('Sampled Signal');
xlabel('Time (s)');
ylabel('Amplitude');

% Reconstructed Signal
subplot(3,1,3);
plot(t, x, 'LineWidth', 1.5);
hold on;
plot(t, xr, '--', 'LineWidth', 1.5);
grid on;
title('Original vs Reconstructed Signal');
xlabel('Time (s)');
ylabel('Amplitude');