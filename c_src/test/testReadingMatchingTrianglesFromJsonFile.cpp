#include "gtest/gtest.h"
#include "img_hash/PerceptualHash.h"



#include <stdio.h>
#include "opencv2/opencv.hpp"

#include "utils/utils.hpp"



TEST(readingMatchingTriangles, basicTest){
    auto matchingTris = readMatchingTrianglesFromJsonFile("c_src/test/resources/matchingTriangles.json");

}



