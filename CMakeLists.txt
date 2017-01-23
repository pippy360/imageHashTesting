cmake_minimum_required(VERSION 3.6)
project(imageHashTesting)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp
        c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp
        c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp
        c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp
        c_src/src/img_hash/img_hash_opencv_module/phash.cpp
        c_src/src/img_hash/img_hash_opencv_module/radial_variance_hash.cpp
        c_src/src/main.cc
        c_src/src/mainImageProcessingFunctions.cpp)

add_executable(imageHashTesting ${SOURCE_FILES})