#include "../include/WavWriter.hpp"

#include <iostream>
#include <fstream>

int WavWriter::writeData(std::vector<float> dataPoints, uint32_t samplingRate, uint16_t channels) {
    header.channels = channels;
    header.samplingRate = samplingRate;
    header.bytesPerSec = sizeof(float) * samplingRate;
    header.bitsPerSample = 8 * sizeof(float) * channels;
    header.blockAlign = sizeof(float) * channels;


    header.dataSize = sizeof(float) * dataPoints.size();

    // sadly not the proper C++ way doing this, but its much easier this way
    FILE* fp = fopen(filePath.c_str(), "w");
    fwrite(&header, 1, sizeHeader, fp);
    fwrite(static_cast<void*>(dataPoints.data()), 2, header.dataSize, fp);
    fclose(fp);
    std::cout << header.dataSize + sizeHeader << " Bytes written to: " << filePath.string() << std::endl;
    return 1;
}

std::vector<float> WavWriter::readData() {
    // fill in self.header
    // fill vector with payload

    std::ifstream file(filePath, std::ios::binary);

    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    std::cout << header.dataSize + sizeHeader << " Bytes loaded from " << filePath.string() << std::endl;
    std::cout << "Audio Format:\t" << header.audioFormat << "\nSample Rate:\t" << header.samplingRate << "\nChannels:\t" << header.channels << "\n";

    /* this only holds true for float data */
    unsigned int numberSamples = header.dataSize / 4;
    std::vector<float> audioData ;
    audioData.reserve(numberSamples);

    float sample = 0.f;

    for (unsigned int i = 0; i < numberSamples; ++i) {
        file.read(reinterpret_cast<char*>(&sample), sizeof(sample));
        audioData.push_back(sample); // Normalize to range [-1, 1]
    }

    return audioData;
}
