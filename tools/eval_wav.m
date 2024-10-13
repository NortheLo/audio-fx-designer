%% This file should be used in MATLAB/Octave to eval IRs etc of the C++ Algorithms
clc; clear all;

% parameters to adjust
file_name = "test.wav";

[samples, sample_rate] = audioread(file_name);

plot_samples(samples(1:1000), sample_rate)
