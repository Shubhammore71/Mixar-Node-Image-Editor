// ThresholdNode.hpp
#pragma once
#include "BaseNode.hpp"
#include <vector>  // Add this

class ThresholdNode : public BaseNode {
public:
    ThresholdNode();
    void process() override;
    void drawUI() override;
    int getPinType(int pinId) const override;

private:
    // Add these declarations
    void calculateHistogram();  // Method declaration
    std::vector<float> histogram;  // Member variable
    
    int method = 0;
    float thresholdValue = 128.0f;
    int outputType = 0;
};
