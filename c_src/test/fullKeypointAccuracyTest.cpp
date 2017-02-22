#include "gtest/gtest.h"

#include <boost/bimap.hpp>

#include "opencv2/opencv.hpp"
#include "utils/utils.hpp"

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

typedef boost::bimap< Keypoint, Keypoint > MatchingKeypointMap;

MatchingKeypointMap getMatchingKeypointsTwoWayMap(vector<Keypoint> image1Keypoints, vector<Keypoint> image2Keypoints, cv::Mat transformationMatFromImage1To2)
{
    MatchingKeypointMap result;
    vector<Keypoint> oneToTwo = applyTransformationMatrixToKeypointVector(image1Keypoints, transformationMatFromImage1To2);

    double threshold = 2.0;
    for (auto kp : image2Keypoints)
    {
        //check the dist
        for (unsigned int i = 0; i < oneToTwo.size(); i++)
        {
            if (getKeypointDistance(kp, oneToTwo[i]) < threshold)
            {
                auto kp2 = image1Keypoints[i];
                result.insert({kp2, kp});
            }
        }
    }

    return result;
}

TEST(utilsTest, testingTheConvertingOfKeypoints2) {
    double rotation = 45;
    double scale = 1;
    Mat inputImage = cv::imread("./input/rick1.jpg");
    Mat transformationMartix;
    Size newImageSize;
    tie(transformationMartix, newImageSize) = calcTransformationMatrix(inputImage.size(), rotation, scale);
//    cout << "Size: " << newImageSize << endl;
//    cout << "The output mat: " << endl;
//    cout << Mat(transformationMartix) << endl;

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
    cout << "Number of matching keypints:   " << tempMap.left.size() << endl;
    cout << "Number of keypoints in image1: " << keypointsImage1.size() << " image2: " << keypointsImage2.size() << endl;
    cout << "average:   " << ((keypointsImage1.size() + keypointsImage2.size())/2) << endl;
    cout << "%average:  " << 100.0*(float)(tempMap.left.size())/(float)((keypointsImage1.size() + keypointsImage2.size())/2) << "%" << endl;
    for (auto entry : tempMap.left)
    {
        drawSingleKeypoint(entry.first, inputImage, cv::Scalar(255,0,0));
        drawSingleKeypoint(entry.second, outputImage, cv::Scalar(255,0,0));
    }

    cv::imshow("image1.jpg", inputImage);
    cv::imshow("image2.jpg", outputImage);
    cv::waitKey();
}




































