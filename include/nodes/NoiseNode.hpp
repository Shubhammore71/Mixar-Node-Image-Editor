// NoiseNode.hpp
#pragma once
#include "BaseNode.hpp"
#include <random>

class NoiseNode : public BaseNode {
public:
    NoiseNode();
    void process() override;
    void drawUI() override;
    int getPinType(int pinId) const override;

private:
    int noiseType = 0; // 0: Perlin, 1: Simplex, 2: Worley
    float scale = 1.0f;
    int octaves = 1;
    float persistence = 0.5f;
    int outputMode = 0; // 0: Direct color, 1: Displacement map
    int width = 512;
    int height = 512;
    
    // Noise generation methods
    cv::Mat generatePerlinNoise(int width, int height);
    cv::Mat generateSimplexNoise(int width, int height);
    cv::Mat generateWorleyNoise(int width, int height);
    
    // Helper methods for noise generation
    float perlinNoise(float x, float y, int octaves, float persistence);
    float simplexNoise(float x, float y);
    float worleyNoise(float x, float y);
    
    // Displacement map application
    cv::Mat applyDisplacementMap(const cv::Mat& inputImage, const cv::Mat& noiseMap);
    
    // Random number generation
    std::mt19937 rng;
};
