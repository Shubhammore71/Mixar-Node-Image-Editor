// BlendNode.hpp
#pragma once
#include "BaseNode.hpp"

class BlendNode : public BaseNode {
public:
 int getPinType(int pinId) const override; 
    BlendNode();
    void process() override;
    void drawUI() override;
    
private:
    int blendMode = 0;
    float opacity = 1.0f;
    
    cv::Mat blend(const cv::Mat& base, const cv::Mat& blend);
};
