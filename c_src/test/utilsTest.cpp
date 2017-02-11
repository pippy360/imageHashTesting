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
#include "hiredis/hiredis.h"


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

TEST(utils, readKeypointsJsonFile){
//    string filename = "../c_src/test/resources/keypoints.json";
//    vector<Keypoint> output = readKeypointsFromJsonFile(filename);
//    vector<Triangle> ret = buildTrianglesFromKeypoints(output, 150, 300);
//
//    for(auto kp : output)
//    {
//        cout << "out: " << kp.toString() << endl;
//    }
}

string prettyPrintTriangle(Triangle tri)
{
    string ret = "";
    for (auto kp: tri.toKeypoints())
    {
        ret += kp.toString() + ", ";
    }
    return ret;
}

TEST(utils, keypointsToTriangles1){

//    vector<Keypoint> inputKeypoints;
//    inputKeypoints.push_back(Keypoint(0,0));
//    inputKeypoints.push_back(Keypoint(1,1));
//    inputKeypoints.push_back(Keypoint(2,2));
//    vector<Triangle> ret = buildTrianglesFromKeypoints(inputKeypoints, 1);
//    for (auto tri: ret)
//    {
//        cout << prettyPrintTriangle(tri) << endl;
//    }

}

TEST(utils, keypointsToTriangles2){
//    vector<Keypoint> inputKeypoints;
//    inputKeypoints.push_back(Keypoint(0,0));
//    inputKeypoints.push_back(Keypoint(1,1));
//    inputKeypoints.push_back(Keypoint(1.1,-.01));
//    inputKeypoints.push_back(Keypoint(-.01,1.1));
//    vector<Triangle> ret = buildTrianglesFromKeypoints(inputKeypoints, 1);
//    for (auto tri: ret)
//    {
//        cout << prettyPrintTriangle(tri) << endl;
//    }
}

TEST(utils, keypointsToTriangles3){
//    string filename = "../inputImages/img1/keypoints2.txt";
//    vector<Keypoint> output = readKeypointsFromJsonFile(filename);
//    vector<Triangle> ret = buildTrianglesFromKeypoints(output, 150, 300);
//    for (auto tri: ret)
//    {
//        cout << prettyPrintTriangle(tri) << endl;
//    }
}

TEST(utils, convertingToRedisEntryJson){
//    string imageName = "img1";
//    Keypoint one(100, 200);
//    Keypoint two(200, 300);
//    Keypoint three(400, 500);
//    Triangle tri(one, two, three);
//    cout << "This is what the generated json looks like: " << convertToRedisEntryJson(imageName, tri) << endl;
}

TEST(utils, convertingFromRedisEntryJson){
//     string redisEntry = "{"
//         "\"imageName\" : \"img1\","
//         "\"triangle\" : ["
//             "{\"x\" : 200, \"y\" : 300},"
//             "{\"x\" : 400, \"y\" : 500},"
//             "{\"x\" : 600, \"y\" : 700}"
//         "]"
//     "}";
//    auto tri = getTriangleFromRedisEntry(redisEntry);
//    cout << "ImageName: " << getImageNameFromRedisEntry(redisEntry) << endl;
//    cout << "Triangle: " << tri.toString() << endl;
}

TEST(utils, fullRedisEntryJsonIntigrationTest){
//     string redisEntry = "{"
//         "\"imageName\" : \"img1\","
//         "\"triangle\" : ["
//             "{\"x\" : 200, \"y\" : 300},"
//             "{\"x\" : 400, \"y\" : 500},"
//             "{\"x\" : 600, \"y\" : 700}"
//         "]"
//     "}";
//    auto tri = getTriangleFromRedisEntry(redisEntry);
//    string imageName = getImageNameFromRedisEntry(redisEntry);
//    cout << "Full test: " << convertToRedisEntryJson(imageName, tri) << endl;
}

TEST(utils, testTheTriangleDrawing){
    Keypoint one(100, 100);
    Keypoint two(200, 100);
    Keypoint three(200, 200);
    Triangle tri(one, two, three);
    vector<Triangle> tris;
    tris.push_back(tri);
    auto img = cv::imread("../c_src/test/resources/inputMatchingImages/Moderat-Bad-Kingdom-10/img1.jpg");
    drawSingleTriangleOntoImage(tri, img);
}




