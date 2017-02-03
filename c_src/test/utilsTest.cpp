#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include "Triangle.h"
#include "gtest/gtest.h"
#include "utils/utils.hpp"
// #include "img_hash/PerceptualHash.h"
#include <stdio.h>


#include "opencv2/opencv.hpp"

using namespace std;

TEST(readingMatchingTriangles, basicTest){
    //auto matchingTris = readMatchingTrianglesFromJsonFile("c_src/test/resources/matchingTriangles.json");

    // for (auto tri: matchingTris)
    // {
    //     getAllTheHashesForImage();
    // }
}

TEST(utils, jsonParsing_readingInJsonHashesFile){
    //TODO: MAKE SURE BOTH READ AND WRITE TESTS USE DIFFERENT FILES
    //auto matchingTris = readMatchingTrianglesFromJsonFile("c_src/test/resources/matchingTriangles.json");
//    auto hashes = readJsonHashesFile<hashes::AverageHash>("c_src/test/resources/savedHashes.json");
//    for (auto hash: hashes) {
//        cout << hash.toString() << endl;
//    }
}

TEST(utils, jsonParsing_dumpHashesToJsonHashesFile){
    //load the hashes
    //dump them to the file
    //manually check or call the read test
    //cout << "success" << endl;
    // vector<hashes::PerceptualHash> temp;
    // temp.push_back(hashes::PerceptualHash("4b49e171be8e212a"));
    // dumpHashesToJsonFile<hashes::PerceptualHash>("c_src/test/resources/jsonHashFile_testOutputFile.json", temp);
}

string prettyPrintTriangle(Triangle tri)
{
    string ret = "";
    for (auto kp: tri.toKeypoints())
    {
        ret += kp.toString();
    }
    return ret;
} 

TEST(utils, keypointsToTriangles){
    vector<Keypoint> inputKeypoints;
    inputKeypoints.push_back(Keypoint(0,0));
    inputKeypoints.push_back(Keypoint(1,1));
    inputKeypoints.push_back(Keypoint(2,2));
    vector<Triangle> ret = buildTrianglesFromKeypoints(inputKeypoints, 1);
    for (auto tri: ret)
    {
        cout << prettyPrintTriangle(tri) << endl;
    }
}
