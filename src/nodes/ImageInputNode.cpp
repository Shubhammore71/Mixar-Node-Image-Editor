// ImageInputNode.cpp
// This file implements the ImageInputNode class, which is responsible for loading image files into the node graph.
// It inherits from BaseNode and provides functionality to load images using OpenCV.
#include <imgui.h>  // Include Dear ImGui for UI rendering
#include "portable-file-dialogs.h" // Include cross-platform file dialog library

#include "ImageInputNode.hpp"
#include <opencv2/imgcodecs.hpp>

ImageInputNode::ImageInputNode() {
    name = "Image Input";
    outputs.emplace_back(Pin{0, "Image"});
}

int ImageInputNode::getPinType(int pinId) const {
    return 0; // Assuming all pins are image type
}

void ImageInputNode::process() {
    if(!filepath.empty()) {
        originalImage = cv::imread(filepath);
        outputs[0].data = originalImage.clone();
    }
}

void ImageInputNode::drawUI() {
    ImGui::Text("Image Input");
    if(ImGui::Button("Load Image")) {
        auto file = pfd::open_file("Select image", ".", {"Image Files", "*.png *.jpg *.jpeg *.bmp"});
        if(!file.result().empty()) {
            filepath = file.result()[0];
            process();
        }
    }
    ImGui::Text("%s", filepath.c_str());
}
