#include <imgui.h>
#include <imnodes.h>
#include "NodeEditor.hpp"
#include "nodes/ImageInputNode.hpp"
#include "nodes/OutputNode.hpp"
#include "nodes/BrightnessContrastNode.hpp"
#include "nodes/ColorChannelSplitterNode.hpp"
#include "nodes/BlurNode.hpp"
#include "nodes/ThresholdNode.hpp"
#include "nodes/EdgeDetectionNode.hpp"
#include "nodes/BlendNode.hpp"
#include "nodes/NoiseNode.hpp"
#include "nodes/ConvolutionNode.hpp"
#include <unordered_set>  

NodeEditor::NodeEditor() {
    ImNodes::GetIO().LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
}

NodeEditor::~NodeEditor() {
    clear();
}

void NodeEditor::draw() {
    ImNodes::BeginNodeEditor();


   

    for (auto& node : nodes) {
        ImNodes::BeginNode(node->id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted(node->name.c_str());
        ImNodes::EndNodeTitleBar();

        // Render input pins
        for (auto& input : node->inputs) {
            ImNodes::BeginInputAttribute(input.id);
            ImGui::TextUnformatted(input.name.c_str());
            ImNodes::EndInputAttribute();
        }

        // Render output pins
        for (auto& output : node->outputs) {
            ImNodes::BeginOutputAttribute(output.id);
            ImGui::TextUnformatted(output.name.c_str());
            ImNodes::EndOutputAttribute();
        }

        node->drawUI();
        ImNodes::EndNode();
    }

   for (const auto& connection : connections) {
    // Use a consistent formula for link IDs
    int linkId = connection.inputNode + connection.outputNode;
    
    ImNodes::Link(
        linkId,
        connection.outputPin,
        connection.inputPin
    );
}

    ImNodes::EndNodeEditor();
     // Check for double-click on links
    int hoveredLinkId = -1;
    if (ImNodes::IsLinkHovered(&hoveredLinkId)) {
        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
            // Delete the connection with this ID
            deleteConnection(hoveredLinkId);
        }
    }
    handleConnections();
}

void NodeEditor::deleteConnection(int linkId) {
    // Find the connection matching this link ID
    auto it = std::find_if(connections.begin(), connections.end(), 
        [linkId](const Connection& conn) {
            // Use the same ID generation formula as when creating links
            return (conn.inputNode + conn.outputNode) == linkId;
        });
    
    if (it != connections.end()) {
        // Mark connected nodes as dirty to trigger reprocessing
        BaseNode* inputNode = findNodeById(it->inputNode);
        BaseNode* outputNode = findNodeById(it->outputNode);
        
        if (inputNode) inputNode->dirty = true;
        if (outputNode) outputNode->dirty = true;
        
        // Remove the connection
        connections.erase(it);
    }
}






void NodeEditor::handleConnections() {
    // Check for dropped links (when user releases mouse button)
    int startPin = -1, endPin = -1;
    
    // CRITICAL: This needs to be called EVERY FRAME to detect connections
    if (ImNodes::IsLinkCreated(&startPin, &endPin)) {
        // Debug output
        std::cout << "Link created between pins: " << startPin << " -> " << endPin << std::endl;
        
        // Find the actual nodes these pins belong to
        BaseNode* outputNode = findNodeByPin(startPin, false);
        BaseNode* inputNode = findNodeByPin(endPin, true);
        
        if (outputNode && inputNode) {
            // Create a new connection
            connections.push_back({
                inputNode->id,
                outputNode->id,
                endPin,
                startPin
            });
            
            // Mark nodes as dirty to trigger reprocessing
            outputNode->dirty = true;
            inputNode->dirty = true;
            
            std::cout << "Connection successfully created!" << std::endl;
        }
    }
}

BaseNode* NodeEditor::findNodeById(int nodeId) {
    for (auto& node : nodes) {
        if (node->id == nodeId) {
            return node.get();
        }
    }
    return nullptr;
}

int NodeEditor::findPinIndex(const std::vector<Pin>& pins, int pinId) {
    for (size_t i = 0; i < pins.size(); i++) {
        if (pins[i].id == pinId) {
            return static_cast<int>(i);
        }
    }
    return -1;
}




BaseNode* NodeEditor::findNodeByPin(int pinId, bool isInput) {
    for (auto& node : nodes) {
        if (isInput) {
            for (auto& pin : node->inputs) {
                if (pin.id == pinId) {
                    return node.get();
                }
            }
        } else {
            for (auto& pin : node->outputs) {
                if (pin.id == pinId) {
                    return node.get();
                }
            }
        }
    }
    return nullptr;
}


void NodeEditor::processGraph() {
    std::unordered_set<BaseNode*> processed;

    for (auto& node : nodes) {
        processNode(node.get(), processed);
    }
}
void NodeEditor::processNode(BaseNode* node, std::unordered_set<BaseNode*>& processed) {
    if (processed.count(node) > 0) {
        return; // Skip if already processed
    }
    
    // Process dependencies first
    for (const auto& conn : connections) {
        if (conn.inputNode == node->id) {
            BaseNode* outputNode = findNodeById(conn.outputNode);
            if (outputNode) {
                processNode(outputNode, processed);
                
                // Find connected pins
                int outputPinIdx = findPinIndex(outputNode->outputs, conn.outputPin);
                int inputPinIdx = findPinIndex(node->inputs, conn.inputPin);
                
                if (outputPinIdx >= 0 && inputPinIdx >= 0) {
    const cv::Mat& srcData = outputNode->outputs[outputPinIdx].data;
    if (!srcData.empty()) {
        // Always create a deep copy to avoid memory issues
        node->inputs[inputPinIdx].data = srcData.clone();
    }
}
            }
        }
    }
    
    // Process current node
    node->process();
    processed.insert(node);
}



template <NodeType T>
void NodeEditor::addNode() {
    auto node = createNode(T);
    if (node) {
        node->id = currentId++; // Assign unique node ID

        // Assign unique IDs to input pins
        for (auto& input : node->inputs) {
            input.id = currentId++;
        }

        // Assign unique IDs to output pins
        for (auto& output : node->outputs) {
            output.id = currentId++;
        }

        nodes.emplace_back(std::move(node));
    }
}



BaseNode* NodeEditor::createNode(NodeType type) {
    switch(type) {
        case NodeType::ImageInput: return new ImageInputNode();
        case NodeType::Output: return new OutputNode();
        case NodeType::BrightnessContrast: return new BrightnessContrastNode();
        case NodeType::ColorChannelSplitter: return new ColorChannelSplitterNode();
        case NodeType::Blur: return new BlurNode();
        case NodeType::Threshold: return new ThresholdNode();
        case NodeType::EdgeDetection: return new EdgeDetectionNode();
        case NodeType::Blend: return new BlendNode();
        case NodeType::Noise: return new NoiseNode();
        case NodeType::Convolution: return new ConvolutionNode();
        default: return nullptr;
    }
}


void NodeEditor::drawProperties() {
    // Existing properties rendering logic
    ImGui::Text("Node Properties");

    // Debugging connection info
    ImGui::Begin("Debug");
    ImGui::Text("Connections: %zu", connections.size());
    for (const auto& conn : connections) {
        ImGui::Text("Link %d -> %d", conn.outputPin, conn.inputPin);
    }
    ImGui::End();
}


void NodeEditor::clear() {
    nodes.clear();
    connections.clear();
    currentId = 0;
    selectedNode = nullptr;
}

// Add at the end of NodeEditor.cpp
template void NodeEditor::addNode<NodeType::ImageInput>();
template void NodeEditor::addNode<NodeType::Output>();
template void NodeEditor::addNode<NodeType::BrightnessContrast>();
template void NodeEditor::addNode<NodeType::ColorChannelSplitter>();
template void NodeEditor::addNode<NodeType::Blur>();
template void NodeEditor::addNode<NodeType::Threshold>();
template void NodeEditor::addNode<NodeType::EdgeDetection>();
template void NodeEditor::addNode<NodeType::Blend>();
template void NodeEditor::addNode<NodeType::Noise>();
template void NodeEditor::addNode<NodeType::Convolution>();
