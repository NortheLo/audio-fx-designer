function peakFrequency = estimate_frequency(sample_rate, samples)
    n = length(samples);
    fftResult = fft(samples);

    % Calculate the magnitude of the FFT result
    magnitude = abs(fftResult);

    % Find the index of the maximum magnitude
    [~, maxIndex] = max(magnitude);

    % Calculate the frequency corresponding to the maximum magnitude
    % Note: The FFT result is symmetric, so we only consider the first half
    if maxIndex > n / 2
        maxIndex = maxIndex - n;
    end
    peakFrequency = (maxIndex - 1) * (sample_rate / n);
end
