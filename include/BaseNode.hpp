// include/BaseNode.hpp
#pragma once
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

struct Pin {
    int id;
    std::string name;
    cv::Mat data;
    bool connected = false;
};

class BaseNode {
public:
 static int nextId;
    virtual ~BaseNode() = default;
    virtual void process() = 0;
    virtual void drawUI() = 0;

    virtual int getPinType(int pinId) const = 0; // Pure virtual method

    std::vector<Pin> inputs;
    std::vector<Pin> outputs;
    std::string name;
    int id;
    bool dirty = true;
};
