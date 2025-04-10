// NoiseNode.cpp
#include "nodes/NoiseNode.hpp"
#include <imgui.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

NoiseNode::NoiseNode() {
    name = "Noise Generator";
    // Add input pin for displacement map mode
    inputs.emplace_back(Pin{0, "Image"});
    // Add output pin for noise
    outputs.emplace_back(Pin{1, "Noise"});
    
    // Initialize RNG with random seed
    std::random_device rd;
    rng = std::mt19937(rd());
    
    // Default to Worley noise (as seen in screenshot)
    noiseType = 2;
}

int NoiseNode::getPinType(int pinId) const {
    return 0; // All pins are image type
}

void NoiseNode::process() {
    cv::Mat noiseImage;
    
    // Generate the noise based on selected type
    switch (noiseType) {
        case 0: // Perlin
            noiseImage = generatePerlinNoise(width, height);
            break;
        case 1: // Simplex
            noiseImage = generateSimplexNoise(width, height);
            break;
        case 2: // Worley
            noiseImage = generateWorleyNoise(width, height);
            break;
    }
    
    // If in displacement map mode and input image is available
    if (outputMode == 1 && !inputs[0].data.empty()) {
        // Apply noise as displacement map
        outputs[0].data = applyDisplacementMap(inputs[0].data, noiseImage);
    } else {
        // Direct color output
        outputs[0].data = noiseImage;
    }
}

void NoiseNode::drawUI() {
    // Noise type selection
    const char* noiseTypes[] = {"Perlin", "Simplex", "Worley"};
    ImGui::Combo("Noise Type", &noiseType, noiseTypes, IM_ARRAYSIZE(noiseTypes));
    
    // Noise parameters
    ImGui::SliderFloat("Scale", &scale, 0.001f, 5.0f);
    ImGui::SliderInt("Octaves", &octaves, 1, 8);
    ImGui::SliderFloat("Persistence", &persistence, 0.0f, 1.0f);
    
    // Output resolution
    ImGui::SliderInt("Width", &width, 128, 1024);
    ImGui::SliderInt("Height", &height, 128, 1024);
    
    // Output mode selection
    const char* outputModes[] = {"Direct Color", "Displacement Map"};
    ImGui::Combo("Output Mode", &outputMode, outputModes, IM_ARRAYSIZE(outputModes));
}

cv::Mat NoiseNode::generatePerlinNoise(int width, int height) {
    cv::Mat result(height, width, CV_8UC3);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float nx = x * scale / width;
            float ny = y * scale / height;
            
            float noise = perlinNoise(nx, ny, octaves, persistence);
            // Normalize to 0-255 range
            unsigned char value = static_cast<unsigned char>((noise + 1.0f) * 0.5f * 255.0f);
            
            // Set all channels to the same value for grayscale
            result.at<cv::Vec3b>(y, x) = cv::Vec3b(value, value, value);
        }
    }
    
    return result;
}

cv::Mat NoiseNode::generateSimplexNoise(int width, int height) {
    cv::Mat result(height, width, CV_8UC3);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float nx = x * scale / width;
            float ny = y * scale / height;
            
            float noise = 0.0f;
            float amplitude = 1.0f;
            float totalAmplitude = 0.0f;
            
            // Accumulate octaves
            for (int o = 0; o < octaves; o++) {
                float freq = std::pow(2.0f, static_cast<float>(o));
                float noiseValue = simplexNoise(nx * freq, ny * freq);
                
                noise += noiseValue * amplitude;
                totalAmplitude += amplitude;
                amplitude *= persistence;
            }
            
            // Normalize by total amplitude
            noise /= totalAmplitude;
            
            // Normalize to 0-255 range
            unsigned char value = static_cast<unsigned char>((noise + 1.0f) * 0.5f * 255.0f);
            
            // Set all channels to the same value for grayscale
            result.at<cv::Vec3b>(y, x) = cv::Vec3b(value, value, value);
        }
    }
    
    return result;
}

cv::Mat NoiseNode::generateWorleyNoise(int width, int height) {
    cv::Mat result(height, width, CV_8UC3);
    
    // Generate random feature points
    const int numPoints = 20 + static_cast<int>(scale * 30);
    std::vector<cv::Point2f> points;
    
    std::uniform_real_distribution<float> distX(0, width);
    std::uniform_real_distribution<float> distY(0, height);
    
    for (int i = 0; i < numPoints; i++) {
        points.push_back(cv::Point2f(distX(rng), distY(rng)));
    }
    
    // Generate Worley noise
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Find distance to closest point
            float minDist = std::numeric_limits<float>::max();
            
            for (const auto& p : points) {
                float dx = x - p.x;
                float dy = y - p.y;
                float dist = std::sqrt(dx*dx + dy*dy);
                minDist = std::min(minDist, dist);
            }
            
            // Normalize distance and apply scaling
            float normalizedDist = minDist / (width / (scale * 10.0f));
            normalizedDist = std::min(normalizedDist, 1.0f);
            
            // Apply octaves and persistence for more complex noise
            float noise = normalizedDist;
            float amplitude = 1.0f;
            float totalAmplitude = 1.0f;
            
            for (int o = 1; o < octaves; o++) {
                amplitude *= persistence;
                totalAmplitude += amplitude;
                
                // Add variations to each octave
                noise += normalizedDist * amplitude * (0.5f + 0.5f * std::sin(x * o * 0.01f + y * o * 0.01f));
            }
            
            noise /= totalAmplitude;
            
            // Convert to grayscale value
            unsigned char value = static_cast<unsigned char>(noise * 255.0f);
            
            // Set all channels to the same value for grayscale
            result.at<cv::Vec3b>(y, x) = cv::Vec3b(value, value, value);
        }
    }
    
    return result;
}

// Simple implementation of Perlin noise function
float NoiseNode::perlinNoise(float x, float y, int octaves, float persistence) {
    float total = 0.0f;
    float frequency = 1.0f;
    float amplitude = 1.0f;
    float maxValue = 0.0f;
    
    for (int i = 0; i < octaves; i++) {
        // Simplified 2D gradient noise
        int xi = static_cast<int>(x * frequency);
        int yi = static_cast<int>(y * frequency);
        float xf = x * frequency - xi;
        float yf = y * frequency - yi;
        
        // Simple hash function
        auto hash = [](int x, int y) {
            int h = x * 31 + y;
            h = h ^ (h >> 13);
            h = h * (h * h * 15731 + 789221) + 1376312589;
            return h & 0x7fffffff;
        };
        
        // Get random gradients
        auto getGradient = [&hash](int x, int y) {
            int h = hash(x, y);
            float angle = (h % 360) * 3.14159f / 180.0f;
            return cv::Point2f(std::cos(angle), std::sin(angle));
        };
        
        // Get corners
        cv::Point2f g00 = getGradient(xi, yi);
        cv::Point2f g10 = getGradient(xi + 1, yi);
        cv::Point2f g01 = getGradient(xi, yi + 1);
        cv::Point2f g11 = getGradient(xi + 1, yi + 1);
        
        // Dot products
        float n00 = g00.x * xf + g00.y * yf;
        float n10 = g10.x * (xf - 1.0f) + g10.y * yf;
        float n01 = g01.x * xf + g01.y * (yf - 1.0f);
        float n11 = g11.x * (xf - 1.0f) + g11.y * (yf - 1.0f);
        
        // Smoothing function
        auto fade = [](float t) { return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f); };
        
        // Interpolation
        float u = fade(xf);
        float v = fade(yf);
        
        float nx0 = n00 + u * (n10 - n00);
        float nx1 = n01 + u * (n11 - n01);
        float nxy = nx0 + v * (nx1 - nx0);
        
        total += nxy * amplitude;
        maxValue += amplitude;
        amplitude *= persistence;
        frequency *= 2.0f;
    }
    
    return total / maxValue;
}

// Simple implementation of Simplex noise
float NoiseNode::simplexNoise(float x, float y) {
    // Constants for 2D simplex noise
    const float F2 = 0.366025403f; // 0.5*(sqrt(3.0)-1.0)
    const float G2 = 0.211324865f; // (3.0-sqrt(3.0))/6.0
    
    // Skew input space to determine which simplex cell we're in
    float s = (x + y) * F2;
    float xs = x + s;
    float ys = y + s;
    int i = static_cast<int>(std::floor(xs));
    int j = static_cast<int>(std::floor(ys));
    
    float t = static_cast<float>(i + j) * G2;
    float X0 = i - t;
    float Y0 = j - t;
    float x0 = x - X0;
    float y0 = y - Y0;
    
    // Determine which simplex we're in
    int i1, j1;
    if (x0 > y0) {
        i1 = 1; j1 = 0;
    } else {
        i1 = 0; j1 = 1;
    }
    
    float x1 = x0 - i1 + G2;
    float y1 = y0 - j1 + G2;
    float x2 = x0 - 1.0f + 2.0f * G2;
    float y2 = y0 - 1.0f + 2.0f * G2;
    
    // Simple hash function
    auto hash = [](int x, int y) {
        int h = x * 31 + y;
        h = h ^ (h >> 13);
        h = h * (h * h * 15731 + 789221) + 1376312589;
        return h & 0x7fffffff;
    };
    
    // Calculate contribution from corners
    auto calcCorner = [](float t, float x, float y) {
        if (t > 0.0f) {
            t *= t;
            return t * t * (x * x + y * y);
        }
        return 0.0f;
    };
    
    float n0 = calcCorner(0.5f - x0*x0 - y0*y0, x0, y0);
    float n1 = calcCorner(0.5f - x1*x1 - y1*y1, x1, y1);
    float n2 = calcCorner(0.5f - x2*x2 - y2*y2, x2, y2);
    
    // Scale to [-1,1]
    return 70.0f * (n0 + n1 + n2);
}

// Worley noise is fully implemented in generateWorleyNoise
float NoiseNode::worleyNoise(float x, float y) {
    return 0.0f; // Not used directly - see generateWorleyNoise
}

cv::Mat NoiseNode::applyDisplacementMap(const cv::Mat& inputImage, const cv::Mat& noiseMap) {
    // Resize noise map to match input image if needed
    cv::Mat resizedNoise;
    if (noiseMap.size() != inputImage.size()) {
        cv::resize(noiseMap, resizedNoise, inputImage.size(), 0, 0, cv::INTER_LINEAR);
    } else {
        resizedNoise = noiseMap.clone();
    }
    
    // Create output image
    cv::Mat result = inputImage.clone();
    
    // Apply displacement map
    for (int y = 0; y < inputImage.rows; y++) {
        for (int x = 0; x < inputImage.cols; x++) {
            // Get displacement values from noise (use only R channel since it's grayscale)
            float displaceX = (resizedNoise.at<cv::Vec3b>(y, x)[0] / 255.0f - 0.5f) * 10.0f;
            float displaceY = (resizedNoise.at<cv::Vec3b>(y, x)[0] / 255.0f - 0.5f) * 10.0f;
            
            // Calculate source coordinates
            int srcX = static_cast<int>(x + displaceX);
            int srcY = static_cast<int>(y + displaceY);
            
            // Clamp to image boundaries
            srcX = std::max(0, std::min(srcX, inputImage.cols - 1));
            srcY = std::max(0, std::min(srcY, inputImage.rows - 1));
            
            // Copy pixel value
            result.at<cv::Vec3b>(y, x) = inputImage.at<cv::Vec3b>(srcY, srcX);
        }
    }
    
    return result;
}
