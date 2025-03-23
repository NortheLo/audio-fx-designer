#include <vector>
#include <filesystem>

#include <catch2/catch_test_macros.hpp>

#include "../include/WavWriter.hpp"

float abs_dev = 1e-6;

TEST_CASE("Read Wav File") { 
    std::filesystem::path filePath = "../tools/test.wav";

    WavWriter wav = WavWriter(filePath);
    std::vector<float> res = wav.readData();

    /* Check Header Information first */
    wavHeader hdr = wav.getHeader();
    REQUIRE(hdr.channels == 1);
    REQUIRE(hdr.samplingRate == 48000);
    REQUIRE(hdr.audioFormat == 3);
    REQUIRE(hdr.dataSize == 960000);

    /* Check Payload Data here*/
    REQUIRE(res.size() == 240000);
    REQUIRE((res[0] - 1e3) < abs_dev);
    REQUIRE((res[9] - 9.642805786132812e2) < abs_dev);
    REQUIRE((res[47] - 4.188777923583984) < abs_dev);
    REQUIRE((res[60] - (-3.642266845703125e2)) < abs_dev);
    REQUIRE((res[125] - (-500)) < abs_dev);
    REQUIRE((res[375] - 1e3) < abs_dev);
}