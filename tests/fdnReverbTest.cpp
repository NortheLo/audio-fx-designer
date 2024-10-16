#include <iostream>
#include <vector>
#include <filesystem>

#include "../include/FDNReverb.hpp"
#include "../include/WavWriter.hpp"
#include "../include/FuncGenerator.hpp"

int main(int argc, char *argv[]) {
    unsigned int bufLength = 1000;
    Pulse pulse = Pulse(bufLength);
    std::vector<float> buf = pulse.getSamples();

    std::filesystem::path impulsePath = "../tools/impulse.wav";
    WavWriter wavImpulse = WavWriter(impulsePath);
    wavImpulse.writeData(buf);


    // reverb settings 
    int delayLength = 5;
    FDNReverb reverb(delayLength);

    // move this into a dsp class
    for (size_t i = 0; i < buf.size(); i++) {
        buf[i] = reverb.ProcessSample(buf[i]);
    }

    std::filesystem::path responsePath = "../tools/response.wav";
    WavWriter wavResponse = WavWriter(responsePath);
    wavResponse.writeData(buf);
    
    return EXIT_SUCCESS;
}