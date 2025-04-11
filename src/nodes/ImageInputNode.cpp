// ImageInputNode.cpp
// This file implements the ImageInputNode class, which is responsible for loading image files into the node graph.
// It inherits from BaseNode and provides functionality to load images using OpenCV.
#include <imgui.h>  // Include Dear ImGui for UI rendering
#include "portable-file-dialogs.h" // Include cross-platform file dialog library

#include "ImageInputNode.hpp"
#include <opencv2/imgcodecs.hpp>

/**
 * Constructor for ImageInputNode
 * Initializes the node with a name and creates an output pin for the loaded image
 */
ImageInputNode::ImageInputNode() {
    name = "Image Input";
    outputs.emplace_back(Pin{0, "Image"});
}

/**
 *  Returns the data type associated with a given pin
 * The ID of the pin to check
 * Integer representing the pin type (0 = image type)
 */

int ImageInputNode::getPinType(int pinId) const {
    return 0; // Assuming all pins are image type
}

void ImageInputNode::process() {
    if(!filepath.empty()) {
        originalImage = cv::imread(filepath);
        outputs[0].data = originalImage.clone();
    }
}

/**
 * Renders the node's UI elements
 * Displays the current filepath and provides a button to open the file selection dialog
 */

void ImageInputNode::drawUI() {
    ImGui::Text("Image Input");
    if(ImGui::Button("Load Image")) {
        auto file = pfd::open_file("Select image", ".", {"Image Files", "*.png *.jpg *.jpeg *.bmp"});
        // If a file was selected (result is not empty)
        if(!file.result().empty()) {
            filepath = file.result()[0];
            process();
        }
    }
    // Display the current filepath in the UI
    ImGui::Text("%s", filepath.c_str());
}
