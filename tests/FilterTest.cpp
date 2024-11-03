#include <iostream>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "../include/Filter.hpp"
#include "../include/FuncGenerator.hpp"

// max deviation from the reference MATLAB value
float abs_dev = 1e-6;

TEST_CASE("FIR Filter Test") {
    unsigned int len = 1000;
    Pulse pulse = Pulse(len);
    std::vector<float> buf = pulse.getSamples();

    std::vector<float> a = {1, 0.2};
    std::vector<float> b = {1};

    Filter filter = Filter(a, b);

    // move this into a dsp class
    for (size_t i = 0; i < buf.size(); i++) {
        buf[i] = filter.processSample(buf[i]);
    }

    // ref values are from eval_wav_writer.m; index gere + 1 -> MATLAB indices start with 1 
    REQUIRE( buf.size() == len);

    REQUIRE( abs(buf[0] - 1.f) < abs_dev);
    REQUIRE( abs(buf[1] - (-0.2f)) < abs_dev);
    REQUIRE( abs(buf[2] - 0.04) < abs_dev);
    REQUIRE( abs(buf[3] - (-0.008)) < abs_dev);
    REQUIRE( abs(buf[4] - 0.0016) < abs_dev);
}

TEST_CASE("IIR Filter Test") {
    unsigned int len = 1000;
    Pulse pulse = Pulse(len);
    std::vector<float> buf = pulse.getSamples();

    std::vector<float> a = {2, 3};
    std::vector<float> b = {1, 0.2};

    Filter filter = Filter(a, b);

    // move this into a dsp class
    for (size_t i = 0; i < buf.size(); i++) {
        buf[i] = filter.processSample(buf[i]);
    }

    // ref values are from eval_wav_writer.m; index gere + 1 -> MATLAB indices start with 1 
    REQUIRE( buf.size() == len);

    REQUIRE( abs(buf[0] - 2.f) < abs_dev);
    REQUIRE( abs(buf[1] - 2.6) < abs_dev);
    REQUIRE( abs(buf[2] - (-0.52)) < abs_dev);
    REQUIRE( abs(buf[3] - 0.104) < abs_dev);
    REQUIRE( abs(buf[4] - (-0.208)) < abs_dev);
    REQUIRE( abs(buf[5] - (0.00416)) < abs_dev);

}