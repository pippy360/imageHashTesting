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
CMAKE_SOURCE_DIR = /home/linux/imageHashTesting

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/linux/imageHashTesting

# Include any dependencies generated for this target.
include CMakeFiles/averageHashTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/averageHashTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/averageHashTest.dir/flags.make

CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o: CMakeFiles/averageHashTest.dir/flags.make
CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o: c_src/test/averageHashTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linux/imageHashTesting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o -c /home/linux/imageHashTesting/c_src/test/averageHashTest.cpp

CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linux/imageHashTesting/c_src/test/averageHashTest.cpp > CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.i

CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linux/imageHashTesting/c_src/test/averageHashTest.cpp -o CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.s

CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o.requires:

.PHONY : CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o.requires

CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o.provides: CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/averageHashTest.dir/build.make CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o.provides.build
.PHONY : CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o.provides

CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o.provides.build: CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o


CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o: CMakeFiles/averageHashTest.dir/flags.make
CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o: c_src/test/blockMeanHashTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linux/imageHashTesting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o -c /home/linux/imageHashTesting/c_src/test/blockMeanHashTest.cpp

CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linux/imageHashTesting/c_src/test/blockMeanHashTest.cpp > CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.i

CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linux/imageHashTesting/c_src/test/blockMeanHashTest.cpp -o CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.s

CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o.requires:

.PHONY : CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o.requires

CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o.provides: CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/averageHashTest.dir/build.make CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o.provides.build
.PHONY : CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o.provides

CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o.provides.build: CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o


CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o: CMakeFiles/averageHashTest.dir/flags.make
CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o: c_src/test/perceptualHashTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linux/imageHashTesting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o -c /home/linux/imageHashTesting/c_src/test/perceptualHashTest.cpp

CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linux/imageHashTesting/c_src/test/perceptualHashTest.cpp > CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.i

CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linux/imageHashTesting/c_src/test/perceptualHashTest.cpp -o CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.s

CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o.requires:

.PHONY : CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o.requires

CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o.provides: CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/averageHashTest.dir/build.make CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o.provides.build
.PHONY : CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o.provides

CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o.provides.build: CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o


CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o: CMakeFiles/averageHashTest.dir/flags.make
CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o: c_src/test/utilsTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linux/imageHashTesting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o -c /home/linux/imageHashTesting/c_src/test/utilsTest.cpp

CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linux/imageHashTesting/c_src/test/utilsTest.cpp > CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.i

CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linux/imageHashTesting/c_src/test/utilsTest.cpp -o CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.s

CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o.requires:

.PHONY : CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o.requires

CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o.provides: CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/averageHashTest.dir/build.make CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o.provides.build
.PHONY : CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o.provides

CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o.provides.build: CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o


CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o: CMakeFiles/averageHashTest.dir/flags.make
CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o: c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linux/imageHashTesting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o -c /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp > CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.i

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp -o CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.s

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o.requires:

.PHONY : CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o.requires

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o.provides: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o.requires
	$(MAKE) -f CMakeFiles/averageHashTest.dir/build.make CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o.provides.build
.PHONY : CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o.provides

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o.provides.build: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o


CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o: CMakeFiles/averageHashTest.dir/flags.make
CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o: c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linux/imageHashTesting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o -c /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp > CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.i

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp -o CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.s

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o.requires:

.PHONY : CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o.requires

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o.provides: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o.requires
	$(MAKE) -f CMakeFiles/averageHashTest.dir/build.make CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o.provides.build
.PHONY : CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o.provides

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o.provides.build: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o


CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o: CMakeFiles/averageHashTest.dir/flags.make
CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o: c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linux/imageHashTesting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o -c /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp > CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.i

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp -o CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.s

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o.requires:

.PHONY : CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o.requires

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o.provides: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o.requires
	$(MAKE) -f CMakeFiles/averageHashTest.dir/build.make CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o.provides.build
.PHONY : CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o.provides

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o.provides.build: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o


CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o: CMakeFiles/averageHashTest.dir/flags.make
CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o: c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linux/imageHashTesting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o -c /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp > CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.i

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp -o CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.s

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o.requires:

.PHONY : CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o.requires

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o.provides: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o.requires
	$(MAKE) -f CMakeFiles/averageHashTest.dir/build.make CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o.provides.build
.PHONY : CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o.provides

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o.provides.build: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o


CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o: CMakeFiles/averageHashTest.dir/flags.make
CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o: c_src/src/img_hash/img_hash_opencv_module/phash.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linux/imageHashTesting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o -c /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/phash.cpp

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/phash.cpp > CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.i

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linux/imageHashTesting/c_src/src/img_hash/img_hash_opencv_module/phash.cpp -o CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.s

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o.requires:

.PHONY : CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o.requires

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o.provides: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o.requires
	$(MAKE) -f CMakeFiles/averageHashTest.dir/build.make CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o.provides.build
.PHONY : CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o.provides

CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o.provides.build: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o


# Object files for target averageHashTest
averageHashTest_OBJECTS = \
"CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o" \
"CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o" \
"CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o" \
"CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o" \
"CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o" \
"CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o" \
"CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o" \
"CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o" \
"CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o"

# External object files for target averageHashTest
averageHashTest_EXTERNAL_OBJECTS =

averageHashTest: CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o
averageHashTest: CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o
averageHashTest: CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o
averageHashTest: CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o
averageHashTest: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o
averageHashTest: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o
averageHashTest: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o
averageHashTest: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o
averageHashTest: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o
averageHashTest: CMakeFiles/averageHashTest.dir/build.make
averageHashTest: googletest/googletest/libgtest.a
averageHashTest: googletest/googletest/libgtest_main.a
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.9
averageHashTest: googletest/googletest/libgtest.a
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.9
averageHashTest: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.9
averageHashTest: CMakeFiles/averageHashTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/linux/imageHashTesting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable averageHashTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/averageHashTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/averageHashTest.dir/build: averageHashTest

.PHONY : CMakeFiles/averageHashTest.dir/build

CMakeFiles/averageHashTest.dir/requires: CMakeFiles/averageHashTest.dir/c_src/test/averageHashTest.cpp.o.requires
CMakeFiles/averageHashTest.dir/requires: CMakeFiles/averageHashTest.dir/c_src/test/blockMeanHashTest.cpp.o.requires
CMakeFiles/averageHashTest.dir/requires: CMakeFiles/averageHashTest.dir/c_src/test/perceptualHashTest.cpp.o.requires
CMakeFiles/averageHashTest.dir/requires: CMakeFiles/averageHashTest.dir/c_src/test/utilsTest.cpp.o.requires
CMakeFiles/averageHashTest.dir/requires: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o.requires
CMakeFiles/averageHashTest.dir/requires: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o.requires
CMakeFiles/averageHashTest.dir/requires: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o.requires
CMakeFiles/averageHashTest.dir/requires: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o.requires
CMakeFiles/averageHashTest.dir/requires: CMakeFiles/averageHashTest.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o.requires

.PHONY : CMakeFiles/averageHashTest.dir/requires

CMakeFiles/averageHashTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/averageHashTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/averageHashTest.dir/clean

CMakeFiles/averageHashTest.dir/depend:
	cd /home/linux/imageHashTesting && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/linux/imageHashTesting /home/linux/imageHashTesting /home/linux/imageHashTesting /home/linux/imageHashTesting /home/linux/imageHashTesting/CMakeFiles/averageHashTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/averageHashTest.dir/depend

