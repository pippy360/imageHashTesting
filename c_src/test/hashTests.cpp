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
    string img1FullPath = "./c_src/test/resources/dist_1_7ca4a6eee2a32515-7ca4a6ee62a32515_1.jpg";
    auto img1 = cv::imread(img1FullPath);
    // cv::imshow(img1FullPath, img1);
	ShapeAndPositionInvariantImage s_img1("img1", img1, vector<Keypoint>(), img1FullPath);
    string img2FullPath = "./c_src/test/resources/dist_1_7ca4a6eee2a32515-7ca4a6ee62a32515_2.jpg";
    auto img2 = cv::imread(img2FullPath);
    // cv::imshow(img2FullPath, img2);
	ShapeAndPositionInvariantImage s_img2("img2", img2, vector<Keypoint>(), img2FullPath);

    // AverageHash testHash("7ca4a6eee2a32515");
    AverageHash testHash1(s_img1);
    AverageHash testHash2(s_img2);
    EXPECT_GT(5, testHash1.getHammingDistance(testHash2));
    EXPECT_EQ("8f9397b7b7307357", testHash1.toString());
    EXPECT_EQ("8f9395b7b7347317", testHash2.toString());
}



