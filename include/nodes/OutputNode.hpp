#pragma once
#include "BaseNode.hpp"
#include <string>
#include <GL/glew.h>

class OutputNode : public BaseNode {
public:
    OutputNode();
    ~OutputNode() override;
    void process() override;
    void drawUI() override;
    int getPinType(int pinId) const override;
    void saveImage(const std::string& path);

private:
    GLuint textureID = 0;
    std::string filepath;
    int format = 0;       // 0: PNG, 1: JPEG, 2: BMP
    int quality = 95;
    int compression = 3;  // Compression level for PNG
};
