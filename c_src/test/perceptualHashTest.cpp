#include "gtest/gtest.h"
#include "img_hash/PerceptualHash.h"

#include <stdio.h>
#include <img_hash/PerceptualHash_Fast.h>
#include "opencv2/opencv.hpp"
#include "utils/utils.hpp"


using namespace hashes;

TEST(PerceptualHash, basicSerialiseTest){
//    PerceptualHash testHash("7ca4a6eee2a32515");
//    EXPECT_EQ("7ca4a6eee2a32515", testHash.toString());
}

TEST(PerceptualHash, basicImageTest){
//    string img1FullPath = "./c_src/test/resources/dist_1_7ca4a6eee2a32515-7ca4a6ee62a32515_1.jpg";
//    auto img1 = cv::imread(img1FullPath);
//    // cv::imshow(img1FullPath, img1);
//	ShapeAndPositionInvariantImage s_img1("img1", img1, vector<Keypoint>(), img1FullPath);
//    string img2FullPath = "./c_src/test/resources/dist_1_7ca4a6eee2a32515-7ca4a6ee62a32515_2.jpg";
//    auto img2 = cv::imread(img2FullPath);
//    // cv::imshow(img2FullPath, img2);
//	ShapeAndPositionInvariantImage s_img2("img2", img2, vector<Keypoint>(), img2FullPath);
//
//    // PerceptualHash testHash("7ca4a6eee2a32515");
//    PerceptualHash testHash1(s_img1);
//    PerceptualHash testHash2(s_img2);
//    cout << "The hamming distance is: " << testHash1.getHammingDistance(testHash2) << endl;
//    EXPECT_GT(3, testHash1.getHammingDistance(testHash2));
//    EXPECT_EQ("2c3f116199a05b22", testHash1.toString());
//    EXPECT_EQ("2e3f116199a05ba2", testHash2.toString());
}


TEST(PerceptualHash, accuracyTest){
//    auto matchingTris = readMatchingTrianglesFromJsonFile("c_src/test/resources/matchingTriangles.json");
//    auto loadedHashes = readJsonHashesFile<hashes::AverageHash>("c_src/test/resources/savedHashes.json");
//
//    string path = "c_src/test/resources/inputMatchingImages/Moderat-Bad-Kingdom-10/";
//    vector<Triangle> imageTris1;
//    vector<Triangle> imageTris2;
//    tie(imageTris2, imageTris1) = readMatchingTrianglesFromJsonFile(path+"matchingTriangles.json");
//    // auto loadedImage1 = getLoadedImage();
//    auto loadedImage2 = getLoadedImage(path+"img2.jpg");
//    cv::Mat gray_image;
//    cv::Mat img = cv::imread(path+"img1.jpg");
//    // cv::cvtColor( img, gray_image, CV_BGR2GRAY );
//    // auto loadedImage1 = ShapeAndPositionInvariantImage("", gray_image, std::vector<Keypoint>(), "");
//    auto loadedImage1 = ShapeAndPositionInvariantImage("", img, std::vector<Keypoint>(), "");
//
//    auto hashes1 = cv::getAllTheHashesForImage<hashes::PerceptualHash_Fast>(loadedImage1, imageTris1, path+"outputFragments", "1");
//
//    int totalDist = 0;
//    for (unsigned int i = 0; i < loadedHashes.size(); i++)
//    {
//        // cout << "hamming dist: " << loadedHashes[i].getHammingDistance(hashes1[i]) << endl;
//        totalDist += loadedHashes[i].getHammingDistance(hashes1[i]);
//    }
//    cout << "The total error/hamming distance: " << totalDist << " average error per hash: " << totalDist/loadedHashes.size() << endl;
}

