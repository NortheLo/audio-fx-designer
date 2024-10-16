#include "../include/FuncGenerator.hpp"

std::vector<float> Pulse::getSamples() {
    buf.resize(length);

    // set the conten to all 0.f
    std::fill(buf.begin(), buf.end(), 0.f);
    // set the impulse
    buf[0] = 1.f;
    
    return buf; 
}

/* Returns a buffer of the specified length with new values with an AWGN distribution */
std::vector<float> AWGN::getSamples() {
    buf.resize(length);
    
    // https://en.cppreference.com/w/cpp/numeric/random/normal_distribution
    std::normal_distribution<double> dist(mean, stddev);

    // Add Gaussian noise
    for (auto& x : buf) {
        x = x + dist(generator);
    }

    return buf;
}