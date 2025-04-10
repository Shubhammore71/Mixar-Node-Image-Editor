// NoiseNode.cpp
#include "NoiseNode.hpp"
#include <random>
#include <imgui.h>

// Perlin noise implementation (simplified)

float NoiseNode::perlin(float x, float y) {
    static std::default_random_engine engine;
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    
    // Grid cell coordinates
    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;
    
    // Interpolation weights
    float sx = x - x0;
    float sy = y - y0;
    
    // Generate random gradients
    float n0, n1, ix0, ix1;
    
    n0 = dist(engine);
    n1 = dist(engine);
    ix0 = n0 + sx * (n1 - n0);
    
    n0 = dist(engine);
    n1 = dist(engine);
    ix1 = n0 + sx * (n1 - n0);
    
    return ix0 + sy * (ix1 - ix0);
}

NoiseNode::NoiseNode() {
    name = "Noise Generator";
    outputs.emplace_back(Pin{0, "Noise"});
    noiseType = 0;
    scale = 0.1f;
    octaves = 4;
    persistence = 0.5f;
}

int NoiseNode::getPinType(int pinId) const {
    // Output pin generates image
    return 0;
}


void NoiseNode::process() {
    cv::Mat noise(512, 512, CV_8UC1);
    
    for(int y = 0; y < noise.rows; ++y) {
        for(int x = 0; x < noise.cols; ++x) {
            float fx = x * scale;
            float fy = y * scale;
            
            float amplitude = 1.0f;
            float frequency = 1.0f;
            float total = 0.0f;
            
            for(int i = 0; i < octaves; ++i) {
                total += perlin(fx * frequency, fy * frequency) * amplitude;
                amplitude *= persistence;
                frequency *= 2.0f;
            }
            
            noise.at<uchar>(y, x) = cv::saturate_cast<uchar>((total + 1.0f) * 127.5f);
        }
    }
    
    cv::cvtColor(noise, outputs[0].data, cv::COLOR_GRAY2BGR);
}

void NoiseNode::drawUI() {
    const char* types[] = {"Perlin", "Simplex", "Worley"};
    ImGui::Combo("Noise Type", &noiseType, types, IM_ARRAYSIZE(types));
    ImGui::SliderFloat("Scale", &scale, 0.01f, 1.0f);
    ImGui::SliderInt("Octaves", &octaves, 1, 8);
    ImGui::SliderFloat("Persistence", &persistence, 0.1f, 1.0f);
}
