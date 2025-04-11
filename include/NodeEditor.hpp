// include/NodeEditor.hpp
#pragma once
#include "BaseNode.hpp"
#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>  

// Forward declarations instead of node headers
enum class NodeType {
    ImageInput,
    Output,
    BrightnessContrast,
    ColorChannelSplitter,
    Blur,
    Threshold,
    EdgeDetection,
    Blend,
    Noise,
    Convolution
};

class NodeEditor {
public:
    NodeEditor();
    ~NodeEditor();

    struct Connection {
        int inputNode;
        int outputNode;
        int inputPin;
        int outputPin;
    };


    

    void draw();
    bool isConnectionValid(const Connection& conn);
    void deleteConnection(int linkId);
    void drawProperties();
    BaseNode* findNodeById(int nodeId);
    int findPinIndex(const std::vector<Pin>& pins, int pinId);
    
     void processGraph();
    void processNode(BaseNode* node, std::unordered_set<BaseNode*>& processed);
    void clear();

    template <NodeType T>
    void addNode();

private:


    std::vector<std::unique_ptr<BaseNode>> nodes;
    std::vector<Connection> connections;
    int currentId = 0;
    BaseNode* selectedNode = nullptr;

    
    void handleConnections();
    void handleDeletion();
    BaseNode* findNodeByPin(int pinId, bool isInput);
    BaseNode* createNode(NodeType type);
};
