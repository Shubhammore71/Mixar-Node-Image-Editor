// ImageInputNode.hpp
#pragma once
#include "BaseNode.hpp"

class ImageInputNode : public BaseNode {
public:
 int getPinType(int pinId) const override; 
    ImageInputNode();
    void process() override;
    void drawUI() override;
    
private:
    std::string filepath;
    cv::Mat originalImage;
};
