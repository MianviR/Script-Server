# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mianvi/projects/Script-Server/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mianvi/projects/Script-Server/build

# Include any dependencies generated for this target.
include CMakeFiles/server_beast.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server_beast.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server_beast.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server_beast.dir/flags.make

CMakeFiles/server_beast.dir/codegen:
.PHONY : CMakeFiles/server_beast.dir/codegen

CMakeFiles/server_beast.dir/server_beast.cpp.o: CMakeFiles/server_beast.dir/flags.make
CMakeFiles/server_beast.dir/server_beast.cpp.o: /home/mianvi/projects/Script-Server/src/server_beast.cpp
CMakeFiles/server_beast.dir/server_beast.cpp.o: CMakeFiles/server_beast.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/mianvi/projects/Script-Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server_beast.dir/server_beast.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server_beast.dir/server_beast.cpp.o -MF CMakeFiles/server_beast.dir/server_beast.cpp.o.d -o CMakeFiles/server_beast.dir/server_beast.cpp.o -c /home/mianvi/projects/Script-Server/src/server_beast.cpp

CMakeFiles/server_beast.dir/server_beast.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server_beast.dir/server_beast.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mianvi/projects/Script-Server/src/server_beast.cpp > CMakeFiles/server_beast.dir/server_beast.cpp.i

CMakeFiles/server_beast.dir/server_beast.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server_beast.dir/server_beast.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mianvi/projects/Script-Server/src/server_beast.cpp -o CMakeFiles/server_beast.dir/server_beast.cpp.s

# Object files for target server_beast
server_beast_OBJECTS = \
"CMakeFiles/server_beast.dir/server_beast.cpp.o"

# External object files for target server_beast
server_beast_EXTERNAL_OBJECTS =

server_beast: CMakeFiles/server_beast.dir/server_beast.cpp.o
server_beast: CMakeFiles/server_beast.dir/build.make
server_beast: CMakeFiles/server_beast.dir/compiler_depend.ts
server_beast: /home/mianvi/libs/cpp/boost_1_88_0/stage/lib/libboost_filesystem.so.1.88.0
server_beast: /home/mianvi/libs/cpp/boost_1_88_0/stage/lib/libboost_system.so.1.88.0
server_beast: /home/mianvi/libs/cpp/boost_1_88_0/stage/lib/libboost_atomic.so.1.88.0
server_beast: CMakeFiles/server_beast.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/mianvi/projects/Script-Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable server_beast"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server_beast.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server_beast.dir/build: server_beast
.PHONY : CMakeFiles/server_beast.dir/build

CMakeFiles/server_beast.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server_beast.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server_beast.dir/clean

CMakeFiles/server_beast.dir/depend:
	cd /home/mianvi/projects/Script-Server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mianvi/projects/Script-Server/src /home/mianvi/projects/Script-Server/src /home/mianvi/projects/Script-Server/build /home/mianvi/projects/Script-Server/build /home/mianvi/projects/Script-Server/build/CMakeFiles/server_beast.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/server_beast.dir/depend

