// EdgeDetectionNode.cpp
#include "EdgeDetectionNode.hpp"
#include <imgui.h>

EdgeDetectionNode::EdgeDetectionNode() {
    name = "Edge Detection";
    inputs.emplace_back(Pin{0, "Image"});
    outputs.emplace_back(Pin{1, "Image"});
    method = 0;
    threshold1 = 50.0f;
    threshold2 = 150.0f;
    kernelSize = 3;
    overlay = false;
}
int EdgeDetectionNode::getPinType(int pinId) const {
    return 0; // Image type
}

void EdgeDetectionNode::process() {
    if(inputs[0].data.empty()) return;
    
    cv::Mat gray, edges;
    cv::cvtColor(inputs[0].data, gray, cv::COLOR_BGR2GRAY);
    
    if(method == 0) { // Sobel
        cv::Mat gradX, gradY;
        cv::Sobel(gray, gradX, CV_16S, 1, 0, kernelSize);
        cv::Sobel(gray, gradY, CV_16S, 0, 1, kernelSize);
        cv::convertScaleAbs(gradX, gradX);
        cv::convertScaleAbs(gradY, gradY);
        cv::addWeighted(gradX, 0.5, gradY, 0.5, 0, edges);
    } else { // Canny
        cv::Canny(gray, edges, threshold1, threshold2, kernelSize);
    }
    
    if(overlay) {
        cv::Mat colorEdges;
        cv::cvtColor(edges, colorEdges, cv::COLOR_GRAY2BGR);
        cv::addWeighted(inputs[0].data, 0.7, colorEdges, 0.3, 0, outputs[0].data);
    } else {
        cv::cvtColor(edges, outputs[0].data, cv::COLOR_GRAY2BGR);
    }
}

void EdgeDetectionNode::drawUI() {
    const char* methods[] = {"Sobel", "Canny"};
    ImGui::Combo("Method", &method, methods, IM_ARRAYSIZE(methods));
    
    if(method == 1) {
        ImGui::SliderFloat("Threshold 1", &threshold1, 0.0f, 300.0f);
        ImGui::SliderFloat("Threshold 2", &threshold2, 0.0f, 300.0f);
    }
    ImGui::SliderInt("Kernel Size", &kernelSize, 3, 7);
    ImGui::Checkbox("Overlay", &overlay);
}
