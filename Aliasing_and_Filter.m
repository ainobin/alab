%{
Problem 23: Aliasing + Filtering Combined
• Create aliased signal 
• Apply anti-aliasing filter
Analyze improvement
%}
clc;
clear;
close all;

% Original signal
f0 = 60;
fs = 70;

t = linspace(0,1,4000);
x = sin(2*pi*f0*t);

% Case 1: Direct sampling (Aliased)
ts = 0:1/fs:1;
xs_aliased = interp1(t,x,ts);

% Case 2: Apply anti-aliasing filter
b_aa = fir1(50,25/(fs/2));
x_filtered = filter(b_aa,1,x);
xs_filtered = interp1(t,x_filtered,ts);

% Plot
figure;

subplot(2,1,1);
plot(t,x,'Color',[0.7 0.7 0.7],'LineWidth',1.2);
hold on;
stem(ts,xs_aliased,'r','filled');
title(['Aliased Sampling (f_0 = ' num2str(f0) ' Hz, f_s = ' num2str(fs) ' Hz)']);
xlabel('Time (s)');
ylabel('Amplitude');
grid on;

subplot(2,1,2);
plot(t,x_filtered,'Color',[0.7 0.7 0.7],'LineWidth',1.2);
hold on;
stem(ts,xs_filtered,'g','filled');
title('After Anti-Aliasing Filter (Cutoff = 25 Hz)');
xlabel('Time (s)');
ylabel('Amplitude');
grid on;