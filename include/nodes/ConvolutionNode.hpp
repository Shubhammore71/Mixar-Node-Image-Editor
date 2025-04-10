// ConvolutionNode.hpp
#pragma once
#include "BaseNode.hpp"

class ConvolutionNode : public BaseNode {
public:
 int getPinType(int pinId) const override; 
    ConvolutionNode();
    void process() override;
    void drawUI() override;
    
private:
    int kernelSize = 3;
    float kernel[5][5];
    int preset = 0;
    
    void loadPreset();
};
