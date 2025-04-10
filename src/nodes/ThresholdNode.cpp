// ThresholdNode.cpp
#include "ThresholdNode.hpp"
#include <imgui.h>

ThresholdNode::ThresholdNode() {
    name = "Threshold";
    inputs.emplace_back(Pin{0, "Image"});
    outputs.emplace_back(Pin{1, "Image"});
    thresholdValue = 128.0f;
    method = 0;
}

int ThresholdNode::getPinType(int pinId) const {
    return 0; // Image type
}


void ThresholdNode::calculateHistogram() {
    if(inputs[0].data.empty()) return;
    
    cv::Mat gray;
    cv::cvtColor(inputs[0].data, gray, cv::COLOR_BGR2GRAY);
    
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range};
    cv::calcHist(&gray, 1, 0, cv::Mat(), gray, 1, &histSize, &histRange);
    
    histogram.resize(histSize);
    for(int i = 0; i < histSize; ++i) {
        histogram[i] = gray.at<float>(i);
    }
}

void ThresholdNode::process() {
    if(inputs[0].data.empty()) return;
    
    cv::Mat gray;
    cv::cvtColor(inputs[0].data, gray, cv::COLOR_BGR2GRAY);
    
    cv::Mat thresholded;
    switch(method) {
        case 1: // Adaptive
            cv::adaptiveThreshold(gray, thresholded, 255, 
                cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);
            break;
        case 2: // Otsu
            cv::threshold(gray, thresholded, 0, 255, 
                cv::THRESH_BINARY | cv::THRESH_OTSU);
            break;
        default: // Simple
            cv::threshold(gray, thresholded, thresholdValue, 255, 
                cv::THRESH_BINARY);
    }
    
    outputs[0].data = thresholded;
}

void ThresholdNode::drawUI() {
    if(method == 0) {
        ImGui::SliderFloat("Threshold", &thresholdValue, 0.0f, 255.0f);
    }
    
    const char* methods[] = {"Binary", "Adaptive", "Otsu"};
    ImGui::Combo("Method", &method, methods, IM_ARRAYSIZE(methods));
    
   
    
    if(ImGui::CollapsingHeader("Histogram")) {
        calculateHistogram();
        ImGui::PlotHistogram("##hist", histogram.data(), 
                           histogram.size(), 0, NULL, 0.0f, 255.0f, 
                           ImVec2(200, 80));
    }
}
