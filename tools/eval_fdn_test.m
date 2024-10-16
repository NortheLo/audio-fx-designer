%% This file should be used in MATLAB/Octave to eval IRs etc of the C++ Algorithms
clc; clear all;

% parameters to adjust
file_name_impulse = "impulse.wav";
file_name_response = "response.wav";

% read *.wav files
[samples_impulse, sample_rate_i] = audioread(file_name_impulse);
[samples_response, sample_rate_r] = audioread(file_name_response);

assert (isequal(sample_rate_i, sample_rate_r), "Sample Rate missmatch!")

plot_samples(samples_impulse, sample_rate_i)
plot_samples(samples_response, sample_rate_r)
