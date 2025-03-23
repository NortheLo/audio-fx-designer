clc; clear;

path_ir = "twincab.wav";
path_audio = "rock_riff_wo_ir.wav";

[samples_ir, fs_ir] = audioread(path_ir);
[samples_audio, fs_audio] = audioread(path_audio);

if fs_audio ~= fs_ir
    fprintf('Samples Rate is not equal of the IR and Audio source.\n');
end

samples_audio = samples_audio(:, 1);

% First approach in time domain

audio_out = conv(samples_audio, samples_ir);
audiowrite('rock_riff_td_ir.wav', audio_out, fs_audio);
