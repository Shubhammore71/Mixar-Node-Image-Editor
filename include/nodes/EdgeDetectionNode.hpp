// EdgeDetectionNode.hpp
#pragma once
#include "BaseNode.hpp"

class EdgeDetectionNode : public BaseNode {
public:
 int getPinType(int pinId) const override; 
    EdgeDetectionNode();
    void process() override;
    void drawUI() override;
    
private:
    int method = 0;
    float threshold1 = 50.0f;  // Changed from double
    float threshold2 = 150.0f;
    int kernelSize = 3;
    bool overlay = false;
};
