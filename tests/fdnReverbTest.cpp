#include <iostream>
#include <vector>
#include <filesystem>

#include "../include/FDNReverb.hpp"
#include "../include/WavWriter.hpp"

int main(int argc, char *argv[]) {
    // create data buffer with impulse
    std::vector<float> buf;
    buf.resize(1000);

    unsigned int index = 0;
    for (auto& elem : buf) {
        if (index == 0) {
            elem = 1;
        }
        else {
            elem = 0;
        }
        index++;
    }

    std::filesystem::path impulsePath = "../tools/impulse.wav";
    WavWriter wavImpulse = WavWriter(impulsePath);
    wavImpulse.writeData(buf);


    // reverb settings 
    int delayLength = 1000;
    FDNReverb reverb(delayLength);

    // move this into a dsp class
    for (size_t i = 0; i < buf.size(); i++) {
        buf[i] = reverb.ProcessSample(buf[i]);
    }

    std::filesystem::path responsePath = "../tools/response.wav";
    WavWriter wavResponse = WavWriter(responsePath);
    wavResponse.writeData(buf);
    

    std::cout << "End\n";
    return EXIT_SUCCESS;
}