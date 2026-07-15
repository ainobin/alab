%{
Problem 24: Signal Classification (Basic Intro)
• Generate multiple signal types 
• Extract features (mean, variance, etc.)
Classify based on properties
%}
% Problem 24: Signal Classification (Basic Intro)

clc;
clear;
close all;

% Generate signals
t = linspace(0,1,500);

signals = {sin(2*pi*5*t), ...
           square(2*pi*5*t), ...
           sawtooth(2*pi*5*t), ...
           0.5*randn(1,500)};

names = {'Sine','Square','Sawtooth','Noise'};

figure;

for i = 1:4
    x = signals{i};

    % Features
    m = mean(x);
    v = var(x);

    % Simple classification
    if v < 0.6
        type = 'Sine';
    elseif v < 0.9
        type = 'Sawtooth';
    elseif v < 1.2
        type = 'Square';
    else
        type = 'Noise';
    end

    % Display features
    fprintf('%s Signal\n', names{i});
    fprintf('Mean = %.2f\n', m);
    fprintf('Variance = %.2f\n', v);
    fprintf('Classified As: %s\n\n', type);

    % Plot
    subplot(2,2,i);
    plot(t,x,'LineWidth',1.2);
    title(sprintf('%s\nMean = %.2f, Var = %.2f', names{i}, m, v));
    xlabel('Time (s)');
    ylabel('Amplitude');
    grid on;
end