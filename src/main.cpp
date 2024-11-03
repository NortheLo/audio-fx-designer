#include <iostream>
#include <vector>
#include <cmath>

#include "../include/AudioSystem.hpp"
#include "../include/FDNReverb.hpp"

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

        // move this into a dsp class
        for (size_t i = 0; i < buf.size(); i++) {
            buf[i] = reverb.processSample(buf[i]);
        }

        audio.writeBuffer(buf);
    }


    std::cout << "End\n";
    return EXIT_SUCCESS;
}