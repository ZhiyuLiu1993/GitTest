# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /home/lzy/clion-2018.1.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/lzy/clion-2018.1.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lzy/GitTest/Ran_test/tinyhttp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lzy/GitTest/Ran_test/tinyhttp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/simpleclient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/simpleclient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simpleclient.dir/flags.make

CMakeFiles/simpleclient.dir/simpleclient.c.o: CMakeFiles/simpleclient.dir/flags.make
CMakeFiles/simpleclient.dir/simpleclient.c.o: ../simpleclient.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lzy/GitTest/Ran_test/tinyhttp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/simpleclient.dir/simpleclient.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/simpleclient.dir/simpleclient.c.o   -c /home/lzy/GitTest/Ran_test/tinyhttp/simpleclient.c

CMakeFiles/simpleclient.dir/simpleclient.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simpleclient.dir/simpleclient.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lzy/GitTest/Ran_test/tinyhttp/simpleclient.c > CMakeFiles/simpleclient.dir/simpleclient.c.i

CMakeFiles/simpleclient.dir/simpleclient.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simpleclient.dir/simpleclient.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lzy/GitTest/Ran_test/tinyhttp/simpleclient.c -o CMakeFiles/simpleclient.dir/simpleclient.c.s

CMakeFiles/simpleclient.dir/simpleclient.c.o.requires:

.PHONY : CMakeFiles/simpleclient.dir/simpleclient.c.o.requires

CMakeFiles/simpleclient.dir/simpleclient.c.o.provides: CMakeFiles/simpleclient.dir/simpleclient.c.o.requires
	$(MAKE) -f CMakeFiles/simpleclient.dir/build.make CMakeFiles/simpleclient.dir/simpleclient.c.o.provides.build
.PHONY : CMakeFiles/simpleclient.dir/simpleclient.c.o.provides

CMakeFiles/simpleclient.dir/simpleclient.c.o.provides.build: CMakeFiles/simpleclient.dir/simpleclient.c.o


# Object files for target simpleclient
simpleclient_OBJECTS = \
"CMakeFiles/simpleclient.dir/simpleclient.c.o"

# External object files for target simpleclient
simpleclient_EXTERNAL_OBJECTS =

simpleclient: CMakeFiles/simpleclient.dir/simpleclient.c.o
simpleclient: CMakeFiles/simpleclient.dir/build.make
simpleclient: CMakeFiles/simpleclient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lzy/GitTest/Ran_test/tinyhttp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable simpleclient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simpleclient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simpleclient.dir/build: simpleclient

.PHONY : CMakeFiles/simpleclient.dir/build

CMakeFiles/simpleclient.dir/requires: CMakeFiles/simpleclient.dir/simpleclient.c.o.requires

.PHONY : CMakeFiles/simpleclient.dir/requires

CMakeFiles/simpleclient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/simpleclient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/simpleclient.dir/clean

CMakeFiles/simpleclient.dir/depend:
	cd /home/lzy/GitTest/Ran_test/tinyhttp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lzy/GitTest/Ran_test/tinyhttp /home/lzy/GitTest/Ran_test/tinyhttp /home/lzy/GitTest/Ran_test/tinyhttp/cmake-build-debug /home/lzy/GitTest/Ran_test/tinyhttp/cmake-build-debug /home/lzy/GitTest/Ran_test/tinyhttp/cmake-build-debug/CMakeFiles/simpleclient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simpleclient.dir/depend

