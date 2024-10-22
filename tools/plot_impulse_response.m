function plot_impulse_response(samples_impulse, sample_rate_impulse, samples_response, sample_rate_response)
    % Check if the samples arrays are empty
    if isempty(samples_impulse)
        error('The impulse samples array is empty.');
    end
    if isempty(samples_response)
        error('The response samples array is empty.');
    end

    % Check if sample rates are equal
    if sample_rate_impulse ~= sample_rate_response
        error('Sample rates are not equal.');
    end

    % Time vectors for impulse and response
    t_impulse = (0:length(samples_impulse)-1) / sample_rate_impulse;
    t_response = (0:length(samples_response)-1) / sample_rate_response;

    % Create a figure for plotting
    figure('Name', 'Impulse Response Analysis', 'NumberTitle', 'off');

    % --- Impulse in Time Domain ---

    % Plot the time domain for the impulse
    subplot(4, 1, 1);
    plot(t_impulse, samples_impulse);
    title('Impulse - Time Domain');
    xlabel('Time (seconds)');
    ylabel('Amplitude');
    grid on;

    % --- Response in Time Domain ---

    % Plot the time domain for the response
    subplot(4, 1, 2);
    plot(t_response, samples_response);
    title('Response - Time Domain');
    xlabel('Time (seconds)');
    ylabel('Amplitude');
    grid on;

    % --- Response in Frequency Domain ---

    % Compute the FFT of the response samples
    n_response = length(samples_response);
    f_response = (0:n_response-1) * (sample_rate_response / n_response); % Frequency vector
    Y_response = fft(samples_response);

    % Plot the magnitude of the FFT (only positive frequencies)
    subplot(4, 1, 3);
    plot(f_response(1:n_response/2), abs(Y_response(1:n_response/2)));
    title('Response - Frequency Domain (Magnitude)');
    xlabel('Frequency (Hz)');
    ylabel('Magnitude');
    grid on;

    % Plot the phase of the FFT (only positive frequencies)
    subplot(4, 1, 4);
    plot(f_response(1:n_response/2), angle(Y_response(1:n_response/2)));
    title('Response - Frequency Domain (Phase)');
    xlabel('Frequency (Hz)');
    ylabel('Phase (radians)');
    grid on;

end

