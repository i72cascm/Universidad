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
CMAKE_SOURCE_DIR = /home/manuelcasas/Universidad/Estructura_de_Datos/Academia/ModoExamen/1/try

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/manuelcasas/Universidad/Estructura_de_Datos/Academia/ModoExamen/1/try/build

# Include any dependencies generated for this target.
include CMakeFiles/test_slist.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_slist.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_slist.dir/flags.make

CMakeFiles/test_slist.dir/test_slist.cpp.o: CMakeFiles/test_slist.dir/flags.make
CMakeFiles/test_slist.dir/test_slist.cpp.o: ../test_slist.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manuelcasas/Universidad/Estructura_de_Datos/Academia/ModoExamen/1/try/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_slist.dir/test_slist.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_slist.dir/test_slist.cpp.o -c /home/manuelcasas/Universidad/Estructura_de_Datos/Academia/ModoExamen/1/try/test_slist.cpp

CMakeFiles/test_slist.dir/test_slist.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_slist.dir/test_slist.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/manuelcasas/Universidad/Estructura_de_Datos/Academia/ModoExamen/1/try/test_slist.cpp > CMakeFiles/test_slist.dir/test_slist.cpp.i

CMakeFiles/test_slist.dir/test_slist.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_slist.dir/test_slist.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/manuelcasas/Universidad/Estructura_de_Datos/Academia/ModoExamen/1/try/test_slist.cpp -o CMakeFiles/test_slist.dir/test_slist.cpp.s

# Object files for target test_slist
test_slist_OBJECTS = \
"CMakeFiles/test_slist.dir/test_slist.cpp.o"

# External object files for target test_slist
test_slist_EXTERNAL_OBJECTS =

test_slist: CMakeFiles/test_slist.dir/test_slist.cpp.o
test_slist: CMakeFiles/test_slist.dir/build.make
test_slist: CMakeFiles/test_slist.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/manuelcasas/Universidad/Estructura_de_Datos/Academia/ModoExamen/1/try/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_slist"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_slist.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_slist.dir/build: test_slist

.PHONY : CMakeFiles/test_slist.dir/build

CMakeFiles/test_slist.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_slist.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_slist.dir/clean

CMakeFiles/test_slist.dir/depend:
	cd /home/manuelcasas/Universidad/Estructura_de_Datos/Academia/ModoExamen/1/try/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/manuelcasas/Universidad/Estructura_de_Datos/Academia/ModoExamen/1/try /home/manuelcasas/Universidad/Estructura_de_Datos/Academia/ModoExamen/1/try /home/manuelcasas/Universidad/Estructura_de_Datos/Academia/ModoExamen/1/try/build /home/manuelcasas/Universidad/Estructura_de_Datos/Academia/ModoExamen/1/try/build /home/manuelcasas/Universidad/Estructura_de_Datos/Academia/ModoExamen/1/try/build/CMakeFiles/test_slist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_slist.dir/depend

