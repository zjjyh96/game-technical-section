# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mytrain.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mytrain.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mytrain.dir/flags.make

CMakeFiles/mytrain.dir/main.cpp.o: CMakeFiles/mytrain.dir/flags.make
CMakeFiles/mytrain.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mytrain.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mytrain.dir/main.cpp.o -c /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/main.cpp

CMakeFiles/mytrain.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mytrain.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/main.cpp > CMakeFiles/mytrain.dir/main.cpp.i

CMakeFiles/mytrain.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mytrain.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/main.cpp -o CMakeFiles/mytrain.dir/main.cpp.s

CMakeFiles/mytrain.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/mytrain.dir/main.cpp.o.requires

CMakeFiles/mytrain.dir/main.cpp.o.provides: CMakeFiles/mytrain.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/mytrain.dir/build.make CMakeFiles/mytrain.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/mytrain.dir/main.cpp.o.provides

CMakeFiles/mytrain.dir/main.cpp.o.provides.build: CMakeFiles/mytrain.dir/main.cpp.o


CMakeFiles/mytrain.dir/FaceLib.cpp.o: CMakeFiles/mytrain.dir/flags.make
CMakeFiles/mytrain.dir/FaceLib.cpp.o: ../FaceLib.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mytrain.dir/FaceLib.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mytrain.dir/FaceLib.cpp.o -c /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/FaceLib.cpp

CMakeFiles/mytrain.dir/FaceLib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mytrain.dir/FaceLib.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/FaceLib.cpp > CMakeFiles/mytrain.dir/FaceLib.cpp.i

CMakeFiles/mytrain.dir/FaceLib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mytrain.dir/FaceLib.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/FaceLib.cpp -o CMakeFiles/mytrain.dir/FaceLib.cpp.s

CMakeFiles/mytrain.dir/FaceLib.cpp.o.requires:

.PHONY : CMakeFiles/mytrain.dir/FaceLib.cpp.o.requires

CMakeFiles/mytrain.dir/FaceLib.cpp.o.provides: CMakeFiles/mytrain.dir/FaceLib.cpp.o.requires
	$(MAKE) -f CMakeFiles/mytrain.dir/build.make CMakeFiles/mytrain.dir/FaceLib.cpp.o.provides.build
.PHONY : CMakeFiles/mytrain.dir/FaceLib.cpp.o.provides

CMakeFiles/mytrain.dir/FaceLib.cpp.o.provides.build: CMakeFiles/mytrain.dir/FaceLib.cpp.o


# Object files for target mytrain
mytrain_OBJECTS = \
"CMakeFiles/mytrain.dir/main.cpp.o" \
"CMakeFiles/mytrain.dir/FaceLib.cpp.o"

# External object files for target mytrain
mytrain_EXTERNAL_OBJECTS =

mytrain: CMakeFiles/mytrain.dir/main.cpp.o
mytrain: CMakeFiles/mytrain.dir/FaceLib.cpp.o
mytrain: CMakeFiles/mytrain.dir/build.make
mytrain: /usr/local/lib/libopencv_videostab.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_ts.a
mytrain: /usr/local/lib/libopencv_superres.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_stitching.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_contrib.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_nonfree.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_ocl.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_gpu.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_photo.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_objdetect.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_legacy.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_video.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_ml.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_calib3d.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_features2d.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_highgui.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_imgproc.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_flann.2.4.13.dylib
mytrain: /usr/local/lib/libopencv_core.2.4.13.dylib
mytrain: CMakeFiles/mytrain.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable mytrain"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mytrain.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mytrain.dir/build: mytrain

.PHONY : CMakeFiles/mytrain.dir/build

CMakeFiles/mytrain.dir/requires: CMakeFiles/mytrain.dir/main.cpp.o.requires
CMakeFiles/mytrain.dir/requires: CMakeFiles/mytrain.dir/FaceLib.cpp.o.requires

.PHONY : CMakeFiles/mytrain.dir/requires

CMakeFiles/mytrain.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mytrain.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mytrain.dir/clean

CMakeFiles/mytrain.dir/depend:
	cd /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/cmake-build-debug /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/cmake-build-debug /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytrain/cmake-build-debug/CMakeFiles/mytrain.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mytrain.dir/depend
