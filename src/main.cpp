#include <iostream>
#include <vector>
#include <cmath>

#include <cstring>  // For memcpy
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // For close()

#include "../include/AudioSystem.hpp"
#include "../include/FDNReverb.hpp"
#include "../include/FuncGenerator.hpp"



void sendFloatVector(const std::vector<float>& data, const std::string& host, unsigned short port) {
    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }

    // Set up the recipient address structure
    struct sockaddr_in receiver_addr;
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(port); // Convert port to network byte order
    inet_pton(AF_INET, host.c_str(), &receiver_addr.sin_addr); // Convert IP address

    // Convert float vector to byte array
    std::vector<char> buffer(data.size() * sizeof(float));
    std::memcpy(buffer.data(), data.data(), buffer.size());

    // Send the data
    ssize_t sent_bytes = sendto(sockfd, buffer.data(), buffer.size(), 0,
                                 (struct sockaddr*)&receiver_addr, sizeof(receiver_addr));
    
    if (sent_bytes < 0) {
        std::cerr << "Error sending data" << std::endl;
    } else {
        std::cout << "Sent " << data.size() << " floats to " << host << ":" << port << std::endl;
    }

    // Clean up
    close(sockfd);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {

    // reverb settings 
    int delayLength = 1000;
    FDNReverb reverb(delayLength); // Create a reverb object

    std::vector<float> buf;
    buf.resize(FRAMES_PER_BUFFER);

    AudioSystem audio = AudioSystem();
    audio.openAudio();
    while(Pa_IsStreamActive(audio.stream)) {
        buf = audio.getBuffer();

        //sendFloatVector(buf, "192.168.2.197", 12345);

        // move this into a dsp class
        for (size_t i = 0; i < buf.size(); i++) {
            buf[i] = reverb.processSample(buf[i]);
                sendFloatVector(buf, "192.168.2.197", 12345);
        }
        audio.writeBuffer(buf);
    }

    std::cout << "End\n";
    return EXIT_SUCCESS;
}