// include/nodes/OutputNode.hpp
#pragma once
#include "BaseNode.hpp"
#include <GL/glew.h>

class OutputNode : public BaseNode {
public:
 int getPinType(int pinId) const override; 
    OutputNode();
    void process() override;
    void drawUI() override;
    
private:

    std::string outputPath;
    int format = 0;
    int quality = 95;
    GLuint textureID = 0; // Add texture handle
};
