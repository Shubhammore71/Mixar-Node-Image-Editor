// BlendNode.cpp
#include "BlendNode.hpp"
#include <imgui.h>

BlendNode::BlendNode() {
    name = "Blend";
    inputs = {{0, "Base"}, {1, "Blend"}};
    outputs.emplace_back(Pin{2, "Image"});
    blendMode = 0;
    opacity = 1.0f;
}
int BlendNode::getPinType(int pinId) const {
    // All pins (2 inputs, 1 output) handle images
    return 0;
}

cv::Mat BlendNode::blend(const cv::Mat& base, const cv::Mat& blend) {
    cv::Mat result;
    switch(blendMode) {
        case 1: { // Multiply
            cv::multiply(base, blend, result, 1/255.0);
            break;
        }
        case 2: { // Screen
            cv::Mat temp;
            cv::multiply(255 - base, 255 - blend, temp, 1/255.0);
            result = 255 - temp;
            break;
        }
        case 3: { // Overlay
            cv::Mat low, high;
            cv::threshold(base, low, 128, 255, cv::THRESH_BINARY);
            cv::multiply(base, blend, high, 1/255.0);
            cv::multiply(255 - (255 - base)*(255 - blend)/255.0, low, low, 1/255.0);
            result = high + low;
            break;
        }
        case 4: // Difference
            cv::absdiff(base, blend, result);
            break;
        default: { // Normal
            cv::addWeighted(base, opacity, blend, 1.0f - opacity, 0, result);
            break;
        }
    }
    return result;
}

void BlendNode::process() {
    if(inputs[0].data.empty() || inputs[1].data.empty()) return;
    
    cv::Mat base, blendImg;
    inputs[0].data.convertTo(base, CV_32FC3, 1/255.0);
    inputs[1].data.convertTo(blendImg, CV_32FC3, 1/255.0);
    
    cv::resize(blendImg, blendImg, base.size());
    
    cv::Mat blended = blend(base, blendImg);
    blended.convertTo(outputs[0].data, CV_8UC3, 255.0);
}

void BlendNode::drawUI() {
    const char* modes[] = {"Normal", "Multiply", "Screen", "Overlay", "Difference"};
    ImGui::Combo("Blend Mode", &blendMode, modes, IM_ARRAYSIZE(modes));
    ImGui::SliderFloat("Opacity", &opacity, 0.0f, 1.0f);
}
