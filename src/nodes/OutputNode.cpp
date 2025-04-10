// src/nodes/OutputNode.cpp
#include "nodes/OutputNode.hpp"
#include <opencv2/opencv.hpp>
#include <imgui.h>

OutputNode::OutputNode() {
    name = "Output";
    inputs.emplace_back(Pin{0, "Image"});
}
int OutputNode::getPinType(int pinId) const {
    // Input pin (image)
    return 0;
}

void OutputNode::process() {
    if (inputs.empty() || inputs[0].data.empty()) {
        return;
    }

    // Get input image
    cv::Mat inputImage = inputs[0].data;
    
    // Create OpenGL texture if needed
    if (textureID == 0) {
        glGenTextures(1, &textureID);
    }
    
    // Explicitly flip the image vertically
    cv::Mat flippedImage;
    cv::flip(inputImage, flippedImage, 0);  // 0 = flip around x-axis
    
    // Convert BGR to RGB format for OpenGL
    cv::Mat rgbImage;
    cv::cvtColor(flippedImage, rgbImage, cv::COLOR_BGR2RGB);
    
    // Bind texture and set parameters
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
                 rgbImage.cols, rgbImage.rows, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, rgbImage.data);
}






void OutputNode::drawUI() {
    // Display debugging info
    ImGui::Text("Input image: %dx%d", 
        inputs.empty() || inputs[0].data.empty() ? 0 : inputs[0].data.cols,
        inputs.empty() || inputs[0].data.empty() ? 0 : inputs[0].data.rows);
    ImGui::Text("TextureID: %d", textureID);
    
    // Display the image with flipped UV coordinates
    if (textureID != 0 && !inputs.empty() && !inputs[0].data.empty()) {
        float width = 300.0f;
        float aspect = (float)inputs[0].data.rows / inputs[0].data.cols;
        float height = width * aspect;
        
        ImGui::Image(
            (ImTextureID)(intptr_t)textureID,
            ImVec2(width, height),
            ImVec2(0, 1),  // Bottom-left UV (flipped vertically)
            ImVec2(1, 0)   // Top-right UV (flipped vertically)
        );
    } else {
        ImGui::Text("No image to display");
    }
}



