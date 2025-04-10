// NoiseNode.hpp
#pragma once
#include "BaseNode.hpp"

class NoiseNode : public BaseNode {
public:
 int getPinType(int pinId) const override; 
    NoiseNode();
    void process() override;
    void drawUI() override;
    
private:
    int noiseType = 0;
    float scale = 0.1f;
    int octaves = 4;
    float persistence = 0.5f;
    
    float perlin(float x, float y);
};
