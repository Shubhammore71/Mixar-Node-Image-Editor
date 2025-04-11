// ColorChannelSplitterNode.cpp
// This file implements the ColorChannelSplitterNode class which separates an input image
// into its individual color channels (red, green, blue, and alpha if available)
#include "ColorChannelSplitterNode.hpp"
#include <imgui.h>

/**
 * Constructor for ColorChannelSplitterNode
 * Initializes a node that splits an RGB/RGBA image into its component channels
 * Creates one input pin for the source image and four output pins for each color channel
 */
ColorChannelSplitterNode::ColorChannelSplitterNode() {
    name = "Channel Splitter";               // Set the display name for the node
    inputs.emplace_back(Pin{0, "Image"});    // Create an input pin for the source image
    
    // Create four output pins for R, G, B, and Alpha channels
    outputs = {{1, "Red"}, {2, "Green"}, {3, "Blue"}, {4, "Alpha"}};
}

/**
 * Specifies the data type for pins
 * The ID of the pin to check
 * Integer representing the pin type (0 = image type)
 */
int ColorChannelSplitterNode::getPinType(int pinId) const {
    // Input and all outputs are images (type 0)
    return 0;
}

/**
 * Processes the input image by splitting it into individual channels
 * 
 * Separates the input image into its component channels (R, G, B, and Alpha if present).
 * Each channel can be output either as a grayscale image or as a colorized image
 * where only the respective channel contains data.
 */
void ColorChannelSplitterNode::process() {
    if(inputs[0].data.empty()) return;  // Skip processing if no input image
    
    // Split the input image into individual channel matrices
    std::vector<cv::Mat> channels;
    cv::split(inputs[0].data, channels);
    
    // Process each channel and assign to the corresponding output pin
    for(size_t i = 0; i < outputs.size() && i < channels.size(); ++i) {
        if(grayscaleOutput) {
            // Option 1: Output each channel as a grayscale image
            outputs[i].data = channels[i];
        } else {
            // Option 2: Output each channel as a colorized image
            // Create an empty 3-channel (color) image filled with zeros
            cv::Mat color(inputs[0].data.size(), CV_8UC3, cv::Scalar(0));
            
            // Place the channel data in the appropriate color channel of the output
            // For example: channel 0 (red) goes into the red channel of the color image
            cv::mixChannels({channels[i]}, {color}, {0, static_cast<int>(i)});
            outputs[i].data = color;
        }
    }
}

/**
 *  Renders UI controls for the node
 * 
 * Provides a checkbox to toggle between grayscale and colorized output modes
 */
void ColorChannelSplitterNode::drawUI() {
    ImGui::Checkbox("Grayscale Output", &grayscaleOutput);  // Toggle between output modes
}
