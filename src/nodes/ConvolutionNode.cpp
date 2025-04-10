// ConvolutionNode.cpp
#include "ConvolutionNode.hpp"
#include <imgui.h>

ConvolutionNode::ConvolutionNode() {
    name = "Convolution Filter";
    inputs.emplace_back(Pin{0, "Image"});
    outputs.emplace_back(Pin{1, "Image"});
    kernelSize = 3;
    preset = 0;
    memset(kernel, 0, sizeof(kernel));
    kernel[1][1] = 1.0f; // Identity kernel
}
int ConvolutionNode::getPinType(int pinId) const {
    return 0; // Image type
}


void ConvolutionNode::loadPreset() {
    switch(preset) {
        case 1: // Sharpen
            kernel[0][0] = 0; kernel[0][1] = -1; kernel[0][2] = 0;
            kernel[1][0] = -1; kernel[1][1] = 5; kernel[1][2] = -1;
            kernel[2][0] = 0; kernel[2][1] = -1; kernel[2][2] = 0;
            break;
        case 2: // Emboss
            kernel[0][0] = -2; kernel[0][1] = -1; kernel[0][2] = 0;
            kernel[1][0] = -1; kernel[1][1] = 1; kernel[1][2] = 1;
            kernel[2][0] = 0; kernel[2][1] = 1; kernel[2][2] = 2;
            break;
        default: // Identity
            memset(kernel, 0, sizeof(kernel));
            kernel[1][1] = 1;
    }
}

void ConvolutionNode::process() {
    if(inputs[0].data.empty()) return;
    
    cv::Mat kernelMat(kernelSize, kernelSize, CV_32F);
    for(int i = 0; i < kernelSize; ++i) {
        for(int j = 0; j < kernelSize; ++j) {
            kernelMat.at<float>(i, j) = kernel[i][j];
        }
    }
    
    cv::filter2D(inputs[0].data, outputs[0].data, -1, kernelMat);
}

void ConvolutionNode::drawUI() {
    const char* presets[] = {"Custom", "Sharpen", "Emboss"};
    if(ImGui::Combo("Preset", &preset, presets, IM_ARRAYSIZE(presets))) {
        loadPreset();
    }
    
    ImGui::SliderInt("Kernel Size", &kernelSize, 3, 5);
    
    ImGui::BeginTable("Kernel", kernelSize, ImGuiTableFlags_Borders);
    for(int i = 0; i < kernelSize; ++i) {
        ImGui::TableNextRow();
        for(int j = 0; j < kernelSize; ++j) {
            ImGui::TableSetColumnIndex(j);
            ImGui::PushID(i*kernelSize + j);
            ImGui::InputFloat("##cell", &kernel[i][j], 0.1f);
            ImGui::PopID();
        }
    }
    ImGui::EndTable();
}
