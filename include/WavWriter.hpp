#pragma once

#include <cstdint>
#include "vector"

typedef struct WAV_HEADER {

} wav_hdr;


class WavWriter
{
    public:
        WavWriter(uint32_t samplingRate = 48000, uint16_t channels = 1);
        int writeData(std::vector<float> dataPoints);
        ~WavWriter();
    private:
        uint8_t  RIFF[4] = {'R', 'I', 'F', 'F'};        // RIFF Header Magic header
        uint32_t chunkSize;                             // RIFF Chunk Size
        uint8_t  WAVE[4] = {'W', 'A', 'V', 'E'};        // WAVE Header
        uint8_t  fmt[4] = {'f', 'm', 't', ' '};         // FMT header
        uint32_t subchunksize = 16;                     // Size of the fmt chunk
        uint16_t audioFormat = 3;                       // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM, 3=IEEE754 float
        uint16_t channels = 1;                          // Number of channels 1=Mono 2=Stereo
        uint32_t samplingRate = 48000;                  // Sampling Frequency in Hz
        uint32_t bytesPerSec   = 48000 * 4;             // bytes per second
        uint16_t blockAlign = 2;                        // 2=16-bit mono, 4=16-bit stereo
        uint16_t bitsPerSample = 1 * 32;                // Number of bits per sample NbrChannels * BitsPerSample
        uint8_t  dataBlocID[4] = {'d', 'a', 't', 'a'};  // "data"  string
        uint32_t dataSize;                              // Sampled data length

};

