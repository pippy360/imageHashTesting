#include "gtest/gtest.h"
#include "img_hash/AverageHash.h"

#include <stdio.h>
#include "opencv2/opencv.hpp"


using namespace hashes;

TEST(AverageHash, basicSerialiseTest){
    AverageHash testHash("7ca4a6eee2a32515");
    EXPECT_EQ("7ca4a6eee2a32515", testHash.toString());
}

TEST(AverageHash, basicImageTest){
    AverageHash testHash("7ca4a6eee2a32515");
    string img1FullPath = "./resources/dist_1_7ca4a6eee2a32515-7ca4a6ee62a32515_1.jpg";
    auto img1 = cv::imread(img1FullPath);
	ShapeAndPositionInvariantImage("img1", img1, vector<Keypoint>(), img1FullPath);
    string img2FullPath = "./resources/dist_1_7ca4a6eee2a32515-7ca4a6ee62a32515_2.jpg";
    auto img2 = cv::imread(img2FullPath);
	ShapeAndPositionInvariantImage("img2", img2, vector<Keypoint>(), img2FullPath);
    

    EXPECT_EQ("7ca4a6eee2a32515", testHash.toString());
}

