#include "../include/FuncGenerator.hpp"

std::vector<float> Pulse::getSamples() {
    buf.resize(length);

    unsigned int index = 0;
    for (auto& elem : buf) {
        if (index == 0) {
            elem = 1.f;
        }
        else {
            elem = 0.f;
        }
        
        index++;
    }

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