%{
Problem 12: Short-Time Fourier Transform (STFT)
• Apply spectrogram() on: 
o Stationary signal 
o Non-stationary signal
Interpret time-frequency behavior
%}

clc;
clear;
close all;

% Sampling parameters
fs = 1000;
t = 0:1/fs:2-1/fs;

% Stationary signal
x1 = sin(2*pi*50*t);

% Non-stationary signal
x2 = zeros(size(t));
x2(1:length(t)/2) = sin(2*pi*20*t(1:length(t)/2));
x2(length(t)/2+1:end) = sin(2*pi*80*t(length(t)/2+1:end));

% Plot spectrograms
figure;

subplot(2,1,1);
spectrogram(x1,128,120,128,fs,'yaxis');
title('Stationary Signal');

subplot(2,1,2);
spectrogram(x2,128,120,128,fs,'yaxis');
title('Non-Stationary Signal');