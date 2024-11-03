#include "../include/WavWriter.hpp"

#include <iostream>
#include <fstream>

WavWriter::WavWriter(std::filesystem::path p, uint32_t samplingRate, uint16_t channels) : filePath(p) { 
                            header.channels = channels;
                            header.samplingRate = samplingRate;
                            header.bytesPerSec = sizeof(float) * samplingRate;
                            header.bitsPerSample = 8 * sizeof(float) * channels;
                            header.blockAlign = sizeof(float) * channels;
                        }

int WavWriter::writeData(std::vector<float> dataPoints) {
    header.dataSize = sizeof(float) * dataPoints.size();

    // sadly not the proper C++ way doing this, but its much easier this way
    FILE* fp = fopen(filePath.c_str(), "w");
    fwrite(&header, 1, sizeHeader, fp);
    fwrite(static_cast<void*>(dataPoints.data()), 2, header.dataSize, fp);
    fclose(fp);
    std::cout << header.dataSize + sizeHeader << " Bytes written to: " << filePath.string() << std::endl;
    return 1;
}

// std::vector<float> WavWriter::readData() {
//     FILE* fp;
//     fp = fopen(filePath.c_str(), "rb");

//     while (1) {
//         fread(&header, sizeof(header), 1, fp);
//         if(feof(fp)) {
//             break;
//         }
//     }

//     // not working because we are not considering the riff chunk size
//     std::cout << header.audioFormat << std::endl << header.samplingRate << std::endl;

//     std::vector<float> hi = {0.f};
//     return hi;
// }

WavWriter::~WavWriter() {
}
