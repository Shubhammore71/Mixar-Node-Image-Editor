#include "nodes/OutputNode.hpp"
#include <imgui.h>
#include "portable-file-dialogs.h"
#include <opencv2/imgcodecs.hpp>
#include <filesystem>


OutputNode::OutputNode() {
    name = "Output";
    inputs.emplace_back(Pin{0, "Image"});
    glGenTextures(1, &textureID);
}

OutputNode::~OutputNode() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }
}

void OutputNode::process() {
    if (inputs.empty() || inputs[0].data.empty()) return;

    cv::Mat processedImage;
    if (inputs[0].data.channels() == 1) {
        cv::cvtColor(inputs[0].data, processedImage, cv::COLOR_GRAY2BGR);
    } else {
        processedImage = inputs[0].data.clone();
    }

    cv::flip(processedImage, processedImage, 0);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
                processedImage.cols, processedImage.rows, 0,
                GL_BGR, GL_UNSIGNED_BYTE, processedImage.data);
}

void OutputNode::drawUI() {
    ImGui::Text("Output Settings");
    
    const char* formats[] = {"PNG", "JPEG", "BMP"};
    ImGui::Combo("Format", &format, formats, IM_ARRAYSIZE(formats));

    if (format == 1) { // JPEG
        ImGui::SliderInt("Quality", &quality, 1, 100);
    } else if (format == 0) { // PNG
        ImGui::SliderInt("Compression", &compression, 0, 9);
    }

    if (ImGui::Button("Save Image")) {
        auto file = pfd::save_file("Save image", "",
            { "Image Files", "*.png *.jpg *.jpeg *.bmp" });
        if (!file.result().empty()) {
            saveImage(file.result());
        }
    }

    if (!inputs[0].data.empty() && textureID != 0) {
        float aspect = static_cast<float>(inputs[0].data.rows) / inputs[0].data.cols;
        ImGui::Image((ImTextureID)(intptr_t)textureID, 
                    ImVec2(300, 300 * aspect),
                    ImVec2(0, 1), ImVec2(1, 0));
    }
}



void OutputNode::saveImage(const std::string& path) {
    if (inputs.empty() || inputs[0].data.empty()) {
        std::cerr << "ERROR: No input image to save!\n";
        return;
    }

    // Debug: Print image properties
    std::cout << "\n--- Saving Image Debug Info ---\n"
              << "Dimensions: " << inputs[0].data.cols << "x" 
              << inputs[0].data.rows << "\n"
              << "Channels: " << inputs[0].data.channels() << "\n"
              << "Data pointer: " << inputs[0].data.data << "\n";

    // Undo OpenGL's vertical flip
    cv::Mat saveImage;
    cv::flip(inputs[0].data, saveImage, 0); // 0 = vertical flip

    // Add file extension if missing
    std::string fullPath = path;
    const char* extensions[] = {".png", ".jpg", ".bmp"};
    if (fullPath.find('.') == std::string::npos) {
        fullPath += extensions[format];
    }

    // Create parent directories
    std::filesystem::create_directories(
        std::filesystem::path(fullPath).parent_path()
    );

    // Set OpenCV write parameters
    std::vector<int> params;
    switch(format) {
        case 0: params = {cv::IMWRITE_PNG_COMPRESSION, compression}; break;
        case 1: params = {cv::IMWRITE_JPEG_QUALITY, quality}; break;
        default: break;
    }

    // Attempt to save
    bool success = cv::imwrite(fullPath, saveImage, params);
    
    std::cout << "Save " << (success ? "SUCCEEDED" : "FAILED") 
              << " at: " << fullPath << "\n";

    if (!success) {
        std::cerr << "Possible reasons:\n"
                  << "1. Invalid path/permissions\n"
                  << "2. Unsupported format\n"
                  << "3. Corrupted image data\n";
    }
}


int OutputNode::getPinType(int pinId) const {
    return 0; // All pins are image type
}
