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

# Include any dependencies generated for this target.
include avl_tests/CMakeFiles/avl_tests.dir/depend.make

# Include the progress variables for this target.
include avl_tests/CMakeFiles/avl_tests.dir/progress.make

# Include the compile flags for this target's objects.
include avl_tests/CMakeFiles/avl_tests.dir/flags.make

avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.o: avl_tests/CMakeFiles/avl_tests.dir/flags.make
avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.o: avl_tests/test_insert.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.o"
	cd /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/avl_tests.dir/test_insert.cpp.o -c /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests/test_insert.cpp

avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/avl_tests.dir/test_insert.cpp.i"
	cd /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests/test_insert.cpp > CMakeFiles/avl_tests.dir/test_insert.cpp.i

avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/avl_tests.dir/test_insert.cpp.s"
	cd /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests/test_insert.cpp -o CMakeFiles/avl_tests.dir/test_insert.cpp.s

avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.o.requires:

.PHONY : avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.o.requires

avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.o.provides: avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.o.requires
	$(MAKE) -f avl_tests/CMakeFiles/avl_tests.dir/build.make avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.o.provides.build
.PHONY : avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.o.provides

avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.o.provides.build: avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.o


avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.o: avl_tests/CMakeFiles/avl_tests.dir/flags.make
avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.o: avl_tests/test_remove.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.o"
	cd /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/avl_tests.dir/test_remove.cpp.o -c /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests/test_remove.cpp

avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/avl_tests.dir/test_remove.cpp.i"
	cd /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests/test_remove.cpp > CMakeFiles/avl_tests.dir/test_remove.cpp.i

avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/avl_tests.dir/test_remove.cpp.s"
	cd /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests/test_remove.cpp -o CMakeFiles/avl_tests.dir/test_remove.cpp.s

avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.o.requires:

.PHONY : avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.o.requires

avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.o.provides: avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.o.requires
	$(MAKE) -f avl_tests/CMakeFiles/avl_tests.dir/build.make avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.o.provides.build
.PHONY : avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.o.provides

avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.o.provides.build: avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.o


# Object files for target avl_tests
avl_tests_OBJECTS = \
"CMakeFiles/avl_tests.dir/test_insert.cpp.o" \
"CMakeFiles/avl_tests.dir/test_remove.cpp.o"

# External object files for target avl_tests
avl_tests_EXTERNAL_OBJECTS =

avl_tests/avl_tests: avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.o
avl_tests/avl_tests: avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.o
avl_tests/avl_tests: avl_tests/CMakeFiles/avl_tests.dir/build.make
avl_tests/avl_tests: testing_utils/libtesting_utils.a
avl_tests/avl_tests: /usr/lib/libgtest_main.a
avl_tests/avl_tests: /usr/lib/libgtest.a
avl_tests/avl_tests: testing_utils/kwsys/libkwsys.a
avl_tests/avl_tests: testing_utils/libperf/libperf.a
avl_tests/avl_tests: avl_tests/CMakeFiles/avl_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable avl_tests"
	cd /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/avl_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
avl_tests/CMakeFiles/avl_tests.dir/build: avl_tests/avl_tests

.PHONY : avl_tests/CMakeFiles/avl_tests.dir/build

avl_tests/CMakeFiles/avl_tests.dir/requires: avl_tests/CMakeFiles/avl_tests.dir/test_insert.cpp.o.requires
avl_tests/CMakeFiles/avl_tests.dir/requires: avl_tests/CMakeFiles/avl_tests.dir/test_remove.cpp.o.requires

.PHONY : avl_tests/CMakeFiles/avl_tests.dir/requires

avl_tests/CMakeFiles/avl_tests.dir/clean:
	cd /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests && $(CMAKE_COMMAND) -P CMakeFiles/avl_tests.dir/cmake_clean.cmake
.PHONY : avl_tests/CMakeFiles/avl_tests.dir/clean

avl_tests/CMakeFiles/avl_tests.dir/depend:
	cd /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests /home/cs104/CS104/hw-amirhega/hw6/bst-avl/bst-avl-check/avl_tests/CMakeFiles/avl_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : avl_tests/CMakeFiles/avl_tests.dir/depend

