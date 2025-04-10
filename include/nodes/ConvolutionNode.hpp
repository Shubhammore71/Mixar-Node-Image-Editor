#pragma once
#include "BaseNode.hpp"
#include <vector>

class ConvolutionNode : public BaseNode {
public:
    ConvolutionNode();
    void process() override;
    void drawUI() override;
    int getPinType(int pinId) const override;

    enum FilterPreset {
        PRESET_CUSTOM = 0,
        PRESET_IDENTITY,
        PRESET_EDGE_DETECT,
        PRESET_SHARPEN,
        PRESET_EMBOSS,
        PRESET_BLUR,
        PRESET_COUNT
    };

private:
    void updateKernelSize(int newSize);
    void loadPreset(FilterPreset preset);
    void normalizeKernel();
    
    int kernelSize;
    std::vector<std::vector<float>> kernel;
    FilterPreset currentPreset;
    float kernelScale;
};
