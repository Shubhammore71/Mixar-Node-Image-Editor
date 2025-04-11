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

/**
 *  Returns the data type for a specific pin
 * The ID of the pin to check
 *  Integer representing the pin type (0 = image type)
 */

int ThresholdNode::getPinType(int pinId) const {
    return 0; // Image type
}
/**
 *  Calculates the histogram of the input image
 * 
 * This method computes a 256-bin histogram of pixel intensities
 * from the input grayscale image. If the input is a color image,
 * it's converted to grayscale first.
 */

// ThresholdNode.cpp
void ThresholdNode::calculateHistogram() {
    if (inputs.empty() || inputs[0].data.empty()) return;

    // Convert to grayscale if needed
    cv::Mat gray;
    if (inputs[0].data.channels() == 3) {
        cv::cvtColor(inputs[0].data, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = inputs[0].data.clone();
    }

    // Calculate histogram
    const int histSize = 256;
    const float range[] = {0, 256};
    const float* histRange = {range};
    
    cv::Mat hist;
    cv::calcHist(&gray, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);

    // Store in member variable
    histogram.resize(histSize);
    for (int i = 0; i < histSize; i++) {
        histogram[i] = hist.at<float>(i);
    }
}


/**
 *Processes the input image with the selected thresholding method
 * 
 * Applies one of several thresholding algorithms to the input image:
 * - Simple binary thresholding with a fixed value
 * - Adaptive thresholding that adjusts to local image regions
 * - Otsu's method for automatic threshold determination
 */

void ThresholdNode::process() {
    if(inputs[0].data.empty()) return;
    // Convert to grayscale if needed (thresholding requires grayscale input)
    cv::Mat gray;
    if (inputs[0].data.channels() == 3) {
        cv::cvtColor(inputs[0].data, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = inputs[0].data.clone();
    }
    
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
    const char* methods[] = {"Binary", "Binary Inv", "Trunc", "To Zero", "To Zero Inv"};
    ImGui::Combo("Method", &method, methods, IM_ARRAYSIZE(methods));
    
    ImGui::SliderFloat("Value", &thresholdValue, 0.0f, 255.0f);
    
    const char* types[] = {"8UC1", "32FC1"};
    ImGui::Combo("Type", &outputType, types, IM_ARRAYSIZE(types)); // Now valid
}

