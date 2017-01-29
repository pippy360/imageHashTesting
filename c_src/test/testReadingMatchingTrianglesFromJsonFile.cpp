#ifdef _MSC_VER
#include <boost/config/compiler/visualc.hpp>
#endif
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include "utils/utils.hpp"
#include "img_hash/PerceptualHash.h"
#include <stdio.h>

#include "opencv2/opencv.hpp"

TEST(readingMatchingTriangles, basicTest){
    auto matchingTris = readMatchingTrianglesFromJsonFile("c_src/test/resources/matchingTriangles.json");


}



