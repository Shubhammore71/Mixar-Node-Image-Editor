// EdgeDetectionNode.hpp
#pragma once
#include "BaseNode.hpp"

class EdgeDetectionNode : public BaseNode {
public:
    EdgeDetectionNode();
    void process() override;
    void drawUI() override;
    int getPinType(int pinId) const override;

private:
    int method = 0;          // 0: Sobel, 1: Canny, 2: Laplacian
    float threshold1 = 50.0f;
    float threshold2 = 150.0f;
    int kernelSize = 3;      // Default to 3 (must be odd: 1, 3, 5, or 7)
    bool overlay = false;
};
