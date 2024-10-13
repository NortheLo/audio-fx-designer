function plot_samples(samples, sample_rate)
    % Check if the samples array is empty
    if isempty(samples)
        error('The samples array is empty.');
    end

    % Time vector based on the length of samples and sampling frequency
    t = (0:length(samples)-1) / sample_rate;

    % Create a figure for plotting
    figure;

    % Plot the time domain
    subplot(2, 1, 1);
    plot(t, samples);
    title('Time Domain');
    xlabel('Time (seconds)');
    ylabel('Amplitude');
    grid on;

    % Compute the FFT of the samples
    n = length(samples);
    f = (0:n-1) * (sample_rate / n); % Frequency vector
    Y = fft(samples);

    % Plot the frequency domain (only positive frequencies)
    subplot(2, 1, 2);
    plot(f(1:n/2), abs(Y(1:n/2))); % Magnitude of the FFT
    title('Frequency Domain');
    xlabel('Frequency (Hz)');
    ylabel('Magnitude');
    grid on;

     % Find and display the maximum frequency
    maxFrequency = f(find(abs(Y(1:n/2)) == max(abs(Y(1:n/2))), 1));
    fprintf('The maximum frequency in the FFT results is: %.2f Hz\n', maxFrequency)

end

