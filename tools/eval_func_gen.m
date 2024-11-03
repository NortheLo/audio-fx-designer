clear all; clear;

% Parameters
Fs = 48000;          % Sampling rate (Hz)
f = 440;            % Frequency of the sinusoid (Hz)
A = 2;              % Amplitude
N = 1024;           % Number of samples

% Time vector
t = (0:N-1) / Fs;   % Time vector from 0 to (N-1)/Fs

% Sinusoidal signal
sinusoidal_signal = A * sin(2 * pi * f * t);


