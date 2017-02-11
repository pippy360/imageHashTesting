#ifndef mainImageProcessingFunctions_cpp
#define mainImageProcessingFunctions_cpp


#include <vector>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iomanip>      // std::setw
#include <math.h>       /* pow, atan2 */

#include "img_hash/FragmentHash.h"
#include "ShapeAndPositionInvariantImage.h"
#include "Triangle.h"
//#include "img_hash/img_hash_opencv_module/average_hash.cpp"
//#include "img_hash/img_hash_opencv_module/block_mean_hash.cpp"
//#include "img_hash/img_hash_opencv_module/color_moment_hash.cpp"
//#include "img_hash/img_hash_opencv_module/marr_hildreth_hash.cpp"
//#include "img_hash/img_hash_opencv_module/phash.cpp"

#define NUM_OF_ROTATIONS 3
#define HASH_SIZE 8
#define TARGET_TRIANGLE_SCALE 10 //the fragments are scaled by this value 
#define FRAGMENT_WIDTH TARGET_TRIANGLE_SCALE*HASH_SIZE
#define FRAGMENT_HEIGHT TARGET_TRIANGLE_SCALE*(HASH_SIZE+1)
#define PI 3.14159265

const std::vector<Keypoint> getTargetTriangle(int scalex=FRAGMENT_WIDTH, int scaley=FRAGMENT_HEIGHT)
{
    std::vector<Keypoint> v;
	//multiply all points by TARGET_TRIANGLE_SCALE
    v.push_back(Keypoint(0,0));
    v.push_back(Keypoint(.5*scalex,1*scaley));
    v.push_back(Keypoint(1*scalex,0));
    return v;
}

namespace cv
{

std::string getShapeStr(std::vector<Keypoint> shape)
{
    auto k1 = shape[0];
    auto k2 = shape[1];
    auto k3 = shape[2];
    std::ostringstream stringStream;
    stringStream << "[" << "[" << k1.x << ", " << k1.y << "], " << "[" << k2.x << ", " << k2.y << "], " << "[" << k3.x << ", " << k3.y << "]]";
    std::string copyOfStr = stringStream.str();
    return copyOfStr;
}

std::vector<bool> dHashSlowWithoutResizeOrGrayscale(Mat resized_input_mat)
{
	std::vector<bool> output;
	unsigned int width_j = resized_input_mat.cols;
	unsigned int height_i = resized_input_mat.rows;
	for (unsigned int i = 0; i < height_i; i++)
	{
		for (unsigned int j = 0; j < width_j; j++)// "width_j-1" skip the last run
		{
			if(j == width_j -1 ){
				continue;
			}
			unsigned char left = resized_input_mat.at<unsigned char>(i, j, 0);
			unsigned char right = resized_input_mat.at<unsigned char>(i, j+1, 0);
			output.push_back( right > left );
		}
	}
	return output;
}


std::vector<bool> dHashSlowWithResizeAndGrayscale(const Mat input_mat)
{	
	int height = HASH_SIZE;
	int width = HASH_SIZE+1;
	Mat resized_input_mat;
	resize(input_mat, resized_input_mat, cvSize(width, height));

	Mat gray_image;
	cvtColor(resized_input_mat, gray_image, CV_BGR2GRAY);

	return dHashSlowWithoutResizeOrGrayscale(resized_input_mat);
}

Matx33d calcTransformationMatrix(const std::vector<Keypoint>& inputTriangle, const std::vector<Keypoint>& targetTriangle)
{
	/*
	 * ######CODE BY ROSCA#######
	 */
	Keypoint target_pt1 = targetTriangle[1];
	Keypoint target_pt2 = targetTriangle[2];
	cv::Matx33d targetPoints(  target_pt1.x, target_pt2.x, 0.0,
							   target_pt1.y, target_pt2.y, 0.0,
							   0.0, 0.0, 1.0 );

	Keypoint pt2 = Keypoint(inputTriangle[1].x - inputTriangle[0].x, inputTriangle[1].y - inputTriangle[0].y);
	Keypoint pt3 = Keypoint(inputTriangle[2].x - inputTriangle[0].x, inputTriangle[2].y - inputTriangle[0].y);

	cv::Matx33d inputPoints(  pt2.x, pt3.x, 0.0,
							  pt2.y, pt3.y, 0.0,
							  0.0, 0.0, 1.0 );

	cv::Matx33d transpose_m(  1.0, 0.0, -inputTriangle[0].x,
							  0.0, 1.0, -inputTriangle[0].y,
							  0.0, 0.0, 1.0 );
	
	// std::cout << "targetPoints:\n" << targetPoints << std::endl;
	// std::cout << "inputPoints.inv(): \n" << inputPoints.inv() << std::endl;
	return  targetPoints * inputPoints.inv() * transpose_m;
}

bool isToTheLeftOf(Keypoint pt1, Keypoint pt2)
{
    return ((0 - pt1.x)*(pt2.y - pt1.y) - (0 - pt1.y)*(pt2.x - pt1.x)) > 0;
}

const std::vector<Keypoint> prepShapeForCalcOfTransformationMatrix(const std::vector<Keypoint>& inputTriangle, const std::vector<Keypoint>& targetTriangle)
{
	/*
	
	tri = fragmentImageShape
	x_trans = tri[0][0]
	y_trans = tri[0][1]
	pt1 = (tri[1][0] - x_trans, tri[1][1] - y_trans)
	pt2 = (tri[2][0] - x_trans, tri[2][1] - y_trans)

	import math
	t1 = math.atan2(pt1[1], pt1[0])
	t1 %= 2*math.pi
	#print t1
	t2 = math.atan2(pt2[1], pt2[0])
	t2 %= 2*math.pi
	#print t2
	if t1 < t2:
		return np.matrix(pt1).T, np.matrix(pt2).T, -x_trans, -y_trans
	else:
		return np.matrix(pt2).T, np.matrix(pt1).T, -x_trans, -y_trans
	*/


	auto pt1 = inputTriangle[0];
	auto pt2 = inputTriangle[1];
	auto pt3 = inputTriangle[2];
	auto pt2_t = Keypoint(pt2.x-pt1.x, pt2.y-pt1.y);
	auto pt3_t = Keypoint(pt3.x-pt1.x, pt3.y-pt1.y);

	auto ret = std::vector<Keypoint>();
	ret.push_back(pt1);
    if( isToTheLeftOf(pt2_t, pt3_t) ){
		ret.push_back(pt2);
		ret.push_back(pt3);
	} else {
		ret.push_back(pt3);
		ret.push_back(pt2);
	}
	return ret;			
}

//@shift: this is used to get every rotation of the triangle we need (3, one for each edge of the triangle)
const std::vector<Keypoint> prepShapeForCalcOfTransformationMatrixWithShift(const std::vector<Keypoint> shape, const std::vector<Keypoint>& targetTriangle, int shift)
{
	auto shape_cpy = shape;
	shift %= shape_cpy.size();
	std::rotate(shape_cpy.begin(),shape_cpy.begin()+shift,shape_cpy.end());
	//printf("this is the shift: %d\n", shift);
	return prepShapeForCalcOfTransformationMatrix(shape_cpy, targetTriangle);
}

Mat formatTransformationMat(const Matx33d transformation_matrix)
{
	cv::Mat m = cv::Mat::ones(2, 3, CV_64F);
	m.at<double>(0, 0) = transformation_matrix(0, 0);
	m.at<double>(0, 1) = transformation_matrix(0, 1);
	m.at<double>(0, 2) = transformation_matrix(0, 2);
	m.at<double>(1, 0) = transformation_matrix(1, 0);
	m.at<double>(1, 1) = transformation_matrix(1, 1);
	m.at<double>(1, 2) = transformation_matrix(1, 2);
	return m;
}

Mat applyTransformationMatrixToImage(Mat inputImage, const Matx33d transformation_matrix, int outputTriangleSizeX, int outputTriangleSizeY)
{
	Mat m = formatTransformationMat(transformation_matrix);

    //Mat outputImage(FRAGMENT_HEIGHT, FRAGMENT_WIDTH, CV_8UC3, Scalar(0,0,0));
    // Mat outputImage(32, 32, CV_8UC3, Scalar(0,0,0));
    // Mat outputImage(150*.83, 150, CV_8UC3, Scalar(0,0,0));
	//Mat outputImage(200*.83, 200, CV_8UC3, Scalar(0,0,0));
	Mat outputImage(outputTriangleSizeY, outputTriangleSizeX, CV_8UC3, Scalar(0,0,0));
	// Mat outputImage(400*.83, 400, CV_8UC3, Scalar(0,0,0));
	warpAffine(inputImage, outputImage, m, outputImage.size());
	//DEBUG
	// imshow("fragmentAfterTransformation", outputImage);
	// waitKey();
	//DEBUG
	return outputImage;
}

void drawLines(Mat input_img, vector<Keypoint> shape){
	cv::Scalar scl = Scalar(0, 0, 255);
	cv::line(input_img, Point2f(shape[2].x, shape[2].y), Point2f(shape[0].x, shape[0].y), scl);
	cv::line(input_img, Point2f(shape[0].x, shape[0].y), Point2f(shape[1].x, shape[1].y), scl);
	cv::line(input_img, Point2f(shape[1].x, shape[1].y), Point2f(shape[2].x, shape[2].y), scl);
}

Matx33d calcTransformationMatrixWithShapePreperation(const std::vector<Keypoint>& inputTriangle, const std::vector<Keypoint>& targetTriangle, int shift)
{
	auto newShape = prepShapeForCalcOfTransformationMatrixWithShift(inputTriangle, targetTriangle, shift);

	//DEBUG
	// auto k1 = newShape[0];
	// auto k2 = newShape[1];
	// auto k3 = newShape[2];
    // std::cout << "the shape after shift [" << "[" << k1.x << ", " << k1.y << "], " << "[" << k2.x << ", " << k2.y << "], " << "[" << k3.x << ", " << k3.y << "]]" << std::endl;
	//DEBUG

	return calcTransformationMatrix(newShape, targetTriangle);
}

std::vector<ShapeAndPositionInvariantImage> normaliseScaleAndRotationForSingleFrag(ShapeAndPositionInvariantImage& fragment)
{
	auto shape = fragment.getShape();
	auto ret = std::vector<ShapeAndPositionInvariantImage>();
	int outputTriangleSizeX = 60*.83;
	int outputTriangleSizeY = 60;
	for (unsigned int i = 0; i < NUM_OF_ROTATIONS; i++)
	{	
		auto transformationMatrix = calcTransformationMatrixWithShapePreperation(shape, getTargetTriangle(outputTriangleSizeX, outputTriangleSizeY), i);
		// std::cout << "transformationMatrix:\n" << transformationMatrix << std::endl;
		auto input_img = fragment.getImageData();
		//DEBUG
		//drawLines(input_img, shape);
		//DEBUG
		auto newImageData = applyTransformationMatrixToImage(input_img, transformationMatrix, outputTriangleSizeX, outputTriangleSizeY);
		auto t = ShapeAndPositionInvariantImage(fragment.getImageName(), newImageData, shape, fragment.getImageFullPath());
		//DEBUG
// 		auto hash_b = dHashSlowWithResizeAndGrayscale(newImageData);
// 		auto hash = FragmentHash(hash_b, shape);
// 		// printf("hash: %s shape: %s\n", convertHashToString(hash).c_str(), getShapeStr(hash.getShape()).c_str());
// 		//imshow("fragmentAfterTransformation", newImageData);
// 		// std::string str = convertHashToString(hash);
// 		// imwrite("../output/"+ str + ".jpg", newImageData);

// 		cv::imwrite("../inputImages/"+fragment.getImageName()+"/outputFragments/"+convertHashToString(hash)+".jpg", newImageData);
// //		printf("%s\n", ("../inputImages/"+fragment.getImageName()+"/outputFragments/"+convertHashToString(hash)+".jpg").c_str() );

		// waitKey();
		//DEBUG
		ret.push_back(t);
	}
	
	return ret;
}

ShapeAndPositionInvariantImage getFragment(const ShapeAndPositionInvariantImage& input_image, const Triangle& tri)
{
	//TODO: cut out the fragment
	return ShapeAndPositionInvariantImage(input_image.getImageName(), input_image.getImageData(), tri.toKeypoints(), "");
}

template<typename T> std::vector<T> getHashesForFragments(std::vector<ShapeAndPositionInvariantImage>& normalisedFragments, const string STRING_DEBUG_FRAGMENT_DUMP_FOLDER_PATH="", const string DEBUG_STRING_APPEND="")
{
	auto ret = std::vector<T>();
	for (unsigned int i = 0; i < normalisedFragments.size(); i++)
	{
		auto frag = normalisedFragments[i];
//	for (auto frag : normalisedFragments)
//	{
		auto calculatedHash = T(frag);
		ret.push_back(calculatedHash);
		//DEBUG
//		if(STRING_DEBUG_FRAGMENT_DUMP_FOLDER_PATH != ""){
//			cv::imwrite(STRING_DEBUG_FRAGMENT_DUMP_FOLDER_PATH+"/"+to_string(i)+""+calculatedHash.toString()+"_" + DEBUG_STRING_APPEND + ".jpg", frag.getImageData());
//		}
		//cv::waitKey();
		//\DEBUG
	}
	return ret;
}

template<typename T> std::vector<T> getHashesForTriangle(ShapeAndPositionInvariantImage& input_image, const Triangle& tri, const string STRING_DEBUG_FRAGMENT_DUMP_FOLDER_PATH="", const string DEBUG_STRING_APPEND="")
{
	auto fragment = getFragment(input_image, tri);
	auto normalisedFragments = normaliseScaleAndRotationForSingleFrag(fragment);
	auto hashes = getHashesForFragments<T>(normalisedFragments, STRING_DEBUG_FRAGMENT_DUMP_FOLDER_PATH, DEBUG_STRING_APPEND);

	return hashes;
}

Triangle resizeTri(Triangle tri, double mult){
	vector<Keypoint> newKpts;
	for (auto kp: tri.toKeypoints())
	{
		newKpts.push_back( Keypoint(kp.x*mult, kp.y*mult) );
	}
	return Triangle(newKpts);
}

vector<Triangle> resizeAllTris(vector<Triangle> inputTriangles, double mult){
	auto ret = vector<Triangle>();
	for (auto tri: inputTriangles){
		ret.push_back(resizeTri(tri, mult));
	}
	return ret;
}

template<typename T> vector<pair<Triangle, T>> getAllTheHashesForImage(ShapeAndPositionInvariantImage inputImage, std::vector<Triangle> triangles, const string STRING_DEBUG_FRAGMENT_DUMP_FOLDER_PATH="", const string DEBUG_STRING_APPEND="")
{
	//resize it
//	Mat resizedImage;
	double mult = 1.0;
//	cv::resize(inputImage.getImageData(), resizedImage, Size(0,0), mult, mult);

	ShapeAndPositionInvariantImage inputImage2("", inputImage.getImageData(), std::vector<Keypoint>(), "");
	triangles = resizeAllTris(triangles, mult);
	//\resize it
	vector<pair<Triangle, T>> ret(triangles.size()*NUM_OF_ROTATIONS);
    #pragma omp parallel for
    for (unsigned int i = 0; i < triangles.size(); i++) {
        auto tri = triangles[i];
		auto hashes = getHashesForTriangle<T>(inputImage2, tri, STRING_DEBUG_FRAGMENT_DUMP_FOLDER_PATH, DEBUG_STRING_APPEND);

        for (unsigned int j = 0; j < 3; j++)
        {
            ret[(i*3)+j] = pair<Triangle, T>(tri, hashes[j]);
		}
	}
	return ret;
}


}//namespace cv

#endif//mainImageProcessingFunctions_cpp
