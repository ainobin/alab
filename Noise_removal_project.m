%{
Problem 21: Noise Removal Project
• Add noise to signal 
• Apply appropriate filter
Evaluate performance using SNR
%}
% Problem 21: Noise Removal Project
% Add noise, apply filter, and evaluate using SNR

clc;
clear;
close all;

% Generate original signal
fs = 1000;
t = 0:1/fs:1-1/fs;
clean = sin(2*pi*10*t);

% Add white Gaussian noise
noisy = clean + 0.5*randn(size(t));

% Design Butterworth low-pass filter
[b,a] = butter(4,30/(fs/2));

% Filter the noisy signal
filtered = filter(b,a,noisy);

% Calculate SNR
snr_before = 10*log10(mean(clean.^2)/mean((noisy-clean).^2));
snr_after  = 10*log10(mean(clean.^2)/mean((filtered-clean).^2));

% Display SNR values
fprintf('SNR Before Filtering = %.2f dB\n', snr_before);
fprintf('SNR After Filtering  = %.2f dB\n', snr_after);

% Plot signals
figure;

subplot(3,1,1);
plot(t,clean,'LineWidth',1.5);
title('Original Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(3,1,2);
plot(t,noisy,'LineWidth',1.2);
title('Noisy Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(3,1,3);
plot(t,filtered,'LineWidth',1.5);
title('Filtered Signal');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

% Plot SNR comparison
figure;

b = bar([snr_before snr_after]);

b.FaceColor = 'flat';
b.CData(1,:) = [1 0 0];    % Red
b.CData(2,:) = [0 0 1];    % Blue

set(gca,'XTickLabel',{'Before Filtering','After Filtering'});
ylabel('SNR (dB)');
title('SNR Improvement After Filtering');
grid on;