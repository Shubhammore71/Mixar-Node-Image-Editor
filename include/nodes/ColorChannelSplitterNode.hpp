// ColorChannelSplitterNode.hpp
#pragma once
#include "BaseNode.hpp"

class ColorChannelSplitterNode : public BaseNode {
public:
 int getPinType(int pinId) const override; 
    ColorChannelSplitterNode();
    void process() override;
    void drawUI() override;
    
private:
    bool grayscaleOutput = true;
};
