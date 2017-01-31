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

using namespace std;

TEST(readingMatchingTriangles, basicTest){
    auto matchingTris = readMatchingTrianglesFromJsonFile("c_src/test/resources/matchingTriangles.json");

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
    vector<hashes::PerceptualHash> temp;
    temp.push_back(hashes::PerceptualHash("4b49e171be8e212a"));
    dumpHashesToJsonFile<hashes::PerceptualHash>("c_src/test/resources/jsonHashFile_testOutputFile.json", temp);
}
