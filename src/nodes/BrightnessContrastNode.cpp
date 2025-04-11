// BrightnessContrastNode.cpp
#include "BrightnessContrastNode.hpp"
#include <imgui.h> 

BrightnessContrastNode::BrightnessContrastNode() {
    name = "Brightness/Contrast";
    inputs.emplace_back(Pin{0, "Image"});
    outputs.emplace_back(Pin{1, "Image"});
}
int BrightnessContrastNode::getPinType(int pinId) const {
    // Both input and output are images
    return 0;
}


void BrightnessContrastNode::process() {
    if (inputs.empty() || inputs[0].data.empty()) {
        return;
    }
    // Create a copy of the input image
    cv::Mat output = inputs[0].data.clone();
    // Apply brightness and contrast
    output.convertTo(output, -1, contrast, brightness);

    outputs[0].data = output;
}


void BrightnessContrastNode::drawUI() {
    ImGui::SliderFloat("Brightness", &brightness, -100.0f, 100.0f);
    ImGui::SliderFloat("Contrast", &contrast, 0.0f, 3.0f);
    if(ImGui::Button("Reset")) {
        brightness = 0.0f;
        contrast = 1.0f;
    }
}
