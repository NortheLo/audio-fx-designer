#include <iostream>
#include <cmath>

#include "../include/AudioSystem.hpp"

/*
    This test should feed back the incomming sound to the output device.
*/

int main() {
    std::vector<float> buf;
    buf.resize(FRAMES_PER_BUFFER);
    
    AudioSystem audio = AudioSystem();
    audio.openAudio();

    while(Pa_IsStreamActive(audio.stream)) {
        buf = audio.getBuffer();
        audio.writeBuffer(buf);
    }
    return 0;
}