#include "../include/FDNReverb.hpp"

FDNReverb::FDNReverb(int delayLength) : delayLength(delayLength) {

    // initialize empty delay lines (fifo)
    for (int delayLineLength = 0; delayLineLength < M[0]; delayLineLength++) {
        firstDelayPath.push(0.f);
    }

    for (int delayLineLength = 0; delayLineLength < M[1]; delayLineLength++) {
        secondDelayPath.push(0.f);
    }

    for (int delayLineLength = 0; delayLineLength < M[2]; delayLineLength++) {
        thirdDelayPath.push(0.f);
    }

 }

float FDNReverb::processSample(float input) {
    std::array<float, 4> x = { input * b[0], input * b[1], input * b[2], input * d};
    
    // perform add with feedback values
    x[0] = feedbackBuffer[0] + x[0];
    x[1] = feedbackBuffer[1] + x[1];
    x[1] = feedbackBuffer[2] + x[2];

    // insert values into delay line
    firstDelayPath.push(x[0]);
    secondDelayPath.push(x[1]);
    thirdDelayPath.push(x[2]);

    // create feedback samples through the permutation matrix and its coeff g
    feedbackBuffer[0] = g[0] * (q[0][0] * firstDelayPath.front() + q[0][1] * secondDelayPath.front() + q[0][2] * thirdDelayPath.front());
    feedbackBuffer[1] = g[1] * (q[1][0] * firstDelayPath.front() + q[1][1] * secondDelayPath.front() + q[1][2] * thirdDelayPath.front());
    feedbackBuffer[2] = g[1] * (q[2][0] * firstDelayPath.front() + q[2][1] * secondDelayPath.front() + q[2][2] * thirdDelayPath.front());

    // create sum for output 
    float E = c[0] * firstDelayPath.front() + c[1] * secondDelayPath.front() + c[2] * thirdDelayPath.front(); 
    
    // remove old samples
    firstDelayPath.pop();
    secondDelayPath.pop();
    thirdDelayPath.pop();

    // sum with dry signal
    float output = E + x[3];

    return output;
}