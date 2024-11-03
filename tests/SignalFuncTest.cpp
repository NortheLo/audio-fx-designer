#include <vector>

#include <catch2/catch_test_macros.hpp>
#include "../include/FuncGenerator.hpp"

// max deviation from the reference MATLAB value
float abs_dev = 1e-6;

TEST_CASE("Sinus Function Generator") {
    long unsigned len = 1024;
    double freq = 440.f;
    double amp = 2.f;
    int samplingRate = 48000;


    SinTone sinGen = SinTone(len, samplingRate, freq, amp);
    std::vector<float> res = sinGen.getSamples();

    // ref values are from eval_wav_writer.m; index gere + 1 -> MATLAB indices start with 1 
    REQUIRE( res.size() == len);

    REQUIRE( res[0] == 0.0f);
    REQUIRE( abs(res[9] - 0.9909f) < abs_dev);
    REQUIRE( abs(res[14] - 1.4435f) < abs_dev);
    REQUIRE( abs(res[499] - (-0.8986f)) < abs_dev);
    REQUIRE( abs(res[687] - 1.9116f)< abs_dev);
} 

TEST_CASE("Impulse Function Generator") {
    long unsigned int len = 1024;

    Pulse pulseGen = Pulse(len);
    std::vector<float> res = pulseGen.getSamples();

    REQUIRE( res.size() == len);

    REQUIRE( res[0] == 1.0f);
    REQUIRE( res[1] == 0.0f);
    REQUIRE( res[500] == 0.0f);
    REQUIRE( res[len-1] == 0.0f);
} 