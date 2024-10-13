#include <iostream>
#include <filesystem>
#include <vector>
#include <cmath>

#include "../include/WavWriter.hpp"

int main() {
    std::filesystem::path filePath = "../tools/test.wav";
    WavWriter wav = WavWriter(filePath);


    std::vector<float> buffer;
    // Playing a C Note
    float MIDDLE_C = 256.00;
    unsigned int sample_rate = 48000;
    unsigned int time_sec = 5; 
    unsigned int BUFFER_SIZE = sample_rate * time_sec;

    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer.push_back( (float) ((cos((2 * M_PI * MIDDLE_C * i) / 48000) * 1000)));
    }

    int err = wav.writeData(buffer);

    return EXIT_SUCCESS;
}