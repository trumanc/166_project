# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1

# Include any dependencies generated for this target.
include CMakeFiles/btree_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/btree_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/btree_test.dir/flags.make

CMakeFiles/btree_test.dir/btree_test.cc.o: CMakeFiles/btree_test.dir/flags.make
CMakeFiles/btree_test.dir/btree_test.cc.o: btree_test.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/btree_test.dir/btree_test.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/btree_test.dir/btree_test.cc.o -c /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1/btree_test.cc

CMakeFiles/btree_test.dir/btree_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/btree_test.dir/btree_test.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1/btree_test.cc > CMakeFiles/btree_test.dir/btree_test.cc.i

CMakeFiles/btree_test.dir/btree_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/btree_test.dir/btree_test.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1/btree_test.cc -o CMakeFiles/btree_test.dir/btree_test.cc.s

CMakeFiles/btree_test.dir/btree_test.cc.o.requires:
.PHONY : CMakeFiles/btree_test.dir/btree_test.cc.o.requires

CMakeFiles/btree_test.dir/btree_test.cc.o.provides: CMakeFiles/btree_test.dir/btree_test.cc.o.requires
	$(MAKE) -f CMakeFiles/btree_test.dir/build.make CMakeFiles/btree_test.dir/btree_test.cc.o.provides.build
.PHONY : CMakeFiles/btree_test.dir/btree_test.cc.o.provides

CMakeFiles/btree_test.dir/btree_test.cc.o.provides.build: CMakeFiles/btree_test.dir/btree_test.cc.o

CMakeFiles/btree_test.dir/btree_test_flags.cc.o: CMakeFiles/btree_test.dir/flags.make
CMakeFiles/btree_test.dir/btree_test_flags.cc.o: btree_test_flags.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/btree_test.dir/btree_test_flags.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/btree_test.dir/btree_test_flags.cc.o -c /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1/btree_test_flags.cc

CMakeFiles/btree_test.dir/btree_test_flags.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/btree_test.dir/btree_test_flags.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1/btree_test_flags.cc > CMakeFiles/btree_test.dir/btree_test_flags.cc.i

CMakeFiles/btree_test.dir/btree_test_flags.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/btree_test.dir/btree_test_flags.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1/btree_test_flags.cc -o CMakeFiles/btree_test.dir/btree_test_flags.cc.s

CMakeFiles/btree_test.dir/btree_test_flags.cc.o.requires:
.PHONY : CMakeFiles/btree_test.dir/btree_test_flags.cc.o.requires

CMakeFiles/btree_test.dir/btree_test_flags.cc.o.provides: CMakeFiles/btree_test.dir/btree_test_flags.cc.o.requires
	$(MAKE) -f CMakeFiles/btree_test.dir/build.make CMakeFiles/btree_test.dir/btree_test_flags.cc.o.provides.build
.PHONY : CMakeFiles/btree_test.dir/btree_test_flags.cc.o.provides

CMakeFiles/btree_test.dir/btree_test_flags.cc.o.provides.build: CMakeFiles/btree_test.dir/btree_test_flags.cc.o

# Object files for target btree_test
btree_test_OBJECTS = \
"CMakeFiles/btree_test.dir/btree_test.cc.o" \
"CMakeFiles/btree_test.dir/btree_test_flags.cc.o"

# External object files for target btree_test
btree_test_EXTERNAL_OBJECTS =

btree_test: CMakeFiles/btree_test.dir/btree_test.cc.o
btree_test: CMakeFiles/btree_test.dir/btree_test_flags.cc.o
btree_test: CMakeFiles/btree_test.dir/build.make
btree_test: gtest/libgtest_main.so
btree_test: gtest/libgtest.so
btree_test: gflags/libgflags_nothreads.so.2.2.0
btree_test: CMakeFiles/btree_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable btree_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/btree_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/btree_test.dir/build: btree_test
.PHONY : CMakeFiles/btree_test.dir/build

CMakeFiles/btree_test.dir/requires: CMakeFiles/btree_test.dir/btree_test.cc.o.requires
CMakeFiles/btree_test.dir/requires: CMakeFiles/btree_test.dir/btree_test_flags.cc.o.requires
.PHONY : CMakeFiles/btree_test.dir/requires

CMakeFiles/btree_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/btree_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/btree_test.dir/clean

CMakeFiles/btree_test.dir/depend:
	cd /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1 /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1 /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1 /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1 /home/truman/Dropbox/Courses/DS_CS166/project/code/cpp-btree-1.0.1/CMakeFiles/btree_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/btree_test.dir/depend

