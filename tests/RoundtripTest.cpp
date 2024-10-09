#include <iostream>
#include <unistd.h> // For UNIX sleep function; deprectaded but could be useful for OpenBSD port
#include <cmath>

#include "../include/AudioSystem.hpp"
#include "../include/LowPass.hpp"


int main() {
    float* buf;
    AudioSystem audio = AudioSystem();
    audio.openAudio();
    while(Pa_IsStreamActive(audio.stream)) {

        buf = audio.getBuffer();
        // for(size_t i = 0; i < 256; i++) {
        //     lp.applyEffect(buf[i], buf[i]);
        // }

        audio.writeBuffer(buf, 256);
        usleep(1); 
    }
    return 0;
}