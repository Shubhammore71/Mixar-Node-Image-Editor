cmake_minimum_required(VERSION 3.15)
project(NodeImageEditor)

# Core configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Dependency configuration
find_package(OpenCV REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Apple Silicon specific configuration
if(APPLE)
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
    add_compile_definitions(GL_SILENCE_DEPRECATION)
endif()

# ImGui configuration
add_library(imgui STATIC
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)

# ImNodes configuration
add_library(imnodes STATIC imnodes/imnodes.cpp)
target_include_directories(imnodes PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/imnodes
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

# Main executable
add_executable(${PROJECT_NAME}
src/main.cpp
src/NodeEditor.cpp
src/BaseNode.cpp
src/nodes/ImageInputNode.cpp
src/nodes/OutputNode.cpp
src/nodes/BrightnessContrastNode.cpp
src/nodes/ColorChannelSplitterNode.cpp
src/nodes/BlurNode.cpp
src/nodes/ThresholdNode.cpp
src/nodes/EdgeDetectionNode.cpp
src/nodes/BlendNode.cpp
src/nodes/NoiseNode.cpp
src/nodes/ConvolutionNode.cpp
)



# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/nodes
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/pfd
    ${OpenCV_INCLUDE_DIRS}
    ${GLFW3_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
    glfw
    GLEW::GLEW
    imgui
    imnodes
    ${OPENGL_LIBRARIES} # Add this
)

# macOS specific frameworks
if(APPLE)
    target_link_libraries(${PROJECT_NAME}
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()

# Debug configuration
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
endif()