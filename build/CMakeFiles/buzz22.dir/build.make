# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/SEAN/HyperJackets/buzz-22

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/SEAN/HyperJackets/buzz-22/build

# Include any dependencies generated for this target.
include CMakeFiles/buzz22.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/buzz22.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/buzz22.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/buzz22.dir/flags.make

CMakeFiles/buzz22.dir/main.cpp.obj: CMakeFiles/buzz22.dir/flags.make
CMakeFiles/buzz22.dir/main.cpp.obj: ../main.cpp
CMakeFiles/buzz22.dir/main.cpp.obj: CMakeFiles/buzz22.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/SEAN/HyperJackets/buzz-22/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/buzz22.dir/main.cpp.obj"
	C:/MinGW/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/buzz22.dir/main.cpp.obj -MF CMakeFiles/buzz22.dir/main.cpp.obj.d -o CMakeFiles/buzz22.dir/main.cpp.obj -c C:/SEAN/HyperJackets/buzz-22/main.cpp

CMakeFiles/buzz22.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/buzz22.dir/main.cpp.i"
	C:/MinGW/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/SEAN/HyperJackets/buzz-22/main.cpp > CMakeFiles/buzz22.dir/main.cpp.i

CMakeFiles/buzz22.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/buzz22.dir/main.cpp.s"
	C:/MinGW/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/SEAN/HyperJackets/buzz-22/main.cpp -o CMakeFiles/buzz22.dir/main.cpp.s

# Object files for target buzz22
buzz22_OBJECTS = \
"CMakeFiles/buzz22.dir/main.cpp.obj"

# External object files for target buzz22
buzz22_EXTERNAL_OBJECTS =

buzz22.exe: CMakeFiles/buzz22.dir/main.cpp.obj
buzz22.exe: CMakeFiles/buzz22.dir/build.make
buzz22.exe: CMakeFiles/buzz22.dir/linklibs.rsp
buzz22.exe: CMakeFiles/buzz22.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:/SEAN/HyperJackets/buzz-22/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable buzz22.exe"
	"C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" -E rm -f CMakeFiles/buzz22.dir/objects.a
	C:/MinGW/bin/ar.exe cr CMakeFiles/buzz22.dir/objects.a @CMakeFiles/buzz22.dir/objects1.rsp
	C:/MinGW/bin/g++.exe -g -Wl,--whole-archive CMakeFiles/buzz22.dir/objects.a -Wl,--no-whole-archive -o buzz22.exe -Wl,--out-implib,libbuzz22.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/buzz22.dir/linklibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/buzz22.dir/build: buzz22.exe
.PHONY : CMakeFiles/buzz22.dir/build

CMakeFiles/buzz22.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/buzz22.dir/cmake_clean.cmake
.PHONY : CMakeFiles/buzz22.dir/clean

CMakeFiles/buzz22.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/SEAN/HyperJackets/buzz-22 C:/SEAN/HyperJackets/buzz-22 C:/SEAN/HyperJackets/buzz-22/build C:/SEAN/HyperJackets/buzz-22/build C:/SEAN/HyperJackets/buzz-22/build/CMakeFiles/buzz22.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/buzz22.dir/depend
