// BlurNode.cpp
// Implementation of the BlurNode class which provides Gaussian and directional blur operations
// on input images using OpenCV's blur filters
#include "BlurNode.hpp"
#include <imgui.h>

/**
 * Constructor for BlurNode
 * Initializes a node that applies blur effects to images
 * Sets up input/output pins and default parameter values
 */
BlurNode::BlurNode() {
    name = "Blur";                      // Set display name for the node
    inputs.emplace_back(Pin{0, "Image"}); // Create input pin for source image
    outputs.emplace_back(Pin{1, "Image"}); // Create output pin for blurred image
    radius = 3;                         // Default blur radius
    directional = false;                // Default to standard (non-directional) blur
    angle = 0.0f;                       // Default angle for directional blur
}

/**
 * @brief Defines the data type for each pin
 * @param pinId The ID of the pin to check
 * @return Integer representing the pin type (0 = image type)
 */
int BlurNode::getPinType(int pinId) const {
    return 0; // Image type for all pins
}

/**
 * @brief Processes the input image with blur effect
 * Applies either standard Gaussian blur or directional blur based on settings
 * The processed result is stored in the output pin
 */
void BlurNode::process() {
    if(inputs[0].data.empty()) return;  // Skip processing if no input image
    
    if(directional) {
        // Create and apply a directional blur effect by:
        // 1. Creating a Gaussian kernel
        cv::Mat kernel = cv::getGaussianKernel(radius*2+1, -1);
        
        // 2. Converting to 2D kernel by multiplying with its transpose
        cv::Mat kernelX = kernel * kernel.t();
        
        // 3. Rotating the kernel according to the specified angle
        cv::warpAffine(kernelX, kernelX, 
            cv::getRotationMatrix2D(cv::Point2f(radius, radius), angle, 1.0), 
            kernelX.size());
            
        // 4. Applying the rotated kernel as a custom filter
        cv::filter2D(inputs[0].data, outputs[0].data, -1, kernelX);
    } else {
        // Apply standard Gaussian blur with specified radius
        // Kernel size is calculated as 2*radius+1 to ensure odd dimensions
        cv::GaussianBlur(inputs[0].data, outputs[0].data, 
                        cv::Size(radius*2+1, radius*2+1), 0);
    }
}

/**
 * Renders UI controls for adjusting blur parameters
 * Provides sliders and checkbox for interactive parameter adjustment
 */
void BlurNode::drawUI() {
    ImGui::SliderInt("Radius", &radius, 1, 20);  // Control blur strength/kernel size
    ImGui::Checkbox("Directional", &directional); // Toggle between standard and directional blur
    
    // Only show angle control when directional blur is enabled
    if(directional) {
        ImGui::SliderFloat("Angle", &angle, 0.0f, 360.0f); // Control blur direction angle
    }
}
