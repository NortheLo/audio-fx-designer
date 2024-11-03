#pragma once

#include <vector>
#include <random>

class SignalFunction {
    protected:
        unsigned int length;
        std::vector<float> buf;

    public:
        SignalFunction(unsigned int length) : length(length) { };
        virtual ~SignalFunction() { };
        virtual std::vector<float> getSamples() = 0;
};

class Pulse : public SignalFunction {
    public:
        /* Create a vector with one Pulse @ idx = 0 of value 1 */
        Pulse(unsigned int length) : SignalFunction(length) {  }
        ~Pulse() { };
        std::vector<float> getSamples();
};

class AWGN : public SignalFunction {
    private:
        double mean = 0.f;
        double stddev = 0.1;
        std::default_random_engine generator;
    
    public:
        /* Create a vector with all white gaussian noise */
        AWGN(unsigned int length, double mean = 0.f, double stddev = 0.1) : 
            SignalFunction(length), mean(mean), stddev(stddev) { };
        ~AWGN() { };
        std::vector<float> getSamples();
};

class SinTone : public SignalFunction {
    private:
        float sampleRate = 44100;
        double frequency = 440.f;
        double amplitude = 1.f;
    public:
        SinTone(unsigned int length, float sampleRate, double frequency, double amplitude) 
        : SignalFunction(length), sampleRate(sampleRate), frequency(frequency), amplitude(amplitude) { };
        ~SinTone() { };
        std::vector<float> getSamples();
};