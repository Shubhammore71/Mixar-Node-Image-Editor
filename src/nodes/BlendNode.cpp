#include "BlendNode.hpp"
#include <imgui.h>
#include <opencv2/opencv.hpp>

BlendNode::BlendNode() {
    name = "Blend";
    inputs = {{0, "Base"}, {1, "Blend"}};
    outputs.emplace_back(Pin{2, "Image"});
    blendMode = 0;
    opacity = 1.0f;
}

int BlendNode::getPinType(int pinId) const {
    return 0; // All pins handle images
}

void BlendNode::process() {
    if (inputs.size() < 2 || inputs[0].data.empty() || inputs[1].data.empty()) return;

    // Convert inputs to 3-channel if grayscale
    cv::Mat base, blend;
    if (inputs[0].data.channels() == 1) {
        cv::cvtColor(inputs[0].data, base, cv::COLOR_GRAY2BGR);
    } else {
        base = inputs[0].data.clone();
    }

    if (inputs[1].data.channels() == 1) {
        cv::cvtColor(inputs[1].data, blend, cv::COLOR_GRAY2BGR);
    } else {
        blend = inputs[1].data.clone();
    }

    // Ensure same size
    if (base.size() != blend.size()) {
        cv::resize(blend, blend, base.size(), 0, 0, cv::INTER_LINEAR);
    }

    // Convert to floating point with normalization
    cv::Mat baseFloat, blendFloat;
    base.convertTo(baseFloat, CV_32FC3, 1.0/255.0);
    blend.convertTo(blendFloat, CV_32FC3, 1.0/255.0);

    cv::Mat resultFloat = blendImages(baseFloat, blendFloat);

    // Convert back to original format
    resultFloat.convertTo(outputs[0].data, CV_8UC3, 255.0);
}

cv::Mat BlendNode::blendImages(const cv::Mat& base, const cv::Mat& blend) {
    cv::Mat result(base.size(), CV_32FC3);
    
    switch(blendMode) {
        case 1: // Multiply
            cv::multiply(base, blend, result);
            break;
            
        case 2: // Screen
            result = cv::Scalar::all(1.0) - 
                    (cv::Scalar::all(1.0) - base).mul(cv::Scalar::all(1.0) - blend);
            break;
            
        case 3: // Overlay
            for (int y = 0; y < base.rows; y++) {
                for (int x = 0; x < base.cols; x++) {
                    const cv::Vec3f& b = base.at<cv::Vec3f>(y, x);
                    const cv::Vec3f& s = blend.at<cv::Vec3f>(y, x);
                    cv::Vec3f& r = result.at<cv::Vec3f>(y, x);
                    
                    for (int c = 0; c < 3; c++) {
                        r[c] = (b[c] < 0.5f) ? 
                            2 * b[c] * s[c] : 
                            1 - 2 * (1 - b[c]) * (1 - s[c]);
                    }
                }
            }
            break;
            
        case 4: // Difference
            cv::absdiff(base, blend, result);
            break;
            
        default: // Normal
            cv::addWeighted(base, opacity, blend, 1.0f - opacity, 0.0f, result);
            break;
    }
    
    return result;
}

void BlendNode::drawUI() {
    const char* modes[] = {"Normal", "Multiply", "Screen", "Overlay", "Difference"};
    ImGui::Combo("Blend Mode", &blendMode, modes, IM_ARRAYSIZE(modes));
    
    if (blendMode == 0) { // Only show opacity for Normal mode
        ImGui::SliderFloat("Opacity", &opacity, 0.0f, 1.0f);
    }
}
