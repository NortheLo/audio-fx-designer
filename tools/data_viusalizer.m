% MATLAB Code for Live 2D Image Plot of UDP Packets with FIFO Buffer
clear; clc;

% Parameters
udpPort = 12345; % Change to your UDP port
dataSize = 256; % Size of each packet in bytes
numPackets = 100; % Size of the circular buffer
buffer = zeros(numPackets, dataSize); % Circular buffer for packets
currentIndex = 1; % Current index for the circular buffer

% Create UDP object
udpReceiver = udpport("datagram", "LocalPort", udpPort);
disp(['Listening for UDP packets on port ', num2str(udpPort)]);

% Initialize figure for 2D image plot
figure;
hImage = imagesc(zeros(dataSize, numPackets)); % Initialize empty image
colormap('jet'); % Set colormap
colorbar; % Add colorbar
title('Live 2D Image Plot of UDP Packet Data');
xlabel('Packet Number');
ylabel('Data Index');

% Loop to receive packets
while true
    % Receive a packet
    data = read(udpReceiver, 1, "single");
    
    % Store the data in the circular buffer
    power_spec = abs(fft(data.Data));
    power_spec = 10*log10(power_spec);
    power_spec = fftshift(power_spec);
    buffer(currentIndex, :) = power_spec; % Store received packet
    currentIndex = mod(currentIndex, numPackets) + 1; % Update index for circular behavior
    
    % Prepare data for plotting
    % If the buffer has wrapped around, use the entire buffer
    if currentIndex == 1
        plotData = buffer; % Full buffer
    else
        % Prepare the current state of the buffer for plotting
        plotData = [buffer(currentIndex:end, :); buffer(1:currentIndex-1, :)];
    end
    
    % Update the 2D image
    set(hImage, 'CData', plotData');
    xlim([1 numPackets]); % Set x-axis limits
    ylim([1 dataSize]);   % Set y-axis limits
    zlim([-50 0])
    title('Live 2D Image Plot of UDP Packet Data');
    
    % Pause for visualization update
    pause(0.1); % Adjust for desired update rate
end

% Clean up
clear udpReceiver;
disp('UDP reception complete.');
