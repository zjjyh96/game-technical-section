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
CMAKE_SOURCE_DIR = /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mytest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mytest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mytest.dir/flags.make

CMakeFiles/mytest.dir/main.cpp.o: CMakeFiles/mytest.dir/flags.make
CMakeFiles/mytest.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mytest.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mytest.dir/main.cpp.o -c /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/main.cpp

CMakeFiles/mytest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mytest.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/main.cpp > CMakeFiles/mytest.dir/main.cpp.i

CMakeFiles/mytest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mytest.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/main.cpp -o CMakeFiles/mytest.dir/main.cpp.s

CMakeFiles/mytest.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/mytest.dir/main.cpp.o.requires

CMakeFiles/mytest.dir/main.cpp.o.provides: CMakeFiles/mytest.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/mytest.dir/build.make CMakeFiles/mytest.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/mytest.dir/main.cpp.o.provides

CMakeFiles/mytest.dir/main.cpp.o.provides.build: CMakeFiles/mytest.dir/main.cpp.o


CMakeFiles/mytest.dir/FaceLib.cpp.o: CMakeFiles/mytest.dir/flags.make
CMakeFiles/mytest.dir/FaceLib.cpp.o: ../FaceLib.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mytest.dir/FaceLib.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mytest.dir/FaceLib.cpp.o -c /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/FaceLib.cpp

CMakeFiles/mytest.dir/FaceLib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mytest.dir/FaceLib.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/FaceLib.cpp > CMakeFiles/mytest.dir/FaceLib.cpp.i

CMakeFiles/mytest.dir/FaceLib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mytest.dir/FaceLib.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/FaceLib.cpp -o CMakeFiles/mytest.dir/FaceLib.cpp.s

CMakeFiles/mytest.dir/FaceLib.cpp.o.requires:

.PHONY : CMakeFiles/mytest.dir/FaceLib.cpp.o.requires

CMakeFiles/mytest.dir/FaceLib.cpp.o.provides: CMakeFiles/mytest.dir/FaceLib.cpp.o.requires
	$(MAKE) -f CMakeFiles/mytest.dir/build.make CMakeFiles/mytest.dir/FaceLib.cpp.o.provides.build
.PHONY : CMakeFiles/mytest.dir/FaceLib.cpp.o.provides

CMakeFiles/mytest.dir/FaceLib.cpp.o.provides.build: CMakeFiles/mytest.dir/FaceLib.cpp.o


# Object files for target mytest
mytest_OBJECTS = \
"CMakeFiles/mytest.dir/main.cpp.o" \
"CMakeFiles/mytest.dir/FaceLib.cpp.o"

# External object files for target mytest
mytest_EXTERNAL_OBJECTS =

mytest: CMakeFiles/mytest.dir/main.cpp.o
mytest: CMakeFiles/mytest.dir/FaceLib.cpp.o
mytest: CMakeFiles/mytest.dir/build.make
mytest: /usr/local/lib/libopencv_videostab.2.4.13.dylib
mytest: /usr/local/lib/libopencv_ts.a
mytest: /usr/local/lib/libopencv_superres.2.4.13.dylib
mytest: /usr/local/lib/libopencv_stitching.2.4.13.dylib
mytest: /usr/local/lib/libopencv_contrib.2.4.13.dylib
mytest: /usr/local/lib/libopencv_nonfree.2.4.13.dylib
mytest: /usr/local/lib/libopencv_ocl.2.4.13.dylib
mytest: /usr/local/lib/libopencv_gpu.2.4.13.dylib
mytest: /usr/local/lib/libopencv_photo.2.4.13.dylib
mytest: /usr/local/lib/libopencv_objdetect.2.4.13.dylib
mytest: /usr/local/lib/libopencv_legacy.2.4.13.dylib
mytest: /usr/local/lib/libopencv_video.2.4.13.dylib
mytest: /usr/local/lib/libopencv_ml.2.4.13.dylib
mytest: /usr/local/lib/libopencv_calib3d.2.4.13.dylib
mytest: /usr/local/lib/libopencv_features2d.2.4.13.dylib
mytest: /usr/local/lib/libopencv_highgui.2.4.13.dylib
mytest: /usr/local/lib/libopencv_imgproc.2.4.13.dylib
mytest: /usr/local/lib/libopencv_flann.2.4.13.dylib
mytest: /usr/local/lib/libopencv_core.2.4.13.dylib
mytest: CMakeFiles/mytest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable mytest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mytest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mytest.dir/build: mytest

.PHONY : CMakeFiles/mytest.dir/build

CMakeFiles/mytest.dir/requires: CMakeFiles/mytest.dir/main.cpp.o.requires
CMakeFiles/mytest.dir/requires: CMakeFiles/mytest.dir/FaceLib.cpp.o.requires

.PHONY : CMakeFiles/mytest.dir/requires

CMakeFiles/mytest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mytest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mytest.dir/clean

CMakeFiles/mytest.dir/depend:
	cd /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/cmake-build-debug /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/cmake-build-debug /Users/jinfee/Documents/Github/game-technical-section/Eigenface/mytest/cmake-build-debug/CMakeFiles/mytest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mytest.dir/depend

