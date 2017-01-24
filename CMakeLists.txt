cmake_minimum_required(VERSION 3.5)
project(imageHashTesting)

set(CMAKE_CXX_STANDARD 11)

include_directories(c_src/src)

set(SOURCE_FILES
        c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp
        c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp
        c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp
        c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp
        c_src/src/img_hash/img_hash_opencv_module/phash.cpp
        c_src/src/main.cc
        c_src/src/mainImageProcessingFunctions.cpp)

find_package( OpenCV REQUIRED )

add_executable(imageHashTesting ${SOURCE_FILES})

target_link_libraries( imageHashTesting ${OpenCV_LIBS} )

