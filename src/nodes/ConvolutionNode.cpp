#include "nodes/ConvolutionNode.hpp"
#include <imgui.h>
#include <opencv2/opencv.hpp>
#include <iostream>

ConvolutionNode::ConvolutionNode() {
    name = "Convolution";
    inputs.emplace_back(Pin{0, "Image"});
    outputs.emplace_back(Pin{1, "Image"});
    
    kernelSize = 3;
    kernelScale = 1.0f;
    currentPreset = PRESET_IDENTITY;
    updateKernelSize(kernelSize);
    loadPreset(currentPreset);
}

int ConvolutionNode::getPinType(int pinId) const {
    return 0;
}

void ConvolutionNode::process() {
    if (inputs.empty() || inputs[0].data.empty()) {
        outputs[0].data.release();
        return;
    }

    // Validate and prepare input
    cv::Mat input = inputs[0].data.clone();
    if (input.channels() == 4) {
        cv::cvtColor(input, input, cv::COLOR_BGRA2BGR);
    }

    // Create and validate kernel matrix
    cv::Mat kernelMat(kernelSize, kernelSize, CV_32F);
    try {
        for (int i = 0; i < kernelSize; i++) {
            for (int j = 0; j < kernelSize; j++) {
                kernelMat.at<float>(i, j) = kernel[i][j] * kernelScale;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Kernel access error: " << e.what() << std::endl;
        return;
    }

    // Apply convolution with safety checks
    cv::Mat output;
    try {
        cv::filter2D(input, output, -1, kernelMat, 
                    cv::Point(-1,-1), 0, cv::BORDER_REPLICATE);
    } catch (const cv::Exception& e) {
        std::cerr << "Convolution failed: " << e.what() << std::endl;
        return;
    }

    outputs[0].data = output;
}

void ConvolutionNode::drawUI() {
    // Preset selector
    const char* presets[] = {"Custom", "Identity", "Edge Detect", 
                            "Sharpen", "Emboss", "Blur"};
    if (ImGui::Combo("Preset", (int*)&currentPreset, presets, PRESET_COUNT)) {
        loadPreset(currentPreset);
    }

    // Kernel size control
    int newSize = kernelSize;
    if (ImGui::SliderInt("Kernel Size", &newSize, 3, 9)) {
        updateKernelSize(newSize);
        if (currentPreset != PRESET_CUSTOM) {
            loadPreset(currentPreset);
        }
    }

    // Kernel scale
    ImGui::SliderFloat("Scale", &kernelScale, 0.1f, 2.0f, "%.2f");

    // Kernel matrix editor
    ImGui::Text("Kernel Matrix:");
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 2));
    for (int i = 0; i < kernelSize; i++) {
        ImGui::PushID(i);
        for (int j = 0; j < kernelSize; j++) {
            if (j > 0) ImGui::SameLine();
            ImGui::PushItemWidth(50);
            if (ImGui::InputFloat("", &kernel[i][j], 0, 0, "%.2f")) {
                currentPreset = PRESET_CUSTOM;
            }
            ImGui::PopItemWidth();
        }
        ImGui::PopID();
    }
    ImGui::PopStyleVar();
}

void ConvolutionNode::updateKernelSize(int newSize) {
    // Ensure odd size between 3 and 9
    kernelSize = std::max(3, std::min(9, newSize));
    if (kernelSize % 2 == 0) {
        kernelSize++;
    }
    
    // Resize kernel matrix
    kernel.resize(kernelSize);
    for (auto& row : kernel) {
        row.resize(kernelSize, 0.0f);
    }
}

void ConvolutionNode::loadPreset(FilterPreset preset) {
    updateKernelSize(kernelSize); // Ensure proper size
    
    // Clear existing kernel
    for (auto& row : kernel) {
        std::fill(row.begin(), row.end(), 0.0f);
    }

    switch(preset) {
        case PRESET_IDENTITY:
            kernel[kernelSize/2][kernelSize/2] = 1.0f;
            kernelScale = 1.0f;
            break;
            
        case PRESET_EDGE_DETECT:
            for (int i = 0; i < kernelSize; i++) {
                for (int j = 0; j < kernelSize; j++) {
                    kernel[i][j] = -1.0f;
                }
            }
            kernel[kernelSize/2][kernelSize/2] = 8.0f;
            kernelScale = 1.0f;
            break;
            
        case PRESET_SHARPEN: {
            float center = 5.0f / (kernelSize * kernelSize);
            float edge = -1.0f / (kernelSize * kernelSize);
            for (int i = 0; i < kernelSize; i++) {
                for (int j = 0; j < kernelSize; j++) {
                    kernel[i][j] = (i == kernelSize/2 && j == kernelSize/2) 
                                  ? center : edge;
                }
            }
            kernelScale = 1.0f;
            break;
        }
            
        case PRESET_EMBOSS:
            for (int i = 0; i < kernelSize; i++) {
                for (int j = 0; j < kernelSize; j++) {
                    kernel[i][j] = static_cast<float>(i + j - kernelSize + 1);
                }
            }
            kernelScale = 0.5f;
            break;
            
        case PRESET_BLUR:
            for (auto& row : kernel) {
                std::fill(row.begin(), row.end(), 1.0f);
            }
            normalizeKernel();
            break;
            
        case PRESET_CUSTOM:
        default:
            break;
    }
}

void ConvolutionNode::normalizeKernel() {
    float sum = 0.0f;
    for (const auto& row : kernel) {
        for (float val : row) {
            sum += val;
        }
    }
    
    if (sum != 0.0f) {
        for (auto& row : kernel) {
            for (float& val : row) {
                val /= sum;
            }
        }
    }
}
