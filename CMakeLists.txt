cmake_minimum_required(VERSION 3.5)
project(imageHashTesting)

set(CMAKE_CXX_STANDARD 11)



################################
# Testing
################################
# This adds another subdirectory, which has 'project(gtest)'.
add_subdirectory(googletest)

enable_testing()

# Include the gtest library. gtest_SOURCE_DIR is available due to
    # 'project(gtest)' above.
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
message(STATUS "here ${gtest_SOURCE_DIR}/include ")


include_directories(c_src/src)

SET(TARGET_H
        c_src/src/img_hash/AverageHash.h
        c_src/src/img_hash/FragmentHash.h
        c_src/src/Keypoint.h
        c_src/src/ShapeAndPositionInvariantImage.h
        c_src/src/Triangle.h
        )

set(SOURCE_FILES
        c_src/src/img_hash/img_hash_opencv_module/average_hash.cpp
        c_src/src/img_hash/img_hash_opencv_module/block_mean_hash.cpp
        c_src/src/img_hash/img_hash_opencv_module/color_moment_hash.cpp
        c_src/src/img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp
        c_src/src/img_hash/img_hash_opencv_module/phash.cpp
        c_src/src/main.cc
        c_src/src/mainImageProcessingFunctions.cpp)

set( TEST_FILES
        c_src/test/hashTests.cpp)

find_package( OpenCV REQUIRED )

add_executable(imageHashTesting ${SOURCE_FILES} ${TARGET_H})
add_executable(test1 ${TEST_FILES})

target_link_libraries( imageHashTesting ${OpenCV_LIBS} )


# Options. Turn on with 'cmake -Dmyvarname=ON'.


set(CMAKE_CXX_FLAGS "-g -Wall")

