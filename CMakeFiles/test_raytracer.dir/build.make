# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dimasya/sources/shad/git_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dimasya/sources/shad/git_cpp

# Include any dependencies generated for this target.
include raytracer/CMakeFiles/test_raytracer.dir/depend.make

# Include the progress variables for this target.
include raytracer/CMakeFiles/test_raytracer.dir/progress.make

# Include the compile flags for this target's objects.
include raytracer/CMakeFiles/test_raytracer.dir/flags.make

raytracer/CMakeFiles/test_raytracer.dir/test.cpp.o: raytracer/CMakeFiles/test_raytracer.dir/flags.make
raytracer/CMakeFiles/test_raytracer.dir/test.cpp.o: raytracer/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dimasya/sources/shad/git_cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object raytracer/CMakeFiles/test_raytracer.dir/test.cpp.o"
	cd /home/dimasya/sources/shad/git_cpp/raytracer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_raytracer.dir/test.cpp.o -c /home/dimasya/sources/shad/git_cpp/raytracer/test.cpp

raytracer/CMakeFiles/test_raytracer.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_raytracer.dir/test.cpp.i"
	cd /home/dimasya/sources/shad/git_cpp/raytracer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dimasya/sources/shad/git_cpp/raytracer/test.cpp > CMakeFiles/test_raytracer.dir/test.cpp.i

raytracer/CMakeFiles/test_raytracer.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_raytracer.dir/test.cpp.s"
	cd /home/dimasya/sources/shad/git_cpp/raytracer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dimasya/sources/shad/git_cpp/raytracer/test.cpp -o CMakeFiles/test_raytracer.dir/test.cpp.s

# Object files for target test_raytracer
test_raytracer_OBJECTS = \
"CMakeFiles/test_raytracer.dir/test.cpp.o"

# External object files for target test_raytracer
test_raytracer_EXTERNAL_OBJECTS =

test_raytracer: raytracer/CMakeFiles/test_raytracer.dir/test.cpp.o
test_raytracer: raytracer/CMakeFiles/test_raytracer.dir/build.make
test_raytracer: libcontrib_catch_main.a
test_raytracer: /usr/lib/x86_64-linux-gnu/libpng.so
test_raytracer: /usr/lib/x86_64-linux-gnu/libjpeg.so
test_raytracer: raytracer/CMakeFiles/test_raytracer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dimasya/sources/shad/git_cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../test_raytracer"
	cd /home/dimasya/sources/shad/git_cpp/raytracer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_raytracer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
raytracer/CMakeFiles/test_raytracer.dir/build: test_raytracer

.PHONY : raytracer/CMakeFiles/test_raytracer.dir/build

raytracer/CMakeFiles/test_raytracer.dir/clean:
	cd /home/dimasya/sources/shad/git_cpp/raytracer && $(CMAKE_COMMAND) -P CMakeFiles/test_raytracer.dir/cmake_clean.cmake
.PHONY : raytracer/CMakeFiles/test_raytracer.dir/clean

raytracer/CMakeFiles/test_raytracer.dir/depend:
	cd /home/dimasya/sources/shad/git_cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dimasya/sources/shad/git_cpp /home/dimasya/sources/shad/git_cpp/raytracer /home/dimasya/sources/shad/git_cpp /home/dimasya/sources/shad/git_cpp/raytracer /home/dimasya/sources/shad/git_cpp/raytracer/CMakeFiles/test_raytracer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : raytracer/CMakeFiles/test_raytracer.dir/depend

