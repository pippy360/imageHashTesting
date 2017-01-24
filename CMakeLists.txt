cmake_minimum_required(VERSION 3.5)
project(imageHashTesting)

set(CMAKE_CXX_STANDARD 11)

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
option(test "Build all tests." ON) # Makes boolean 'test' available.


set(CMAKE_CXX_FLAGS "-g -Wall")


################################
# Testing
################################
if (test)
    # This adds another subdirectory, which has 'project(gtest)'.
    add_subdirectory(googletest)

    enable_testing()

    # Include the gtest library. gtest_SOURCE_DIR is available due to
    # 'project(gtest)' above.
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    ##############
    # Unit Tests
    ##############
    add_executable(runUnitTests test_project1.cpp)

    # Standard linking to gtest stuff.
    target_link_libraries(runUnitTests gtest gtest_main)

    # Extra linking for the project.
    target_link_libraries(runUnitTests project1_lib)

    # This is so you can do 'make test' to see all your tests run, instead of
    # manually running the executable runUnitTests to see those specific tests.
    add_test(NAME that-test-I-made COMMAND runUnitTests)

    # You can also omit NAME and COMMAND. The second argument could be some other
    # test executable.
    add_test(that-other-test-I-made runUnitTests)
endif()