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
CMAKE_COMMAND = /snap/clion/169/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/169/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yassa/CLionProjects/edumenagemantsys

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yassa/CLionProjects/edumenagemantsys/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/edumenagementsys.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/edumenagementsys.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/edumenagementsys.dir/flags.make

CMakeFiles/edumenagementsys.dir/main.cpp.o: CMakeFiles/edumenagementsys.dir/flags.make
CMakeFiles/edumenagementsys.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yassa/CLionProjects/edumenagemantsys/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/edumenagementsys.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/edumenagementsys.dir/main.cpp.o -c /home/yassa/CLionProjects/edumenagemantsys/main.cpp

CMakeFiles/edumenagementsys.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/edumenagementsys.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yassa/CLionProjects/edumenagemantsys/main.cpp > CMakeFiles/edumenagementsys.dir/main.cpp.i

CMakeFiles/edumenagementsys.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/edumenagementsys.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yassa/CLionProjects/edumenagemantsys/main.cpp -o CMakeFiles/edumenagementsys.dir/main.cpp.s

CMakeFiles/edumenagementsys.dir/source_files/helper_functions.cpp.o: CMakeFiles/edumenagementsys.dir/flags.make
CMakeFiles/edumenagementsys.dir/source_files/helper_functions.cpp.o: ../source_files/helper_functions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yassa/CLionProjects/edumenagemantsys/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/edumenagementsys.dir/source_files/helper_functions.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/edumenagementsys.dir/source_files/helper_functions.cpp.o -c /home/yassa/CLionProjects/edumenagemantsys/source_files/helper_functions.cpp

CMakeFiles/edumenagementsys.dir/source_files/helper_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/edumenagementsys.dir/source_files/helper_functions.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yassa/CLionProjects/edumenagemantsys/source_files/helper_functions.cpp > CMakeFiles/edumenagementsys.dir/source_files/helper_functions.cpp.i

CMakeFiles/edumenagementsys.dir/source_files/helper_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/edumenagementsys.dir/source_files/helper_functions.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yassa/CLionProjects/edumenagemantsys/source_files/helper_functions.cpp -o CMakeFiles/edumenagementsys.dir/source_files/helper_functions.cpp.s

CMakeFiles/edumenagementsys.dir/database_class/Database.cpp.o: CMakeFiles/edumenagementsys.dir/flags.make
CMakeFiles/edumenagementsys.dir/database_class/Database.cpp.o: ../database_class/Database.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yassa/CLionProjects/edumenagemantsys/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/edumenagementsys.dir/database_class/Database.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/edumenagementsys.dir/database_class/Database.cpp.o -c /home/yassa/CLionProjects/edumenagemantsys/database_class/Database.cpp

CMakeFiles/edumenagementsys.dir/database_class/Database.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/edumenagementsys.dir/database_class/Database.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yassa/CLionProjects/edumenagemantsys/database_class/Database.cpp > CMakeFiles/edumenagementsys.dir/database_class/Database.cpp.i

CMakeFiles/edumenagementsys.dir/database_class/Database.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/edumenagementsys.dir/database_class/Database.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yassa/CLionProjects/edumenagemantsys/database_class/Database.cpp -o CMakeFiles/edumenagementsys.dir/database_class/Database.cpp.s

# Object files for target edumenagementsys
edumenagementsys_OBJECTS = \
"CMakeFiles/edumenagementsys.dir/main.cpp.o" \
"CMakeFiles/edumenagementsys.dir/source_files/helper_functions.cpp.o" \
"CMakeFiles/edumenagementsys.dir/database_class/Database.cpp.o"

# External object files for target edumenagementsys
edumenagementsys_EXTERNAL_OBJECTS =

edumenagementsys: CMakeFiles/edumenagementsys.dir/main.cpp.o
edumenagementsys: CMakeFiles/edumenagementsys.dir/source_files/helper_functions.cpp.o
edumenagementsys: CMakeFiles/edumenagementsys.dir/database_class/Database.cpp.o
edumenagementsys: CMakeFiles/edumenagementsys.dir/build.make
edumenagementsys: CMakeFiles/edumenagementsys.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yassa/CLionProjects/edumenagemantsys/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable edumenagementsys"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/edumenagementsys.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/edumenagementsys.dir/build: edumenagementsys
.PHONY : CMakeFiles/edumenagementsys.dir/build

CMakeFiles/edumenagementsys.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/edumenagementsys.dir/cmake_clean.cmake
.PHONY : CMakeFiles/edumenagementsys.dir/clean

CMakeFiles/edumenagementsys.dir/depend:
	cd /home/yassa/CLionProjects/edumenagemantsys/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yassa/CLionProjects/edumenagemantsys /home/yassa/CLionProjects/edumenagemantsys /home/yassa/CLionProjects/edumenagemantsys/cmake-build-debug /home/yassa/CLionProjects/edumenagemantsys/cmake-build-debug /home/yassa/CLionProjects/edumenagemantsys/cmake-build-debug/CMakeFiles/edumenagementsys.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/edumenagementsys.dir/depend

