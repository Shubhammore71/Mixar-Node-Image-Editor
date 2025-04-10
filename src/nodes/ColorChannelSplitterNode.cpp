// ColorChannelSplitterNode.cpp
#include "ColorChannelSplitterNode.hpp"
#include <imgui.h>

ColorChannelSplitterNode::ColorChannelSplitterNode() {
    name = "Channel Splitter";
    inputs.emplace_back(Pin{0, "Image"});
    outputs = {{1, "Red"}, {2, "Green"}, {3, "Blue"}, {4, "Alpha"}};
}

int ColorChannelSplitterNode::getPinType(int pinId) const {
    // Input and all outputs are images
    return 0;
}


void ColorChannelSplitterNode::process() {
    if(inputs[0].data.empty()) return;
    
    std::vector<cv::Mat> channels;
    cv::split(inputs[0].data, channels);
    
    for(size_t i = 0; i < outputs.size() && i < channels.size(); ++i) {
        if(grayscaleOutput) {
            outputs[i].data = channels[i];
        } else {
            // Fixed line:
            cv::Mat color(inputs[0].data.size(), CV_8UC3, cv::Scalar(0));
            cv::mixChannels({channels[i]}, {color}, {0, static_cast<int>(i)});
            outputs[i].data = color;
        }
    }
}

void ColorChannelSplitterNode::drawUI() {
    ImGui::Checkbox("Grayscale Output", &grayscaleOutput);
}
