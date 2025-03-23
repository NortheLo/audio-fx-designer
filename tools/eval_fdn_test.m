%% This file should be used in MATLAB/Octave to eval IRs etc of the C++ Algorithms
clc; clear;

% when running Octave import the packages; MATLAB needs tej signal toolbox
% pkg load signal

% parameters to adjust
file_name_impulse = "impulse.wav";
file_name_response = "response.wav";

% read *.wav files
[samples_impulse, sample_rate_i] = audioread(file_name_impulse);
[samples_response, sample_rate_r] = audioread(file_name_response);

plot_impulse_response(samples_impulse, sample_rate_i, samples_response, sample_rate_r);
