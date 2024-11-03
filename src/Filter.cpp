#include "../include/Filter.hpp"

#include <iostream>

Filter::Filter(std::vector<float> a, std::vector<float> b) : numerator(a), denumerator(b) {
    // get longest delay line tap
    int len = a.size() >= b.size() ? a.size() : b.size();

    for (int i = 0; i < len; i++) {
        fifo.push_front(0.f);
    }
}

float Filter::processSample(float input) {
    // Update the FIFO with the new input sample
    fifo.push_back(input);
    fifo.pop_front(); 
    

    // Calculate output using the IIR filter formula
    float output = 0.0f;

    // Feedforward part (numerator)
    for (long unsigned int i = 0; i < numerator.size(); i++) {
        output += numerator[i] * fifo[fifo.size() - 1 - i]; 
    }

    // Feedback part (denominator)
    for (long unsigned int i = 1; i < denumerator.size(); i++) {
        output -= denumerator[i] * fifo[i - 1]; 
    }

    return output;
}