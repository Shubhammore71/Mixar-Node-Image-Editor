// ImageInputNode.cpp
// src/nodes/ImageInputNode.cpp
#include <imgui.h>
#include "portable-file-dialogs.h"

#include "ImageInputNode.hpp"
#include <opencv2/imgcodecs.hpp>

ImageInputNode::ImageInputNode() {
    name = "Image Input";
    outputs.emplace_back(Pin{0, "Image"});
}

int ImageInputNode::getPinType(int pinId) const {
    // Return 0 for image type, 1 for numeric, etc.
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
