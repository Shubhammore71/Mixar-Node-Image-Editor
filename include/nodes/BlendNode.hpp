// include/nodes/BlendNode.hpp
#pragma once
#include "BaseNode.hpp"

class BlendNode : public BaseNode {
public:
    BlendNode();
    void process() override;
    void drawUI() override;
    int getPinType(int pinId) const override;

private:
    // Add this declaration
    cv::Mat blendImages(const cv::Mat& base, const cv::Mat& blend);
    
    int blendMode;
    float opacity;
};
