# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	cd /home/dimasya/sources/shad/git_cpp && $(CMAKE_COMMAND) -E cmake_progress_start /home/dimasya/sources/shad/git_cpp/CMakeFiles /home/dimasya/sources/shad/git_cpp/raytracer/CMakeFiles/progress.marks
	cd /home/dimasya/sources/shad/git_cpp && $(MAKE) -f CMakeFiles/Makefile2 raytracer/all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dimasya/sources/shad/git_cpp/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	cd /home/dimasya/sources/shad/git_cpp && $(MAKE) -f CMakeFiles/Makefile2 raytracer/clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	cd /home/dimasya/sources/shad/git_cpp && $(MAKE) -f CMakeFiles/Makefile2 raytracer/preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	cd /home/dimasya/sources/shad/git_cpp && $(MAKE) -f CMakeFiles/Makefile2 raytracer/preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	cd /home/dimasya/sources/shad/git_cpp && $(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

# Convenience name for target.
raytracer/CMakeFiles/test_raytracer.dir/rule:
	cd /home/dimasya/sources/shad/git_cpp && $(MAKE) -f CMakeFiles/Makefile2 raytracer/CMakeFiles/test_raytracer.dir/rule
.PHONY : raytracer/CMakeFiles/test_raytracer.dir/rule

# Convenience name for target.
test_raytracer: raytracer/CMakeFiles/test_raytracer.dir/rule

.PHONY : test_raytracer

# fast build rule for target.
test_raytracer/fast:
	cd /home/dimasya/sources/shad/git_cpp && $(MAKE) -f raytracer/CMakeFiles/test_raytracer.dir/build.make raytracer/CMakeFiles/test_raytracer.dir/build
.PHONY : test_raytracer/fast

test.o: test.cpp.o

.PHONY : test.o

# target to build an object file
test.cpp.o:
	cd /home/dimasya/sources/shad/git_cpp && $(MAKE) -f raytracer/CMakeFiles/test_raytracer.dir/build.make raytracer/CMakeFiles/test_raytracer.dir/test.cpp.o
.PHONY : test.cpp.o

test.i: test.cpp.i

.PHONY : test.i

# target to preprocess a source file
test.cpp.i:
	cd /home/dimasya/sources/shad/git_cpp && $(MAKE) -f raytracer/CMakeFiles/test_raytracer.dir/build.make raytracer/CMakeFiles/test_raytracer.dir/test.cpp.i
.PHONY : test.cpp.i

test.s: test.cpp.s

.PHONY : test.s

# target to generate assembly for a file
test.cpp.s:
	cd /home/dimasya/sources/shad/git_cpp && $(MAKE) -f raytracer/CMakeFiles/test_raytracer.dir/build.make raytracer/CMakeFiles/test_raytracer.dir/test.cpp.s
.PHONY : test.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... test_raytracer"
	@echo "... test.o"
	@echo "... test.i"
	@echo "... test.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	cd /home/dimasya/sources/shad/git_cpp && $(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

