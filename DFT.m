%{
Problem 10: Discrete Fourier Transform (DFT)
• Compute DFT using: 
o Built-in fft
o Manual implementation
Compare results
%}
% Problem 10: Discrete Fourier Transform (DFT)
% Compare built-in FFT with manual DFT

clc;
clear;
close all;

% Generate signal
N = 64;
n = 0:N-1;
x = sin(2*pi*5*n/N);

% Built-in FFT
X_fft = fft(x);

% Manual DFT
X_dft = zeros(1,N);

for k = 1:N
    for m = 1:N
        X_dft(k) = X_dft(k) + x(m) * exp(-1j*2*pi*(k-1)*(m-1)/N);
    end
end

% Plot comparison
figure;

subplot(2,1,1);
stem(0:N-1, abs(X_fft), 'filled');
title('Magnitude Spectrum using FFT');
xlabel('Frequency Index');
ylabel('|X(k)|');
grid on;

subplot(2,1,2);
stem(0:N-1, abs(X_dft), 'filled');
title('Magnitude Spectrum using Manual DFT');
xlabel('Frequency Index');
ylabel('|X(k)|');
grid on;