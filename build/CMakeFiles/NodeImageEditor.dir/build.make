# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/shubhammore/MixarNodeImageEditor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/shubhammore/mixarnodeimageeditor/build

# Include any dependencies generated for this target.
include CMakeFiles/NodeImageEditor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/NodeImageEditor.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/NodeImageEditor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NodeImageEditor.dir/flags.make

CMakeFiles/NodeImageEditor.dir/codegen:
.PHONY : CMakeFiles/NodeImageEditor.dir/codegen

CMakeFiles/NodeImageEditor.dir/src/main.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/main.cpp.o: /Users/shubhammore/MixarNodeImageEditor/src/main.cpp
CMakeFiles/NodeImageEditor.dir/src/main.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/main.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/main.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/main.cpp.o -c /Users/shubhammore/MixarNodeImageEditor/src/main.cpp

CMakeFiles/NodeImageEditor.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shubhammore/MixarNodeImageEditor/src/main.cpp > CMakeFiles/NodeImageEditor.dir/src/main.cpp.i

CMakeFiles/NodeImageEditor.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shubhammore/MixarNodeImageEditor/src/main.cpp -o CMakeFiles/NodeImageEditor.dir/src/main.cpp.s

CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.o: /Users/shubhammore/MixarNodeImageEditor/src/NodeEditor.cpp
CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.o -c /Users/shubhammore/MixarNodeImageEditor/src/NodeEditor.cpp

CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shubhammore/MixarNodeImageEditor/src/NodeEditor.cpp > CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.i

CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shubhammore/MixarNodeImageEditor/src/NodeEditor.cpp -o CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.s

CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.o: /Users/shubhammore/MixarNodeImageEditor/src/BaseNode.cpp
CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.o -c /Users/shubhammore/MixarNodeImageEditor/src/BaseNode.cpp

CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shubhammore/MixarNodeImageEditor/src/BaseNode.cpp > CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.i

CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shubhammore/MixarNodeImageEditor/src/BaseNode.cpp -o CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.s

CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.o: /Users/shubhammore/MixarNodeImageEditor/src/nodes/ImageInputNode.cpp
CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.o -c /Users/shubhammore/MixarNodeImageEditor/src/nodes/ImageInputNode.cpp

CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shubhammore/MixarNodeImageEditor/src/nodes/ImageInputNode.cpp > CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.i

CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shubhammore/MixarNodeImageEditor/src/nodes/ImageInputNode.cpp -o CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.s

CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.o: /Users/shubhammore/MixarNodeImageEditor/src/nodes/OutputNode.cpp
CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.o -c /Users/shubhammore/MixarNodeImageEditor/src/nodes/OutputNode.cpp

CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shubhammore/MixarNodeImageEditor/src/nodes/OutputNode.cpp > CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.i

CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shubhammore/MixarNodeImageEditor/src/nodes/OutputNode.cpp -o CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.s

CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.o: /Users/shubhammore/MixarNodeImageEditor/src/nodes/BrightnessContrastNode.cpp
CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.o -c /Users/shubhammore/MixarNodeImageEditor/src/nodes/BrightnessContrastNode.cpp

CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shubhammore/MixarNodeImageEditor/src/nodes/BrightnessContrastNode.cpp > CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.i

CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shubhammore/MixarNodeImageEditor/src/nodes/BrightnessContrastNode.cpp -o CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.s

CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.o: /Users/shubhammore/MixarNodeImageEditor/src/nodes/ColorChannelSplitterNode.cpp
CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.o -c /Users/shubhammore/MixarNodeImageEditor/src/nodes/ColorChannelSplitterNode.cpp

CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shubhammore/MixarNodeImageEditor/src/nodes/ColorChannelSplitterNode.cpp > CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.i

CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shubhammore/MixarNodeImageEditor/src/nodes/ColorChannelSplitterNode.cpp -o CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.s

CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.o: /Users/shubhammore/MixarNodeImageEditor/src/nodes/BlurNode.cpp
CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.o -c /Users/shubhammore/MixarNodeImageEditor/src/nodes/BlurNode.cpp

CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shubhammore/MixarNodeImageEditor/src/nodes/BlurNode.cpp > CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.i

CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shubhammore/MixarNodeImageEditor/src/nodes/BlurNode.cpp -o CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.s

CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.o: /Users/shubhammore/MixarNodeImageEditor/src/nodes/ThresholdNode.cpp
CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.o -c /Users/shubhammore/MixarNodeImageEditor/src/nodes/ThresholdNode.cpp

CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shubhammore/MixarNodeImageEditor/src/nodes/ThresholdNode.cpp > CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.i

CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shubhammore/MixarNodeImageEditor/src/nodes/ThresholdNode.cpp -o CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.s

CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.o: /Users/shubhammore/MixarNodeImageEditor/src/nodes/EdgeDetectionNode.cpp
CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.o -c /Users/shubhammore/MixarNodeImageEditor/src/nodes/EdgeDetectionNode.cpp

CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shubhammore/MixarNodeImageEditor/src/nodes/EdgeDetectionNode.cpp > CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.i

CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shubhammore/MixarNodeImageEditor/src/nodes/EdgeDetectionNode.cpp -o CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.s

CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.o: /Users/shubhammore/MixarNodeImageEditor/src/nodes/BlendNode.cpp
CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.o -c /Users/shubhammore/MixarNodeImageEditor/src/nodes/BlendNode.cpp

CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shubhammore/MixarNodeImageEditor/src/nodes/BlendNode.cpp > CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.i

CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shubhammore/MixarNodeImageEditor/src/nodes/BlendNode.cpp -o CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.s

CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.o: /Users/shubhammore/MixarNodeImageEditor/src/nodes/NoiseNode.cpp
CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.o -c /Users/shubhammore/MixarNodeImageEditor/src/nodes/NoiseNode.cpp

CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shubhammore/MixarNodeImageEditor/src/nodes/NoiseNode.cpp > CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.i

CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shubhammore/MixarNodeImageEditor/src/nodes/NoiseNode.cpp -o CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.s

CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.o: /Users/shubhammore/MixarNodeImageEditor/src/nodes/ConvolutionNode.cpp
CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.o -MF CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.o -c /Users/shubhammore/MixarNodeImageEditor/src/nodes/ConvolutionNode.cpp

CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shubhammore/MixarNodeImageEditor/src/nodes/ConvolutionNode.cpp > CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.i

CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shubhammore/MixarNodeImageEditor/src/nodes/ConvolutionNode.cpp -o CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.s

# Object files for target NodeImageEditor
NodeImageEditor_OBJECTS = \
"CMakeFiles/NodeImageEditor.dir/src/main.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.o"

# External object files for target NodeImageEditor
NodeImageEditor_EXTERNAL_OBJECTS =

bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/main.cpp.o
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/NodeEditor.cpp.o
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/BaseNode.cpp.o
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/nodes/ImageInputNode.cpp.o
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/nodes/OutputNode.cpp.o
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/nodes/BrightnessContrastNode.cpp.o
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/nodes/ColorChannelSplitterNode.cpp.o
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/nodes/BlurNode.cpp.o
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/nodes/ThresholdNode.cpp.o
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/nodes/EdgeDetectionNode.cpp.o
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/nodes/BlendNode.cpp.o
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/nodes/NoiseNode.cpp.o
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/src/nodes/ConvolutionNode.cpp.o
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/build.make
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_gapi.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_stitching.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_alphamat.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_aruco.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_bgsegm.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_bioinspired.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_ccalib.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_dnn_objdetect.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_dnn_superres.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_dpm.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_face.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_freetype.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_fuzzy.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_hfs.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_img_hash.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_intensity_transform.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_line_descriptor.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_mcc.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_quality.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_rapid.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_reg.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_rgbd.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_saliency.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_sfm.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_signal.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_stereo.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_structured_light.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_superres.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_surface_matching.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_tracking.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_videostab.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_viz.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_wechat_qrcode.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_xfeatures2d.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_xobjdetect.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_xphoto.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libglfw.3.4.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libGLEW.2.2.0.dylib
bin/NodeImageEditor: lib/libimgui.a
bin/NodeImageEditor: lib/libimnodes.a
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_shape.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_highgui.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_datasets.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_plot.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_text.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_ml.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_phase_unwrapping.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_optflow.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_ximgproc.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_video.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_videoio.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_imgcodecs.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_objdetect.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_calib3d.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_dnn.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_features2d.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_flann.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_photo.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_imgproc.4.11.0.dylib
bin/NodeImageEditor: /opt/homebrew/lib/libopencv_core.4.11.0.dylib
bin/NodeImageEditor: CMakeFiles/NodeImageEditor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable bin/NodeImageEditor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NodeImageEditor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NodeImageEditor.dir/build: bin/NodeImageEditor
.PHONY : CMakeFiles/NodeImageEditor.dir/build

CMakeFiles/NodeImageEditor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NodeImageEditor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NodeImageEditor.dir/clean

CMakeFiles/NodeImageEditor.dir/depend:
	cd /Users/shubhammore/mixarnodeimageeditor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/shubhammore/MixarNodeImageEditor /Users/shubhammore/MixarNodeImageEditor /Users/shubhammore/mixarnodeimageeditor/build /Users/shubhammore/mixarnodeimageeditor/build /Users/shubhammore/mixarnodeimageeditor/build/CMakeFiles/NodeImageEditor.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/NodeImageEditor.dir/depend

