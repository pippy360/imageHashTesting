#include "gtest/gtest.h"

#include <boost/bimap.hpp>

#include "opencv2/opencv.hpp"
#include "utils/utils.hpp"
#include <unordered_map>

using namespace cv;
using namespace std;

Mat formatTransformationMat2(const Mat transformation_matrix)
{
    cv::Mat m = cv::Mat::ones(2, 3, CV_64F);
    m.at<double>(0, 0) = transformation_matrix.at<double>(0, 0);
    m.at<double>(0, 1) = transformation_matrix.at<double>(0, 1);
    m.at<double>(0, 2) = transformation_matrix.at<double>(0, 2);
    m.at<double>(1, 0) = transformation_matrix.at<double>(1, 0);
    m.at<double>(1, 1) = transformation_matrix.at<double>(1, 1);
    m.at<double>(1, 2) = transformation_matrix.at<double>(1, 2);
    return m;
}

void runTheTest()
{

//    //load the image
//    //apply a big transformation to it, resize the image if you have to
//    //create a getKeyPointsFunction you can call from the c++ side
//
//    double rotation = 0;
//    double scale = 1;
//    Mat inputImage = cv::imread("./input/lennaWithGreenDots.jpg");
//    for (int j = 0; j < 4; j++){
//        for (int i = 0; i<360; i+= 1){
//            Mat transformationMartix;
//            Size newImageSize;
//            tie(transformationMartix, newImageSize) = calcTransformationMatrix(inputImage.size(), rotation+i, scale*(j+1));
//            cout << "Size: " << newImageSize << endl;
//            cout << "The output mat: " << endl;
//            cout << Mat(transformationMartix) << endl;
//
//            Mat outputImage(newImageSize.height, newImageSize.width, CV_8UC3, Scalar(0,0,0));
//            warpAffine(inputImage, outputImage, formatTransformationMat2(transformationMartix), outputImage.size());
//            imshow("output", outputImage);
//            waitKey(1);
//        }
//    }
//    waitKey();
////    //Then apply it
////    //Then get the keypoints for both images
////    //Then calc the transformation matrix and project both keypoints to both...
////    //Then calc all the stats...

}

TEST(accuracyTest, basic) {
//    runTheTest();

}


TEST(utilsTest, getTheKeypointsTest) {
//    Mat inputImage = cv::imread("./input/rick1.jpg");
//    auto keypoints = getKeypoints(inputImage);
//    drawKeypoints(keypoints, inputImage);
//    cv::imshow("here...", inputImage);
//    cv::waitKey();
//    cout << "Number of keypoints: " << keypoints.size() << endl;
}


TEST(utilsTest, fullKeypointTest) {
//    Mat inputImage = cv::imread("./input/rick1.jpg");
//    auto keypointsForImageOne = getKeypoints(inputImage);
//    convertKeypointsVectorToMat
}

TEST(utilsTest, testingTheConvertingOfKeypoints) {
//    Mat inputImage = cv::imread("./input/rick1.jpg");
//    auto keypointsForImageOne = getKeypoints(inputImage);
//    Mat res = convertKeypointsVectorToMat(keypointsForImageOne);
//    //Mat res = cv::Mat::zeros(1,1, 1);
//    cout << "the resultant matrix" << endl;
//    cout << res << endl;
//    applyTransformationMatrixToKeypointVector(keypointsForImageOne, );
}

typedef std::unordered_map<Keypoint, Keypoint> MatchingKeypointMap;

MatchingKeypointMap getMatchingKeypointsTwoWayMap(vector<Keypoint> image1Keypoints, vector<Keypoint> image2Keypoints, cv::Mat transformationMatFromImage1To2)
{
    MatchingKeypointMap result;
    vector<Keypoint> oneToTwo = applyTransformationMatrixToKeypointVector(image1Keypoints, transformationMatFromImage1To2);

    double threshold = 2.0;
    for (auto keypointFromImage2 : image2Keypoints)
    {
        //check the dist
        for (unsigned int i = 0; i < oneToTwo.size(); i++)
        {
            if (getKeypointDistance(keypointFromImage2, oneToTwo[i]) < threshold)
            {
                auto keyPointFromImage1 = image1Keypoints[i];
                result.insert({keyPointFromImage1, keypointFromImage2});
            }
        }
    }

    return result;
}

typedef std::unordered_map<Triangle, Triangle> MatchingTriangleMap;

tuple<vector<Keypoint>, vector<Keypoint>> splitKeypointMap(MatchingKeypointMap map){
    vector<Keypoint> kp1;
    vector<Keypoint> kp2;

    for (auto entry: map)
    {
        kp1.push_back(entry.first);
        kp2.push_back(entry.second);
    }
    return tuple<vector<Keypoint>, vector<Keypoint>>(kp1, kp2);
}

Triangle convertTriangleUsingMap(Triangle triangle, MatchingKeypointMap oneToTwo) {
    vector<Keypoint> result;
    for (auto kp: triangle.toKeypoints())
    {
        result.push_back(oneToTwo[kp]);
    }
    return result;
}

MatchingTriangleMap buildMatchingTriMap(vector<Triangle> tris1, vector<Triangle> tris2, MatchingKeypointMap unorderedMap) {
    MatchingTriangleMap result;
    for (auto tri1: tris1)
    {
        for (auto tri2: tris2)
        {
            Triangle tri1Convert = convertTriangleUsingMap(tri1, unorderedMap);
            if (tri1Convert == tri2)
            {
                result.insert({tri1, tri2});
                break;
            }
        }
    }

    return result;
}

MatchingTriangleMap getMatchingTriangleTwoWayMap(MatchingKeypointMap oneToTwo) {

    vector<Keypoint> image1Kp;
    vector<Keypoint> image2Kp;
    tie(image1Kp, image2Kp) = splitKeypointMap(oneToTwo);

    auto tris1 = buildTrianglesFromKeypoints(image1Kp);
    auto tris2 = buildTrianglesFromKeypoints(image2Kp);

    return buildMatchingTriMap(tris1, tris2, oneToTwo);
}

unsigned long xorshf962(void) {          //period 2^96-1
    unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return z;
}


void dumpMathcingKeypointTestingInfoToJson(unsigned int count, unsigned int totalCount, unsigned int cout,
                                           MatchingKeypointMap map, unsigned int imagesCount, unsigned int image1Count,
                                           unsigned int image2Count, unsigned int trianglesTotalCount,
                                           unsigned int image2TrianglesTotalCount)
{
    //dump it!!!


}

TEST(utilsTest, testingTheConvertingOfKeypoints2)
{
    double rotation = 45;
    double scale = 2;
    Mat inputImage = cv::imread("./input/lennaWithGreenDots.jpg");
    Mat transformationMartix;
    Size newImageSize;
    tie(transformationMartix, newImageSize) = calcTransformationMatrix(inputImage.size(), rotation, scale);

    Mat outputImage(newImageSize.height, newImageSize.width, CV_8UC3, Scalar(0,0,0));
    warpAffine(inputImage, outputImage, formatTransformationMat2(transformationMartix), outputImage.size());

    auto keypointsImage1 = getKeypoints(inputImage);
    auto keypointsImage2 = getKeypoints(outputImage);

    vector<Keypoint> oneToTwo = applyTransformationMatrixToKeypointVector(keypointsImage1, transformationMartix);
    vector<Keypoint> twoToOne = applyTransformationMatrixToKeypointVector(keypointsImage2, transformationMartix.inv());

    drawKeypoints(keypointsImage1, inputImage);
    drawKeypoints(twoToOne, inputImage, cv::Scalar(0,255,0));
    drawKeypoints(keypointsImage2, outputImage);
    drawKeypoints(oneToTwo, outputImage, cv::Scalar(0,255,0));
    auto tempMap = getMatchingKeypointsTwoWayMap(keypointsImage1, keypointsImage2, transformationMartix);

    cout << "Number of matching keypints:   " << tempMap.size() << endl;
    cout << "Number of keypoints in image1: " << keypointsImage1.size() << " image2: " << keypointsImage2.size() << endl;
    cout << "average:   " << ((keypointsImage1.size() + keypointsImage2.size())/2) << endl;
    cout << "%average:  " << 100.0*(float)(tempMap.size())/(float)((keypointsImage1.size() + keypointsImage2.size())/2) << "%" << endl;

    for (auto entry : tempMap)
    {
        drawSingleKeypoint(entry.first, inputImage, cv::Scalar(255,0,0));
        drawSingleKeypoint(entry.second, outputImage, cv::Scalar(255,0,0));
    }

    cv::imwrite("image1_keypoints.jpg", inputImage);
    cv::imwrite("image2_keypoints.jpg", outputImage);


    MatchingTriangleMap tempTriangleMap = getMatchingTriangleTwoWayMap(tempMap);
    auto allTrisImage1 = buildTrianglesFromKeypoints(keypointsImage1);
    auto allTrisImage2 = buildTrianglesFromKeypoints(keypointsImage2);

    vector<Keypoint> image1Kp;
    vector<Keypoint> image2Kp;
    tie(image1Kp, image2Kp) = splitKeypointMap(tempMap);

    auto tris1 = buildTrianglesFromKeypoints(image1Kp);
    auto tris2 = buildTrianglesFromKeypoints(image2Kp);

    cout << "Number of matching Triangles:   " << tempTriangleMap.size() << endl;
    cout << "Number of Triangles made of matching points in image1: " << tris1.size() << " image2: " << tris2.size() << endl;
    cout << "average:  " << ((tris1.size() + tris2.size())/2) << endl;
    cout << "%average: " << 100.0*(float)(tempTriangleMap.size())/(float)((tris1.size() + tris2.size())/2) << "%" << endl;
    cout << "Number of Triangles in image1: " << allTrisImage1.size() << " image2: " << allTrisImage2.size() << endl;
    cout << "average:  " << ((allTrisImage1.size() + allTrisImage2.size())/2) << endl;
    cout << "%average: " << 100.0*(float)(tempTriangleMap.size())/(float)((allTrisImage1.size() + allTrisImage2.size())/2) << "%" << endl;

    for (auto entry: tempTriangleMap)
    {
        bool setColour = true;
        int r = (int) xorshf962();
        int g = (int) xorshf962();
        int b = (int) xorshf962();
        cv::Scalar colour(b,g,r);
        drawSingleTriangleOntoImage(entry.first, inputImage, setColour, colour);
        drawSingleTriangleOntoImage(entry.second, outputImage, setColour, colour);
    }

    //keypoints
    unsigned int matchingKeypointsCount = tempMap.size();
    unsigned int image1KeypointsTotalCount = keypointsImage1.size();
    unsigned int image2KeypointsTotalCout = keypointsImage2.size();
    auto matchingKeypoints = tempMap;

    //triangles
    unsigned int matchingTrianglesInBothImagesCount = tempTriangleMap.size();
    unsigned int trianglesMadeOfMatchingKeypointsInImage1Count = tris1.size();
    unsigned int trianglesMadeOfMatchingKeypointsInImage2Count = tris2.size();
    unsigned int image1TrianglesTotalCount = allTrisImage1.size();
    unsigned int image2TrianglesTotalCount = allTrisImage2.size();
    auto matchingTriangles = tempTriangleMap;

    dumpMathcingKeypointTestingInfoToJson(matchingKeypointsCount, image1KeypointsTotalCount, image2KeypointsTotalCout,
                                          matchingKeypoints, matchingTrianglesInBothImagesCount, trianglesMadeOfMatchingKeypointsInImage1Count,
                                          trianglesMadeOfMatchingKeypointsInImage2Count, image1TrianglesTotalCount, image2TrianglesTotalCount );

    cv::imwrite("image1_triangles.jpg", inputImage);
    cv::imwrite("image2_triangles.jpg", outputImage);
//    cv::waitKey();
}




































