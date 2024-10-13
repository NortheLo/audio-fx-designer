#include "../include/WavWriter.hpp"

#include <fstream>

WavWriter::WavWriter(std::filesystem::path p, uint32_t samplingRate, uint16_t channels) : filePath(p) { 
                            header.channels = channels;
                            header.samplingRate = samplingRate;
                            header.bytesPerSec = sizeof(float) * samplingRate;
                            header.bitsPerSample = 8 * sizeof(float) * channels;
                            header.blockAlign = sizeof(float) * channels;
                        }

int WavWriter::writeData(std::vector<float> dataPoints) {
    unsigned int payloadSize = sizeof(std::vector<float>) + (sizeof(float) * dataPoints.size());
    header.dataSize = payloadSize + sizeHeader;

    // sadly not the proper C++ way doing this, but its much easier this way
    FILE* fp = fopen(filePath.c_str(), "w");
    fwrite(&header, 1, sizeHeader, fp);
    fwrite(static_cast<void*>(dataPoints.data()), 2, payloadSize, fp);
    fclose(fp);
    return 1;
}


WavWriter::~WavWriter() {
}
