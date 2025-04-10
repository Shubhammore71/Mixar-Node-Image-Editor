// BlurNode.hpp
#pragma once
#include "BaseNode.hpp"

class BlurNode : public BaseNode {
public:
 int getPinType(int pinId) const override; 
    BlurNode();
    void process() override;
    void drawUI() override;
    
private:
    int radius = 3;
    bool directional = false;
    float angle = 0.0f;
};
