// BrightnessContrastNode.hpp
#pragma once
#include "BaseNode.hpp"

class BrightnessContrastNode : public BaseNode {
public:
 int getPinType(int pinId) const override; 
    BrightnessContrastNode();
    void process() override;
    void drawUI() override;
    
private:
    float brightness = 0.0f;
    float contrast = 1.0f;
};
