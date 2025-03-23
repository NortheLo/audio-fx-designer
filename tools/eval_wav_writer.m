%% This file should be used in MATLAB/Octave to eval IRs etc of the C++ Algorithms
clc; clear;

expected_t = 5; 
expected_fs = 48000;
expected_samples = expected_fs * expected_t;
expected_freq = 256;

% parameters to adjust
file_name = "test.wav";

[samples, sample_rate] = audioread(file_name);

freq = estimate_frequency(sample_rate, samples);

assert (freq == expected_freq), "Expected frequency of the sin-function is wrong";
assert (sample_rate == expected_fs), "Sample Rate must be 48kHz";
assert (length(samples) == expected_samples), "There is not the specific number of samples";