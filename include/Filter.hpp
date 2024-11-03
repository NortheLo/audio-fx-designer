#pragma once

#include <vector>
#include <deque>

/*
    Filter Structure: https://vru.vibrationresearch.com/wp-content/uploads/2021/04/iir_order2_df1_ab.png
    Feedback path only in IIR Mode
*/  

class Filter {
    private:
        std::deque<float> fifo;
        std::vector<float> numerator;  // zeros 
        std::vector<float> denumerator; // poles

    public:
        Filter(std::vector<float> a, std::vector<float> b);
        float processSample(float input);
};