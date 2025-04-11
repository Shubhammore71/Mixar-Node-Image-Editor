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

    // Draw all nodes
    for (auto& node : nodes) {
        ImNodes::BeginNode(node->id);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted(node->name.c_str());
        ImNodes::EndNodeTitleBar();

        // Input pins
        for (auto& input : node->inputs) {
            ImNodes::BeginInputAttribute(input.id);
            ImGui::TextUnformatted(input.name.c_str());
            ImNodes::EndInputAttribute();
        }

        // Output pins
        for (auto& output : node->outputs) {
            ImNodes::BeginOutputAttribute(output.id);
            ImGui::TextUnformatted(output.name.c_str());
            ImNodes::EndOutputAttribute();
        }

        node->drawUI();
        ImNodes::EndNode();
    }

for (size_t i = 0; i < connections.size(); i++) {
        ImNodes::Link(
            static_cast<int>(i),  // Use index as link ID
            connections[i].outputPin,
            connections[i].inputPin
        );
    }
    
    ImNodes::EndNodeEditor();


  int hoveredLinkId = -1;
if (ImNodes::IsLinkHovered(&hoveredLinkId)) {
    if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
        std::cout << "Double-clicked on link ID: " << hoveredLinkId << std::endl;
        if (hoveredLinkId >= 0 && hoveredLinkId < static_cast<int>(connections.size())) {
            deleteConnection(hoveredLinkId);
        }
    }
}
 if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
        for (size_t i = 0; i < nodes.size(); i++) {
            if (ImNodes::IsNodeHovered(&nodes[i]->id)) {
                // Remove all connections to/from this node
                connections.erase(
                    std::remove_if(connections.begin(), connections.end(),
                        [nodeId = nodes[i]->id](const Connection& conn) {
                            return conn.inputNode == nodeId || conn.outputNode == nodeId;
                        }),
                    connections.end());
                
                // Remove the node
                nodes.erase(nodes.begin() + i);
                processGraph();
                break;
            }
        }
    }
    handleConnections();
}
void NodeEditor::deleteConnection(int connectionIndex) {
    if (connectionIndex < 0 || connectionIndex >= static_cast<int>(connections.size())) {
        return;
    }
    
    std::cout << "Deleting connection at index: " << connectionIndex << std::endl;
    
    // Get connection to delete
    Connection& conn = connections[connectionIndex];
    
    // Find connected nodes
    BaseNode* inputNode = findNodeById(conn.inputNode);
    BaseNode* outputNode = findNodeById(conn.outputNode);
    
    // Clear connected pins
    if (inputNode) {
        for (auto& pin : inputNode->inputs) {
            if (pin.id == conn.inputPin) {
                pin.data.release(); // Clear data
                pin.connected = false;
            }
        }
        inputNode->dirty = true;
    }
    
    if (outputNode) {
        for (auto& pin : outputNode->outputs) {
            if (pin.id == conn.outputPin) {
                pin.connected = false;
            }
        }
        outputNode->dirty = true;
    }
    
    // Remove connection
    connections.erase(connections.begin() + connectionIndex);
    
    // Reprocess graph
    processGraph();
}


bool NodeEditor::isConnectionValid(const Connection& conn) {
    return findNodeById(conn.inputNode) && findNodeById(conn.outputNode);
}


void NodeEditor::handleConnections() {
    int startPin, endPin;
    if (ImNodes::IsLinkCreated(&startPin, &endPin)) {
        BaseNode* outputNode = findNodeByPin(startPin, false);
        BaseNode* inputNode = findNodeByPin(endPin, true);
        
        if (outputNode && inputNode) {
            // This is where connections should be stored
            connections.push_back({
                inputNode->id,
                outputNode->id,
                endPin,
                startPin
            });
            
            std::cout << "Connection created: " << connections.size() << " total connections" << std::endl;
            
            // Mark for processing
            outputNode->dirty = true;
            inputNode->dirty = true;
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
    connections.erase(std::remove_if(connections.begin(), connections.end(),
        [this](const Connection& conn) {
            return !this->isConnectionValid(conn);
        }), connections.end());
    
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
    if (selectedNode) {
        selectedNode->drawUI();
    } else {
        // Add your debug code here - this is likely the current location
        ImGui::Begin("Debug");
        ImGui::Text("Connections: %zu", connections.size());

        // Show all connections
        for (size_t i = 0; i < connections.size(); i++) {
            ImGui::Text("Link %zu: %d:%d → %d:%d", 
                        i, 
                        connections[i].outputNode, connections[i].outputPin,
                        connections[i].inputNode, connections[i].inputPin);
        }

        // Show event states
        ImGui::Text("Double-clicked: %s", ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) ? "Yes" : "No");

        int hoveredLink = -1;
        bool isHovered = ImNodes::IsLinkHovered(&hoveredLink);
        ImGui::Text("Link hovered: %d (Hovered: %s)", hoveredLink, isHovered ? "Yes" : "No");

        ImGui::End();
    }
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