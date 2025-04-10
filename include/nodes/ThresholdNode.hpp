// ThresholdNode.hpp
#pragma once
#include "BaseNode.hpp"

class ThresholdNode : public BaseNode {
public:
 int getPinType(int pinId) const override; 
    ThresholdNode();
    void process() override;
    void drawUI() override;
    
private:
    float thresholdValue = 128.0f;
    int method = 0;
    std::vector<float> histogram;
    
    void calculateHistogram();
};
