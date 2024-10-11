#include <iostream>
#include <vector>
#include <cmath>

#include "../include/AudioSystem.hpp"
#include "../include/FDNReverb.hpp"

int main(int argc, char *argv[]) {

    // reverb settings 
    int delayLength = 1000;
    FDNReverb reverb(delayLength); // Create a reverb object

    int sampleRate = SAMPLE_RATE;
    float maxDelay = 3.f;

    std::vector<float> buf;
    buf.resize(FRAMES_PER_BUFFER);

    AudioSystem audio = AudioSystem();
    audio.openAudio();
    while(Pa_IsStreamActive(audio.stream)) {
        buf = audio.getBuffer();

        // move this into a dsp class
        for (size_t i = 0; i < buf.size(); i++) {
            buf[i] = reverb.ProcessSample(buf[i]);
        }

        audio.writeBuffer(buf);
    }


    std::cout << "End\n";
    return EXIT_SUCCESS;
}