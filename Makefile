# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /home/linux/Downloads/clion-2016.3.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/linux/Downloads/clion-2016.3.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/linux/imageHashTesting

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/linux/imageHashTesting

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/home/linux/Downloads/clion-2016.3.2/bin/cmake/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/home/linux/Downloads/clion-2016.3.2/bin/cmake/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/linux/imageHashTesting/CMakeFiles /home/linux/imageHashTesting/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/linux/imageHashTesting/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named test1

# Build rule for target.
test1: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test1
.PHONY : test1

# fast build rule for target.
test1/fast:
	$(MAKE) -f CMakeFiles/test1.dir/build.make CMakeFiles/test1.dir/build
.PHONY : test1/fast

#=============================================================================
# Target rules for targets named imageHashTesting

# Build rule for target.
imageHashTesting: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 imageHashTesting
.PHONY : imageHashTesting

# fast build rule for target.
imageHashTesting/fast:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/build
.PHONY : imageHashTesting/fast

c_src/src/img_hash/img_hash_opencv_module/average_hash.o: c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o

.PHONY : c_src/src/img_hash/img_hash_opencv_module/average_hash.o

# target to build an object file
c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o
.PHONY : c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o

c_src/src/img_hash/img_hash_opencv_module/average_hash.i: c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.i

.PHONY : c_src/src/img_hash/img_hash_opencv_module/average_hash.i

# target to preprocess a source file
c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.i:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.i
.PHONY : c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.i

c_src/src/img_hash/img_hash_opencv_module/average_hash.s: c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.s

.PHONY : c_src/src/img_hash/img_hash_opencv_module/average_hash.s

# target to generate assembly for a file
c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.s:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.s
.PHONY : c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.s

c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.o: c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o

.PHONY : c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.o

# target to build an object file
c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o
.PHONY : c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o

c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.i: c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.i

.PHONY : c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.i

# target to preprocess a source file
c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.i:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.i
.PHONY : c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.i

c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.s: c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.s

.PHONY : c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.s

# target to generate assembly for a file
c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.s:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.s
.PHONY : c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.s

c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.o: c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o

.PHONY : c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.o

# target to build an object file
c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o
.PHONY : c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o

c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.i: c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.i

.PHONY : c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.i

# target to preprocess a source file
c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.i:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.i
.PHONY : c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.i

c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.s: c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.s

.PHONY : c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.s

# target to generate assembly for a file
c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.s:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.s
.PHONY : c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.s

c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.o: c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o

.PHONY : c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.o

# target to build an object file
c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o
.PHONY : c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o

c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.i: c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.i

.PHONY : c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.i

# target to preprocess a source file
c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.i:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.i
.PHONY : c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.i

c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.s: c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.s

.PHONY : c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.s

# target to generate assembly for a file
c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.s:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.s
.PHONY : c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.s

c_src/src/img_hash/img_hash_opencv_module/phash.o: c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o

.PHONY : c_src/src/img_hash/img_hash_opencv_module/phash.o

# target to build an object file
c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o
.PHONY : c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o

c_src/src/img_hash/img_hash_opencv_module/phash.i: c_src/src/img_hash/img_hash_opencv_module/phash.cpp.i

.PHONY : c_src/src/img_hash/img_hash_opencv_module/phash.i

# target to preprocess a source file
c_src/src/img_hash/img_hash_opencv_module/phash.cpp.i:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.i
.PHONY : c_src/src/img_hash/img_hash_opencv_module/phash.cpp.i

c_src/src/img_hash/img_hash_opencv_module/phash.s: c_src/src/img_hash/img_hash_opencv_module/phash.cpp.s

.PHONY : c_src/src/img_hash/img_hash_opencv_module/phash.s

# target to generate assembly for a file
c_src/src/img_hash/img_hash_opencv_module/phash.cpp.s:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.s
.PHONY : c_src/src/img_hash/img_hash_opencv_module/phash.cpp.s

c_src/src/main.o: c_src/src/main.cc.o

.PHONY : c_src/src/main.o

# target to build an object file
c_src/src/main.cc.o:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/main.cc.o
.PHONY : c_src/src/main.cc.o

c_src/src/main.i: c_src/src/main.cc.i

.PHONY : c_src/src/main.i

# target to preprocess a source file
c_src/src/main.cc.i:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/main.cc.i
.PHONY : c_src/src/main.cc.i

c_src/src/main.s: c_src/src/main.cc.s

.PHONY : c_src/src/main.s

# target to generate assembly for a file
c_src/src/main.cc.s:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/main.cc.s
.PHONY : c_src/src/main.cc.s

c_src/src/mainImageProcessingFunctions.o: c_src/src/mainImageProcessingFunctions.cpp.o

.PHONY : c_src/src/mainImageProcessingFunctions.o

# target to build an object file
c_src/src/mainImageProcessingFunctions.cpp.o:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/mainImageProcessingFunctions.cpp.o
.PHONY : c_src/src/mainImageProcessingFunctions.cpp.o

c_src/src/mainImageProcessingFunctions.i: c_src/src/mainImageProcessingFunctions.cpp.i

.PHONY : c_src/src/mainImageProcessingFunctions.i

# target to preprocess a source file
c_src/src/mainImageProcessingFunctions.cpp.i:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/mainImageProcessingFunctions.cpp.i
.PHONY : c_src/src/mainImageProcessingFunctions.cpp.i

c_src/src/mainImageProcessingFunctions.s: c_src/src/mainImageProcessingFunctions.cpp.s

.PHONY : c_src/src/mainImageProcessingFunctions.s

# target to generate assembly for a file
c_src/src/mainImageProcessingFunctions.cpp.s:
	$(MAKE) -f CMakeFiles/imageHashTesting.dir/build.make CMakeFiles/imageHashTesting.dir/c_src/src/mainImageProcessingFunctions.cpp.s
.PHONY : c_src/src/mainImageProcessingFunctions.cpp.s

c_src/test/hashTests.o: c_src/test/hashTests.cpp.o

.PHONY : c_src/test/hashTests.o

# target to build an object file
c_src/test/hashTests.cpp.o:
	$(MAKE) -f CMakeFiles/test1.dir/build.make CMakeFiles/test1.dir/c_src/test/hashTests.cpp.o
.PHONY : c_src/test/hashTests.cpp.o

c_src/test/hashTests.i: c_src/test/hashTests.cpp.i

.PHONY : c_src/test/hashTests.i

# target to preprocess a source file
c_src/test/hashTests.cpp.i:
	$(MAKE) -f CMakeFiles/test1.dir/build.make CMakeFiles/test1.dir/c_src/test/hashTests.cpp.i
.PHONY : c_src/test/hashTests.cpp.i

c_src/test/hashTests.s: c_src/test/hashTests.cpp.s

.PHONY : c_src/test/hashTests.s

# target to generate assembly for a file
c_src/test/hashTests.cpp.s:
	$(MAKE) -f CMakeFiles/test1.dir/build.make CMakeFiles/test1.dir/c_src/test/hashTests.cpp.s
.PHONY : c_src/test/hashTests.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... test1"
	@echo "... imageHashTesting"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/average_hash.o"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/average_hash.i"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/average_hash.s"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.o"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.i"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.s"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.o"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.i"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.s"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.o"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.i"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.s"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/phash.o"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/phash.i"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/phash.s"
	@echo "... c_src/src/main.o"
	@echo "... c_src/src/main.i"
	@echo "... c_src/src/main.s"
	@echo "... c_src/src/mainImageProcessingFunctions.o"
	@echo "... c_src/src/mainImageProcessingFunctions.i"
	@echo "... c_src/src/mainImageProcessingFunctions.s"
	@echo "... c_src/test/hashTests.o"
	@echo "... c_src/test/hashTests.i"
	@echo "... c_src/test/hashTests.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

