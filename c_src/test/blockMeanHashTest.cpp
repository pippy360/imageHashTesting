#include "gtest/gtest.h"
#include "img_hash/BlockMeanHash.h"

#include <stdio.h>
#include "opencv2/opencv.hpp"


using namespace hashes;

TEST(BlockMeanHash, basicSerialiseTest){
    BlockMeanHash testHash("184f785970e970e2");
    EXPECT_EQ("184f785970e970e2", testHash.toString());
}

TEST(BlockMeanHash, basicImageTest){
    string img1FullPath = "./c_src/test/resources/dist_1_7ca4a6eee2a32515-7ca4a6ee62a32515_1.jpg";
    auto img1 = cv::imread(img1FullPath);
    // cv::imshow(img1FullPath, img1);
	ShapeAndPositionInvariantImage s_img1("img1", img1, vector<Keypoint>(), img1FullPath);
    string img2FullPath = "./c_src/test/resources/dist_1_7ca4a6eee2a32515-7ca4a6ee62a32515_2.jpg";
    auto img2 = cv::imread(img2FullPath);
    // cv::imshow(img2FullPath, img2);
	ShapeAndPositionInvariantImage s_img2("img2", img2, vector<Keypoint>(), img2FullPath);

    // BlockMeanHash testHash("7ca4a6eee2a32515");
    BlockMeanHash testHash1(s_img1);
    BlockMeanHash testHash2(s_img2);
    EXPECT_GT(3, testHash1.getHammingDistance(testHash2));
    EXPECT_EQ("c01fc03fc31fc31f", testHash1.toString());
    EXPECT_EQ("801fc01fc31fc31f", testHash2.toString());
}



