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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/build

# Include any dependencies generated for this target.
include deps/SFGUI/examples/CMakeFiles/ComboBox.dir/depend.make

# Include the progress variables for this target.
include deps/SFGUI/examples/CMakeFiles/ComboBox.dir/progress.make

# Include the compile flags for this target's objects.
include deps/SFGUI/examples/CMakeFiles/ComboBox.dir/flags.make

deps/SFGUI/examples/CMakeFiles/ComboBox.dir/ComboBox.cpp.o: deps/SFGUI/examples/CMakeFiles/ComboBox.dir/flags.make
deps/SFGUI/examples/CMakeFiles/ComboBox.dir/ComboBox.cpp.o: ../deps/SFGUI/examples/ComboBox.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object deps/SFGUI/examples/CMakeFiles/ComboBox.dir/ComboBox.cpp.o"
	cd /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/build/deps/SFGUI/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ComboBox.dir/ComboBox.cpp.o -c /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/deps/SFGUI/examples/ComboBox.cpp

deps/SFGUI/examples/CMakeFiles/ComboBox.dir/ComboBox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ComboBox.dir/ComboBox.cpp.i"
	cd /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/build/deps/SFGUI/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/deps/SFGUI/examples/ComboBox.cpp > CMakeFiles/ComboBox.dir/ComboBox.cpp.i

deps/SFGUI/examples/CMakeFiles/ComboBox.dir/ComboBox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ComboBox.dir/ComboBox.cpp.s"
	cd /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/build/deps/SFGUI/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/deps/SFGUI/examples/ComboBox.cpp -o CMakeFiles/ComboBox.dir/ComboBox.cpp.s

# Object files for target ComboBox
ComboBox_OBJECTS = \
"CMakeFiles/ComboBox.dir/ComboBox.cpp.o"

# External object files for target ComboBox
ComboBox_EXTERNAL_OBJECTS =

deps/SFGUI/examples/ComboBox: deps/SFGUI/examples/CMakeFiles/ComboBox.dir/ComboBox.cpp.o
deps/SFGUI/examples/ComboBox: deps/SFGUI/examples/CMakeFiles/ComboBox.dir/build.make
deps/SFGUI/examples/ComboBox: deps/SFGUI/lib/libSFGUI-d.so
deps/SFGUI/examples/ComboBox: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
deps/SFGUI/examples/ComboBox: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
deps/SFGUI/examples/ComboBox: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
deps/SFGUI/examples/ComboBox: /usr/lib/x86_64-linux-gnu/libGL.so
deps/SFGUI/examples/ComboBox: /usr/lib/x86_64-linux-gnu/libSM.so
deps/SFGUI/examples/ComboBox: /usr/lib/x86_64-linux-gnu/libICE.so
deps/SFGUI/examples/ComboBox: /usr/lib/x86_64-linux-gnu/libX11.so
deps/SFGUI/examples/ComboBox: /usr/lib/x86_64-linux-gnu/libXext.so
deps/SFGUI/examples/ComboBox: deps/SFGUI/examples/CMakeFiles/ComboBox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ComboBox"
	cd /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/build/deps/SFGUI/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ComboBox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/SFGUI/examples/CMakeFiles/ComboBox.dir/build: deps/SFGUI/examples/ComboBox

.PHONY : deps/SFGUI/examples/CMakeFiles/ComboBox.dir/build

deps/SFGUI/examples/CMakeFiles/ComboBox.dir/clean:
	cd /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/build/deps/SFGUI/examples && $(CMAKE_COMMAND) -P CMakeFiles/ComboBox.dir/cmake_clean.cmake
.PHONY : deps/SFGUI/examples/CMakeFiles/ComboBox.dir/clean

deps/SFGUI/examples/CMakeFiles/ComboBox.dir/depend:
	cd /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/deps/SFGUI/examples /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/build /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/build/deps/SFGUI/examples /home/aeri/projects/Wrath-of-the-Crickets-vs-Brigham-Young/build/deps/SFGUI/examples/CMakeFiles/ComboBox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/SFGUI/examples/CMakeFiles/ComboBox.dir/depend
