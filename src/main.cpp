#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imnodes.h>
#include "NodeEditor.hpp"
#include <iostream>

int main() {
    // Set GLFW error callback
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW Error " << error << ": " << description << std::endl;
    });

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    // Configure GLFW for macOS
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "MIxar Node Editor", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Configure context
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize GLEW after context creation
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImNodes::CreateContext();
    ImNodesStyle& style = ImNodes::GetStyle();
style.NodePadding = ImVec2(8, 4);  // Reduced from default (8,8)
style.GridSpacing = 8.0f;   
ImGuiStyle& imguiStyle = ImGui::GetStyle();
imguiStyle.ItemSpacing = ImVec2(4, 2);  // Reduced from (8,4)
imguiStyle.FramePadding = ImVec2(4, 2); // Reduced from (8,4)
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Setup Platform/Renderer backends
    const char* glsl_version = "#version 410";
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        std::cerr << "Failed to initialize ImGui GLFW backend" << std::endl;
        glfwTerminate();
        return 1;
    }
    
    if (!ImGui_ImplOpenGL3_Init(glsl_version)) {
        std::cerr << "Failed to initialize ImGui OpenGL3 backend" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Style settings
    ImGui::StyleColorsDark();
    ImNodes::StyleColorsDark();

    // Initialize node editor
    NodeEditor editor;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Main menu bar
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New")) editor.clear();
                if (ImGui::MenuItem("Exit")) glfwSetWindowShouldClose(window, true);
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Nodes")) {
                if (ImGui::MenuItem("Image Input")) editor.addNode<NodeType::ImageInput>();
                if (ImGui::MenuItem("Output")) editor.addNode<NodeType::Output>();
                if (ImGui::MenuItem("Brightness/Contrast")) editor.addNode<NodeType::BrightnessContrast>();
                if (ImGui::MenuItem("Channel Splitter")) editor.addNode<NodeType::ColorChannelSplitter>();
                if (ImGui::MenuItem("Blur")) editor.addNode<NodeType::Blur>();
                if (ImGui::MenuItem("Threshold")) editor.addNode<NodeType::Threshold>();
                if (ImGui::MenuItem("Edge Detection")) editor.addNode<NodeType::EdgeDetection>();
                if (ImGui::MenuItem("Blend")) editor.addNode<NodeType::Blend>();
                if (ImGui::MenuItem("Noise")) editor.addNode<NodeType::Noise>();
                if (ImGui::MenuItem("Convolution")) editor.addNode<NodeType::Convolution>();
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // Editor windows
        ImGui::Begin("Node Editor", nullptr, ImGuiWindowFlags_NoScrollbar);
        editor.draw();
        ImGui::End();

        ImGui::Begin("Properties");
        editor.drawProperties();
        ImGui::End();

        // Process node graph
        editor.processGraph();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImNodes::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
