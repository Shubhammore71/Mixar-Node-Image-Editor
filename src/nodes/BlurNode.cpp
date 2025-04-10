// BlurNode.cpp
#include "BlurNode.hpp"
#include <imgui.h>

BlurNode::BlurNode() {
    name = "Blur";
    inputs.emplace_back(Pin{0, "Image"});
    outputs.emplace_back(Pin{1, "Image"});
    radius = 3;
    directional = false;
    angle = 0.0f;
}

int BlurNode::getPinType(int pinId) const {
    return 0; // Image type for all pins
}


void BlurNode::process() {
    if(inputs[0].data.empty()) return;
    
    if(directional) {
        cv::Mat kernel = cv::getGaussianKernel(radius*2+1, -1);
        cv::Mat kernelX = kernel * kernel.t();
        cv::warpAffine(kernelX, kernelX, 
            cv::getRotationMatrix2D(cv::Point2f(radius, radius), angle, 1.0), 
            kernelX.size());
        cv::filter2D(inputs[0].data, outputs[0].data, -1, kernelX);
    } else {
        cv::GaussianBlur(inputs[0].data, outputs[0].data, 
                        cv::Size(radius*2+1, radius*2+1), 0);
    }
}

void BlurNode::drawUI() {
    ImGui::SliderInt("Radius", &radius, 1, 20);
    ImGui::Checkbox("Directional", &directional);
    if(directional) {
        ImGui::SliderFloat("Angle", &angle, 0.0f, 360.0f);
    }
}
