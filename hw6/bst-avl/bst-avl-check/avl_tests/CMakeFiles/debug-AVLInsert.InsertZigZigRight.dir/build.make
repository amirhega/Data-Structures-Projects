# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check

# Utility rule file for debug-AVLInsert.InsertZigZigRight.

# Include the progress variables for this target.
include avl_tests/CMakeFiles/debug-AVLInsert.InsertZigZigRight.dir/progress.make

avl_tests/CMakeFiles/debug-AVLInsert.InsertZigZigRight:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Debugging AVLInsert.InsertZigZigRight with GDB..."
	cd /home/cs104/CS104/hw-amirhega/hw6/bst-avl && gdb --args /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests/avl_tests --gtest_filter=AVLInsert.InsertZigZigRight

debug-AVLInsert.InsertZigZigRight: avl_tests/CMakeFiles/debug-AVLInsert.InsertZigZigRight
debug-AVLInsert.InsertZigZigRight: avl_tests/CMakeFiles/debug-AVLInsert.InsertZigZigRight.dir/build.make

.PHONY : debug-AVLInsert.InsertZigZigRight

# Rule to build all files generated by this target.
avl_tests/CMakeFiles/debug-AVLInsert.InsertZigZigRight.dir/build: debug-AVLInsert.InsertZigZigRight

.PHONY : avl_tests/CMakeFiles/debug-AVLInsert.InsertZigZigRight.dir/build

avl_tests/CMakeFiles/debug-AVLInsert.InsertZigZigRight.dir/clean:
	cd /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests && $(CMAKE_COMMAND) -P CMakeFiles/debug-AVLInsert.InsertZigZigRight.dir/cmake_clean.cmake
.PHONY : avl_tests/CMakeFiles/debug-AVLInsert.InsertZigZigRight.dir/clean

avl_tests/CMakeFiles/debug-AVLInsert.InsertZigZigRight.dir/depend:
	cd /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests/CMakeFiles/debug-AVLInsert.InsertZigZigRight.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : avl_tests/CMakeFiles/debug-AVLInsert.InsertZigZigRight.dir/depend

