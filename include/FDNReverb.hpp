#pragma once

#include <queue>
#include <cmath>
#include <array>
#include <vector>

/*
    Implementation of the Feedback Network Reverberator from the Stautner/Puckette Paper, which can be found here:
    https://www.ee.columbia.edu/~dpwe/e4896/papers/StautP82-reverb.pdf
*/

template <typename T, std::size_t Row, std::size_t Col>
using Array2D = std::array<std::array<T, Col>, Row>;

class FDNReverb {
    public:

        FDNReverb(int delayLength);

        float ProcessSample(float input);

    private:
        // maybe as parameter to tune M?
        int delayLength;

        std::queue<float> firstDelayPath; 
        std::queue<float> secondDelayPath; 
        std::queue<float> thirdDelayPath; 

        // Feedforward gain
        float d = 0.5;

        // the delay time of each feedback tap; offset of samples -> int 
        std::array<int, 3> M = {100, 300, 500};

        // coeff for input before mixing with feedback
        std::array<float, 3> b = {1.f, 1.f, 1.f};

        // coeff for the ouput before the feedback matrix
        std::array<float, 3> c = {1.f, 2.f, 5.f};
        
        // coeff for the output after the feedback matrix
        std::array<float, 3> g = {1.f, 1.f, 1.f};

        // feedback permutation matrix 
        float norm = 1/sqrt(2);
        Array2D<float, 3, 3> q {{
            {0.f,         norm, norm},
            {-1.f * norm, 0.f,  0.f},
            {0.f,         norm, -1*  norm}}}; 

        std::array<float, 3> feedbackBuffer; // Buffer to store feedback samples
};