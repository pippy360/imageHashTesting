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

# Special rule for the target test
test:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running tests..."
	/home/linux/Downloads/clion-2016.3.2/bin/cmake/bin/ctest --force-new-ctest-process $(ARGS)
.PHONY : test

# Special rule for the target test
test/fast: test

.PHONY : test/fast

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

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/home/linux/Downloads/clion-2016.3.2/bin/cmake/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/home/linux/Downloads/clion-2016.3.2/bin/cmake/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/home/linux/Downloads/clion-2016.3.2/bin/cmake/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: install/local

.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/home/linux/Downloads/clion-2016.3.2/bin/cmake/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: install/strip

.PHONY : install/strip/fast

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
# Target rules for targets named averageHashTest

# Build rule for target.
averageHashTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 averageHashTest
.PHONY : averageHashTest

# fast build rule for target.
averageHashTest/fast:
	$(MAKE) -f CMakeFiles/averageHashTest.dir/build.make CMakeFiles/averageHashTest.dir/build
.PHONY : averageHashTest/fast

#=============================================================================
# Target rules for targets named app

# Build rule for target.
app: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 app
.PHONY : app

# fast build rule for target.
app/fast:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/build
.PHONY : app/fast

#=============================================================================
# Target rules for targets named gtest_main

# Build rule for target.
gtest_main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gtest_main
.PHONY : gtest_main

# fast build rule for target.
gtest_main/fast:
	$(MAKE) -f googletest/googletest/CMakeFiles/gtest_main.dir/build.make googletest/googletest/CMakeFiles/gtest_main.dir/build
.PHONY : gtest_main/fast

#=============================================================================
# Target rules for targets named gtest

# Build rule for target.
gtest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gtest
.PHONY : gtest

# fast build rule for target.
gtest/fast:
	$(MAKE) -f googletest/googletest/CMakeFiles/gtest.dir/build.make googletest/googletest/CMakeFiles/gtest.dir/build
.PHONY : gtest/fast

c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.o: c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.cpp.o

.PHONY : c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.o

# target to build an object file
c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.cpp.o:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.cpp.o
.PHONY : c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.cpp.o

c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.i: c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.cpp.i

.PHONY : c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.i

# target to preprocess a source file
c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.cpp.i:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.cpp.i
.PHONY : c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.cpp.i

c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.s: c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.cpp.s

.PHONY : c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.s

# target to generate assembly for a file
c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.cpp.s:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.cpp.s
.PHONY : c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.cpp.s

c_src/src/img_hash/img_hash_opencv_module/average_hash.o: c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o

.PHONY : c_src/src/img_hash/img_hash_opencv_module/average_hash.o

# target to build an object file
c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o
.PHONY : c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.o

c_src/src/img_hash/img_hash_opencv_module/average_hash.i: c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.i

.PHONY : c_src/src/img_hash/img_hash_opencv_module/average_hash.i

# target to preprocess a source file
c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.i:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.i
.PHONY : c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.i

c_src/src/img_hash/img_hash_opencv_module/average_hash.s: c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.s

.PHONY : c_src/src/img_hash/img_hash_opencv_module/average_hash.s

# target to generate assembly for a file
c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.s:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.s
.PHONY : c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp.s

c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.o: c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o

.PHONY : c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.o

# target to build an object file
c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o
.PHONY : c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.o

c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.i: c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.i

.PHONY : c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.i

# target to preprocess a source file
c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.i:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.i
.PHONY : c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.i

c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.s: c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.s

.PHONY : c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.s

# target to generate assembly for a file
c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.s:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.s
.PHONY : c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp.s

c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.o: c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o

.PHONY : c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.o

# target to build an object file
c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o
.PHONY : c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.o

c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.i: c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.i

.PHONY : c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.i

# target to preprocess a source file
c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.i:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.i
.PHONY : c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.i

c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.s: c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.s

.PHONY : c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.s

# target to generate assembly for a file
c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.s:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.s
.PHONY : c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp.s

c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.o: c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o

.PHONY : c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.o

# target to build an object file
c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o
.PHONY : c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.o

c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.i: c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.i

.PHONY : c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.i

# target to preprocess a source file
c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.i:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.i
.PHONY : c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.i

c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.s: c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.s

.PHONY : c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.s

# target to generate assembly for a file
c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.s:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.s
.PHONY : c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp.s

c_src/src/img_hash/img_hash_opencv_module/phash.o: c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o

.PHONY : c_src/src/img_hash/img_hash_opencv_module/phash.o

# target to build an object file
c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o
.PHONY : c_src/src/img_hash/img_hash_opencv_module/phash.cpp.o

c_src/src/img_hash/img_hash_opencv_module/phash.i: c_src/src/img_hash/img_hash_opencv_module/phash.cpp.i

.PHONY : c_src/src/img_hash/img_hash_opencv_module/phash.i

# target to preprocess a source file
c_src/src/img_hash/img_hash_opencv_module/phash.cpp.i:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.i
.PHONY : c_src/src/img_hash/img_hash_opencv_module/phash.cpp.i

c_src/src/img_hash/img_hash_opencv_module/phash.s: c_src/src/img_hash/img_hash_opencv_module/phash.cpp.s

.PHONY : c_src/src/img_hash/img_hash_opencv_module/phash.s

# target to generate assembly for a file
c_src/src/img_hash/img_hash_opencv_module/phash.cpp.s:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/img_hash/img_hash_opencv_module/phash.cpp.s
.PHONY : c_src/src/img_hash/img_hash_opencv_module/phash.cpp.s

c_src/src/main.o: c_src/src/main.cc.o

.PHONY : c_src/src/main.o

# target to build an object file
c_src/src/main.cc.o:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/main.cc.o
.PHONY : c_src/src/main.cc.o

c_src/src/main.i: c_src/src/main.cc.i

.PHONY : c_src/src/main.i

# target to preprocess a source file
c_src/src/main.cc.i:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/main.cc.i
.PHONY : c_src/src/main.cc.i

c_src/src/main.s: c_src/src/main.cc.s

.PHONY : c_src/src/main.s

# target to generate assembly for a file
c_src/src/main.cc.s:
	$(MAKE) -f CMakeFiles/app.dir/build.make CMakeFiles/app.dir/c_src/src/main.cc.s
.PHONY : c_src/src/main.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... test"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... list_install_components"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... averageHashTest"
	@echo "... app"
	@echo "... gtest_main"
	@echo "... gtest"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.o"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.i"
	@echo "... c_src/src/img_hash/img_hash_opencv_module/PHash_Fast.s"
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
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

