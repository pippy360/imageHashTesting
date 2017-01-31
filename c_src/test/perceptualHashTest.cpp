#include "gtest/gtest.h"
#include "img_hash/PerceptualHash.h"

#include <stdio.h>
#include "opencv2/opencv.hpp"


using namespace hashes;

TEST(PerceptualHash, basicSerialiseTest){
    PerceptualHash testHash("7ca4a6eee2a32515");
    EXPECT_EQ("7ca4a6eee2a32515", testHash.toString());
}

TEST(PerceptualHash, basicImageTest){
    string img1FullPath = "./c_src/test/resources/dist_1_7ca4a6eee2a32515-7ca4a6ee62a32515_1.jpg";
    auto img1 = cv::imread(img1FullPath);
    // cv::imshow(img1FullPath, img1);
	ShapeAndPositionInvariantImage s_img1("img1", img1, vector<Keypoint>(), img1FullPath);
    string img2FullPath = "./c_src/test/resources/dist_1_7ca4a6eee2a32515-7ca4a6ee62a32515_2.jpg";
    auto img2 = cv::imread(img2FullPath);
    // cv::imshow(img2FullPath, img2);
	ShapeAndPositionInvariantImage s_img2("img2", img2, vector<Keypoint>(), img2FullPath);

    // PerceptualHash testHash("7ca4a6eee2a32515");
    PerceptualHash testHash1(s_img1);
    PerceptualHash testHash2(s_img2);
    cout << "The hamming distance is: " << testHash1.getHammingDistance(testHash2) << endl;
    EXPECT_GT(3, testHash1.getHammingDistance(testHash2));
    EXPECT_EQ("2c3f116199a05b22", testHash1.toString());
    EXPECT_EQ("2e3f116199a05ba2", testHash2.toString());
}


TEST(PerceptualHash, accuracyTest){

    // string img1FullPath = "./c_src/test/resources/";//TODO: load in the moderat one
    // auto img1 = cv::imread(img1FullPath);
	// ShapeAndPositionInvariantImage s_img1("img1", img1, vector<Keypoint>(), img1FullPath);

    // string jsonHashesFileFullPath = "./c_src/test/resources/hashes.json";
    // readJsonHashFile();

    // cout << "The hamming distance is: " << testHash1.getHammingDistance(testHash2) << endl;
    // EXPECT_GT(3, testHash1.getHammingDistance(testHash2));
    // EXPECT_EQ("2c3f116199a05b22", testHash1.toString());
    // EXPECT_EQ("2e3f116199a05ba2", testHash2.toString());
}

