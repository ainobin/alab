%{
Problem 19: Frequency Response
• Plot magnitude and phase response using freqz
Interpret cutoff frequency
%}
% Problem 19: Frequency Response
% Plot magnitude and phase response using freqz

clc;
clear;
close all;

% Design Butterworth low-pass filter
order = 4;
fc = 100;          % Cutoff frequency (Hz)
fs = 1000;         % Sampling frequency (Hz)

[b,a] = butter(order, fc/(fs/2));

% Plot frequency response
figure;
freqz(b,a,512,fs);