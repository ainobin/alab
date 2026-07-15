%{
Problem 20: Filter Comparison
• Compare FIR vs IIR: 
o Response 
o Stability 
o Phase characteristics
%}

% Problem 20: Filter Comparison
% Compare FIR and IIR filters

clc;
clear;
close all;

% Filter specifications
fs = 1000;
fc = 100;
order = 20;

% FIR filter
b_fir = fir1(order, fc/(fs/2));

% IIR Butterworth filter
[b_iir, a_iir] = butter(4, fc/(fs/2));

% Frequency responses
[Hfir, f] = freqz(b_fir, 1, 512, fs);
[Hiir, ~] = freqz(b_iir, a_iir, 512, fs);

% Plot
figure;

subplot(2,1,1);
plot(f, abs(Hfir), 'b', 'LineWidth', 1.5);
hold on;
plot(f, abs(Hiir), 'r', 'LineWidth', 1.5);
title('Magnitude Response');
xlabel('Frequency (Hz)');
ylabel('Magnitude');
grid on;

subplot(2,1,2);
plot(f, angle(Hfir), 'b', 'LineWidth', 1.5);
hold on;
plot(f, angle(Hiir), 'r', 'LineWidth', 1.5);
title('Phase Response');
xlabel('Frequency (Hz)');
ylabel('Phase (radians)');
grid on;