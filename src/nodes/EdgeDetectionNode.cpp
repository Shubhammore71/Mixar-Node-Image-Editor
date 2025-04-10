// EdgeDetectionNode.cpp
#include "nodes/EdgeDetectionNode.hpp"
#include <imgui.h>
#include <opencv2/opencv.hpp>

EdgeDetectionNode::EdgeDetectionNode() {
    name = "Edge Detection";
    inputs.emplace_back(Pin{0, "Image"});
    outputs.emplace_back(Pin{1, "Image"});
    
    // Default values - ensure kernelSize is valid
    method = 0;
    threshold1 = 50.0f;
    threshold2 = 150.0f;
    kernelSize = 3;  // Set a valid default (1, 3, 5, or 7)
    overlay = false;
}

int EdgeDetectionNode::getPinType(int pinId) const {
    return 0; // All pins are image type
}

void EdgeDetectionNode::process() {
    if (inputs.empty() || inputs[0].data.empty()) {
        return;
    }

    // Get input image
    cv::Mat inputImage = inputs[0].data.clone();
    cv::Mat edges, outputImage;
    
    // Convert to grayscale if it's color
    cv::Mat grayImage;
    if (inputImage.channels() == 3) {
        cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);
    } else {
        grayImage = inputImage.clone();
    }

    // Apply edge detection based on selected method
    switch (method) {
        case 0: { // Sobel
            // CRITICAL FIX: Ensure kernel size is odd and not larger than 31
            int validKernelSize = kernelSize;
            if (validKernelSize % 2 == 0) {
                validKernelSize += 1; // Make it odd
            }
            // Restrict to common Sobel kernel sizes: 1, 3, 5, 7
            validKernelSize = std::min(7, std::max(1, validKernelSize));
            
            // Calculate gradients
            cv::Mat gradX, gradY, absGradX, absGradY;
            cv::Sobel(grayImage, gradX, CV_16S, 1, 0, validKernelSize);
            cv::Sobel(grayImage, gradY, CV_16S, 0, 1, validKernelSize);
            
            // Convert to absolute values
            cv::convertScaleAbs(gradX, absGradX);
            cv::convertScaleAbs(gradY, absGradY);
            
            // Combine gradients
            cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, edges);
            break;
        }
        case 1: { // Canny
            // CRITICAL FIX: Ensure kernel size is odd and within valid range for Canny
            int validKernelSize = (kernelSize % 2 == 0) ? kernelSize + 1 : kernelSize;
            validKernelSize = std::min(7, std::max(3, validKernelSize)); // Canny accepts 3, 5, 7
            
            cv::Canny(grayImage, edges, threshold1, threshold2, validKernelSize);
            break;
        }
        case 2: { // Laplacian
            // CRITICAL FIX: Ensure kernel size is odd and not larger than 31
            int validKernelSize = (kernelSize % 2 == 0) ? kernelSize + 1 : kernelSize;
            validKernelSize = std::min(31, std::max(1, validKernelSize));
            
            cv::Laplacian(grayImage, edges, CV_8U, validKernelSize);
            break;
        }
    }

    // Create output image
    if (overlay && inputImage.channels() == 3) {
        // Convert edges to color for overlay
        cv::cvtColor(edges, outputImage, cv::COLOR_GRAY2BGR);
        
        // Blend with original image
        cv::addWeighted(inputImage, 0.7, outputImage, 0.3, 0, outputImage);
    } else if (overlay && inputImage.channels() == 1) {
        // For grayscale, just blend directly
        cv::addWeighted(inputImage, 0.7, edges, 0.3, 0, outputImage);
    } else {
        outputImage = edges.clone();
    }

    outputs[0].data = outputImage;
}

void EdgeDetectionNode::drawUI() {
    // Edge detection method
    const char* methods[] = {"Sobel", "Canny", "Laplacian"};
    ImGui::Combo("Method", &method, methods, IM_ARRAYSIZE(methods));
    
    // Parameters for each method
    if (method == 0) { // Sobel
        const char* kernelSizes[] = {"1x1", "3x3", "5x5", "7x7"};
        int kernelIndex = 0;
        
        // Convert kernel size to index
        if (kernelSize == 1) kernelIndex = 0;
        else if (kernelSize == 3) kernelIndex = 1;
        else if (kernelSize == 5) kernelIndex = 2;
        else if (kernelSize == 7) kernelIndex = 3;
        else kernelIndex = 1; // Default to 3x3
        
        // Display kernel size choices as dropdown
        if (ImGui::Combo("Kernel Size", &kernelIndex, kernelSizes, IM_ARRAYSIZE(kernelSizes))) {
            // Convert index back to kernel size
            if (kernelIndex == 0) kernelSize = 1;
            else if (kernelIndex == 1) kernelSize = 3;
            else if (kernelIndex == 2) kernelSize = 5;
            else if (kernelIndex == 3) kernelSize = 7;
        }
    } 
    else if (method == 1) { // Canny
        ImGui::SliderFloat("Threshold 1", &threshold1, 0.0f, 300.0f);
        ImGui::SliderFloat("Threshold 2", &threshold2, 0.0f, 300.0f);
        
        const char* kernelSizes[] = {"3x3", "5x5", "7x7"};
        int kernelIndex = 0;
        
        // Convert kernel size to index
        if (kernelSize == 3) kernelIndex = 0;
        else if (kernelSize == 5) kernelIndex = 1;
        else if (kernelSize == 7) kernelIndex = 2;
        else kernelIndex = 0; // Default to 3x3
        
        // Display kernel size choices as dropdown
        if (ImGui::Combo("Kernel Size", &kernelIndex, kernelSizes, IM_ARRAYSIZE(kernelSizes))) {
            // Convert index back to kernel size
            if (kernelIndex == 0) kernelSize = 3;
            else if (kernelIndex == 1) kernelSize = 5;
            else if (kernelIndex == 2) kernelSize = 7;
        }
    }
    else if (method == 2) { // Laplacian
        const char* kernelSizes[] = {"1x1", "3x3", "5x5", "7x7", "9x9", "11x11"};
        int kernelIndex = 1; // Default to 3x3
        
        // Convert kernel size to index
        if (kernelSize == 1) kernelIndex = 0;
        else if (kernelSize == 3) kernelIndex = 1;
        else if (kernelSize == 5) kernelIndex = 2;
        else if (kernelSize == 7) kernelIndex = 3;
        else if (kernelSize == 9) kernelIndex = 4;
        else if (kernelSize == 11) kernelIndex = 5;
        
        // Display kernel size choices as dropdown
        if (ImGui::Combo("Kernel Size", &kernelIndex, kernelSizes, IM_ARRAYSIZE(kernelSizes))) {
            // Convert index back to kernel size
            kernelSize = 1 + kernelIndex * 2; // Generates 1, 3, 5, 7, 9, 11
        }
    }
    
    // Overlay option
    ImGui::Checkbox("Overlay on Original", &overlay);
}
