#include "gtest/gtest.h"

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

    //load the image
    //apply a big transformation to it, resize the image if you have to
    //create a getKeyPointsFunction you can call from the c++ side

    double rotation = 0;
    double scale = 1;
    Mat inputImage = cv::imread("./input/lennaWithGreenDots.jpg");
    for (int j = 0; j < 4; j++){
        for (int i = 0; i<360; i+= 1){
            Mat transformationMartix;
            Size newImageSize;
            tie(transformationMartix, newImageSize) = calcTransformationMatrix(inputImage.size(), rotation+i, scale*(j+1));
            cout << "Size: " << newImageSize << endl;
            cout << "The output mat: " << endl;
            cout << Mat(transformationMartix) << endl;

            Mat outputImage(newImageSize.height, newImageSize.width, CV_8UC3, Scalar(0,0,0));
            warpAffine(inputImage, outputImage, formatTransformationMat2(transformationMartix), outputImage.size());
            imshow("output", outputImage);
            waitKey(1);
        }
    }
    waitKey();
//    //Then apply it
//    //Then get the keypoints for both images
//    //Then calc the transformation matrix and project both keypoints to both...
//    //Then calc all the stats...

}

TEST(accuracyTest, basic) {
    runTheTest();

}
