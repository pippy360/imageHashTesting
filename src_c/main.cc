#include <vector>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <string>
#include <regex>

#include "FragmentHash.h"
#include "ShapeAndPositionInvariantImage.h"
#include "Triangle.h"
#include "mainImageProcessingFunctions.cpp"
#include <iostream>
#include "hiredis/hiredis.h"

using namespace std;

void toTheLeftOfTest()
{

    //FIXME: THIS IS ACTUALLY BROKEN!!!
    //basic
    auto k1 = Keypoint(1,1);
    auto k2 = Keypoint(1,0);
    bool v = false;
    v = cv::isToTheLeftOf(k1, k2);
    if(v==true){
        printf("it worked!!\n");
    }else{
        printf("####ERROR: IT FAILED !!#######\n");
    }
    //TODO: more tests
}

void prepShapeForCalcOfTransformationMatrixTest()
{
    //basic
    auto k1 = Keypoint(0,0);
    auto k2 = Keypoint(1,0);
    auto k3 = Keypoint(1,1);
    auto v = std::vector<Keypoint>();
    v.push_back(k1);
    v.push_back(k2);
    v.push_back(k3);
    
    auto res = cv::prepShapeForCalcOfTransformationMatrix(v, getTargetTriangle());
    printf("{");
    for(auto t: res)
    {
        printf(" point: (%lf, %lf), ", t.x, t.y);
    }
    printf("}");    
    printf("\n");
}

void shiftTest()
{
    //basic
    auto k1 = Keypoint(0,0);
    auto k2 = Keypoint(1,0);
    auto k3 = Keypoint(1,1);
    auto v = std::vector<Keypoint>();
    v.push_back(k1);
    v.push_back(k2);
    v.push_back(k3);
    
    auto res = cv::prepShapeForCalcOfTransformationMatrixWithShift(v, getTargetTriangle(), 0);
    printf("{");
    for(auto t: res)
    {
        printf(" point: (%lf, %lf), ", t.x, t.y);
    }
    printf("}");
    printf("\n");

    res = cv::prepShapeForCalcOfTransformationMatrixWithShift(v, getTargetTriangle(), 1);
    printf("{");
    for(auto t: res)
    {
        printf(" point: (%lf, %lf), ", t.x, t.y);
    }
    printf("}");
    printf("\n");

    res = cv::prepShapeForCalcOfTransformationMatrixWithShift(v, getTargetTriangle(), 2);
    printf("{");
    for(auto t: res)
    {
        printf(" point: (%lf, %lf), ", t.x, t.y);
    }
    printf("}");
    printf("\n");

    //TODO: test shift > vec.size
}

void calcTransformationMatrixTest(){
    //basic
    auto k1 = Keypoint(0,0);
    auto k2 = Keypoint(1,0);
    auto k3 = Keypoint(1,1);
    auto v = std::vector<Keypoint>();
    v.push_back(k1);
    v.push_back(k2);
    v.push_back(k3);
    auto m = cv::calcTransformationMatrix(v, getTargetTriangle());
    //std::cout << "M = "<< std::endl << " "  << m << std::endl << std::endl;
}

void normaliseScaleAndRotationForSingleFragTest(cv::Mat &img){
	//cv::imshow("here", img);
	cv::waitKey();
    auto k1 = Keypoint(0,0);
    auto k2 = Keypoint(100,0);
    auto k3 = Keypoint(100,100);
    auto v = std::vector<Keypoint>();
    v.push_back(k1);
    v.push_back(k2);
    v.push_back(k3);
    auto m = cv::calcTransformationMatrix(v, getTargetTriangle());
    //std::cout << "working so far M = "<< std::endl << " "  << m << std::endl << std::endl;    
    auto im = ShapeAndPositionInvariantImage("d", img, v, "something");
    cv::normaliseScaleAndRotationForSingleFrag(im);
}

void printTheDHash(std::vector<bool> hash){
    printf("\n");
    for(int i = 0; i < hash.size(); i++){
        if (i%8 == 0)
            printf("\n");
        printf("%s, ", (hash[i] == true)? "True":"False");
    }

    for(int i = 0; i < hash.size(); i++){
        printf("%s", (hash[i] == true)? "1":"0");
    }
    printf("\n");
}

cv::Mat prepImage(cv::Mat img)
{
    cv::Mat gray_image;
	cv::cvtColor(img, gray_image, CV_BGR2GRAY);
	
	int height = HASH_SIZE;
	int width = HASH_SIZE+1;

	cv::Mat resized_input_mat;
	resize(gray_image, resized_input_mat, cvSize(width, height));
	std::vector<bool> output;

	unsigned char temp[] = {
		124, 105, 130, 121, 129, 124, 255, 254, 255, 109, 100, 158, 171, 107, 129, 255, 253, 255, 111, 114, 103, 165, 105, 164, 255, 254, 255, 115, 81, 98, 132, 83, 177, 255, 254, 255, 107, 80, 102, 110, 106, 207, 255, 254, 255, 96, 62, 70, 131, 115, 158, 255, 255, 255, 137, 96, 128, 181, 150, 149, 255, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
	};

	int width_j = resized_input_mat.cols;
	int height_i = resized_input_mat.rows;
	int count = 0;

	for (int i = 0; i < height_i; i++)
	{
		for (int j = 0; j < width_j; j++)// "width_j-1" skip the last run
		{
			//printf("%d: %d: %d: %d, ", temp[(i*width_j) + j], (i*width_j) + j, i ,j);
			resized_input_mat.at<unsigned char>(i, j, 0) = temp[(i*width_j) + j];
		}
	}

	printf("...\n, ");
    return resized_input_mat;
}

void dHashSlowTest(){
    cv::Mat img = cv::imread("./small_lenna1.jpg");
    cv::Mat fixed_img = prepImage(img);
    auto hash = cv::dHashSlowWithoutResizeOrGrayscale(fixed_img);
    bool tempBool[] = {
        0,1,0,1,0,1,0,1,0,1,1,0,1,1,
        0,1,1,0,1,0,1,1,0,1,0,1,1,0,
        1,1,0,1,0,1,1,0,1,1,0,1,0,1,
        1,0,1,1,0,0,0,1,1,0,0,1,0,1,
        0,0,0,0,0,0,0,0
        };
    int size = sizeof(tempBool) / sizeof(bool);
    printTheDHash(hash);
    if(size != hash.size()){
        printf("######ERROR: SIZE DOESN'T MATCH \n");
    }

    for (int i = 0; i < hash.size(); i++)
    {
        if(hash[i] != tempBool[i]){
            printf("######ERROR: HASH DOESN'T MATCH \n");            
        }else{
            //printf("Match\n");                        
        }
    }
    printf("done checking hashes\n");
}

void speedTest(){

    cv::Mat img = cv::imread("./small_lenna1.jpg");
    for(int i=0; i<1000;i++){
        normaliseScaleAndRotationForSingleFragTest(img);
    }
}

/*
std::vector<Keypoint>& getShapeFromImage(cv::Mat img)
{
	auto shape = img.size();
    return 
}
*/

const std::string readTheName(std::ifstream *file)
{
    std::string str;
    std::getline(*file, str);
    // printf("file name is: %s\n", str.c_str());
    return str;
}

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

const std::vector<Triangle> readTheTriangles(std::ifstream *file)
{
    std::vector<Triangle> triangles;
    std::string str;
    while (true)
    {
        if(!std::getline(*file, str)){
            break;
        }
        
        double x1 = atof(str.c_str());
        std::getline(*file, str);
        double y1 = atof(str.c_str());
        Keypoint k1(x1, y1);

        std::getline(*file, str);
        double x2 = atof(str.c_str());
        std::getline(*file, str);
        double y2 = atof(str.c_str());
        Keypoint k2(x2, y2);

        std::getline(*file, str);
        double x3 = atof(str.c_str());
        std::getline(*file, str);
        double y3 = atof(str.c_str());
        Keypoint k3(x3, y3);

        Triangle t(k1, k2, k3);
        triangles.push_back(t);
    }
    return triangles;
}


void testHashConversion()
{
    std::vector<bool> hash;
    hash.push_back(false);
    hash.push_back(true);
    hash.push_back(false);
    hash.push_back(false);

    hash.push_back(false);
    hash.push_back(false);
    hash.push_back(false);
    hash.push_back(false);

    std::string str = cv::convertHashToString(FragmentHash(hash));
    std::cout << str << std::endl;
}

std::vector<Triangle> getTheTris(const char *trisPath){
    std::ifstream file(trisPath);
    //std::string filename = readTheName(&file);
    auto tris = readTheTriangles(&file);
    return tris;
}

cv::Matx33d getATransformationMatrix(int width, int height){

    std::ifstream file("output.txt");
    std::string filename = readTheName(&file);
    auto tris = readTheTriangles(&file);
    auto tri = tris[0];
    
    return cv::calcTransformationMatrixWithShapePreperation(tri.toKeypoints(), getTargetTriangle(width, height), 0);
}

cv::Matx33d getATransformationMatrix2(Triangle tri, int width, int height){
    return cv::calcTransformationMatrixWithShapePreperation(tri.toKeypoints(), getTargetTriangle(width, height), 0);
}

cv::Mat getScaleMat(int image_x, int image_y)
{
	cv::Mat m = cv::Mat::ones(2, 3, CV_64F);
	m.at<double>(0, 0) = ((float)(8+1))/ ((float)image_x);
	m.at<double>(0, 1) = 0;
	m.at<double>(0, 2) = 0;
	m.at<double>(1, 0) = 0;
	m.at<double>(1, 1) = ((float)(8))/(float)image_y;
	m.at<double>(1, 2) = 0;
	return m;
}

FragmentHash testHashingForResize()
{
    // cv::Mat img = cv::imread("./small_lenna1.jpg");
    cv::Mat img = cv::imread("../input/rick1.jpg");

    cv::Mat outputImage(200, 200, CV_8UC3, cv::Scalar(0,0,0));
    auto transformation_matrix = getATransformationMatrix(200, 200);
    // auto out2 = cv::applyTransformationMatrixToImage(img, transformationMatrix);

    cv::Mat m = formatTransformationMat(transformation_matrix);
    cv::warpAffine(img, outputImage, m, outputImage.size());

    auto hash = FragmentHash(cv::dHashSlowWithResizeAndGrayscale(outputImage));
    std::cout << cv::convertHashToString(hash) << std::endl;

	cv::imshow("here", outputImage);
	// cv::waitKey();
    return hash;    
}

FragmentHash testHashingForResize2()
{
    // cv::Mat img = cv::imread("./small_lenna1.jpg");
    cv::Mat img = cv::imread("../input/rick1.jpg");

    cv::Mat outputImage(400, 400, CV_8UC3, cv::Scalar(0,0,0));
    auto transformation_matrix = getATransformationMatrix(400, 400);
    // auto out2 = cv::applyTransformationMatrixToImage(img, transformationMatrix);

    cv::Mat m = formatTransformationMat(transformation_matrix);
    cv::warpAffine(img, outputImage, m, outputImage.size());

    auto hash = FragmentHash(cv::dHashSlowWithResizeAndGrayscale(outputImage));
    std::cout << cv::convertHashToString(hash) << std::endl;

	cv::imshow("here", outputImage);
	// cv::waitKey();
    return hash;    
}

FragmentHash testHashingForResize3()
{
    // cv::Mat img = cv::imread("./small_lenna1.jpg");
    cv::Mat img = cv::imread("../input/rick1.jpg");

    int mult = 1;
    int val = (8*mult);
    cv::Mat outputImage((val), (val)+1, CV_8UC3, cv::Scalar(0,0,0));
    auto transformation_matrix = getATransformationMatrix((val)+1, (val));
    // auto out2 = cv::applyTransformationMatrixToImage(img, transformationMatrix);

    cv::Mat m = formatTransformationMat(transformation_matrix);
    //cv::warpAffine(img, outputImage, m, outputImage.size(), cv::INTER_LINEAR);
    cv::warpAffine(img, outputImage, m, outputImage.size());

    cv::Mat outputImage2((val*10), (val*10)+1, CV_8UC3, cv::Scalar(0,0,0));
    transformation_matrix = getATransformationMatrix((val*10)+1, (val*10));
    m = formatTransformationMat(transformation_matrix);
    cv::warpAffine(img, outputImage2, m, outputImage2.size());
    cv::Mat resized_input_mat;    
    cv::resize(outputImage2, resized_input_mat, cvSize(val+1, val));
    

	// cv::imshow("here", outputImage);
	// cv::imshow("here2", resized_input_mat);
    auto hash = FragmentHash(cv::dHashSlowWithResizeAndGrayscale(outputImage));
    std::cout << cv::convertHashToString(hash) << std::endl;
    auto hash2 = FragmentHash(cv::dHashSlowWithResizeAndGrayscale(resized_input_mat));
    cv::imwrite("./hash1.jpg", outputImage);
    cv::imwrite("./hash2.jpg", resized_input_mat);
    std::cout << cv::convertHashToString(hash2) << std::endl;
    int dist = cv::getHashDistance(hash, hash2);
    printf("dist diff : %d\n", dist);
	// cv::waitKey();
    return hash;
}

FragmentHash testHashingForResize4()
{
    // cv::Mat img = cv::imread("./small_lenna1.jpg");
    cv::Mat img = cv::imread("../input/rick1.jpg");

    cv::Mat outputImage(500, 500, CV_8UC3, cv::Scalar(0,0,0));
    auto transformation_matrix = getATransformationMatrix(500, 500);
    // auto out2 = cv::applyTransformationMatrixToImage(img, transformationMatrix);

    cv::Mat m = formatTransformationMat(transformation_matrix);
    cv::warpAffine(img, outputImage, m, outputImage.size());

    cv::Mat resized_input_mat;
    int height = 8;
	int width = 8+1;
    
	resize(outputImage, resized_input_mat, cvSize(width, height));
    auto hash = FragmentHash(cv::dHashSlowWithResizeAndGrayscale(resized_input_mat));
    std::cout << cv::convertHashToString(hash) << std::endl;

	cv::imshow("here", outputImage);
	// cv::waitKey();
    return hash;
}

FragmentHash testHashingForResize5()
{
    // cv::Mat img = cv::imread("./small_lenna1.jpg");
    cv::Mat img = cv::imread("../input/rick1.jpg");

    cv::Mat outputImage(500, 500, CV_8UC3, cv::Scalar(0,0,0));
    auto transformation_matrix = getATransformationMatrix(500, 500);
    // auto out2 = cv::applyTransformationMatrixToImage(img, transformationMatrix);

    cv::Mat m = formatTransformationMat(transformation_matrix);
    cv::warpAffine(img, outputImage, m, outputImage.size());

    cv::Mat resized_input_mat;
    int height = 8;
	int width = 8+1;
    
    int mult = 1;
    cv::Mat outputImage2((8*mult), (8*mult)+1, CV_8UC3, cv::Scalar(0,0,0));
    m = getScaleMat(500.0/mult, 500.0/mult);
    std::cout << "Mat: " << m << std::endl;
    cv::warpAffine(outputImage, outputImage2, m, outputImage2.size());
    auto hash = FragmentHash(cv::dHashSlowWithResizeAndGrayscale(outputImage2));
    cv::imwrite("./hash3_1.jpg", outputImage2);
	// resize(outputImage, resized_input_mat, cvSize(width, height));
    // auto hash = FragmentHash(cv::dHashSlowWithResizeAndGrayscale(resized_input_mat));
    // cv::imwrite("./hash3_2.jpg", resized_input_mat);
    // std::cout << cv::convertHashToString(hash) << std::endl;
    
	cv::imshow("here", outputImage2);
	//cv::waitKey();
    return hash;
}

FragmentHash testSpeedWithoutFix_s(const cv::Mat img, Triangle tri)
{
    int width_outputImage_x = 200;
    int width_outputImage_y = 200;
    cv::Mat outputImage(width_outputImage_y, width_outputImage_x, CV_8UC3, cv::Scalar(0,0,0));    
    auto transformation_matrix = getATransformationMatrix2(tri, width_outputImage_x, width_outputImage_y);
    cv::Mat m = formatTransformationMat(transformation_matrix);
    cv::warpAffine(img, outputImage, m, outputImage.size());

    //now do the resize
    cv::Mat resized_input_mat;
    int height = 8;
	int width = 8+1;
	resize(outputImage, resized_input_mat, cvSize(width, height));


    cv::imwrite("./hash_from_org_test.jpg", resized_input_mat);


    return FragmentHash(cv::dHashSlowWithResizeAndGrayscale(resized_input_mat));
}

// std::vector<FragmentHash> testSpeedWithoutFix()
// {
//     // cv::Mat img = cv::imread("../input/rick1.jpg");
//     // std::vector<FragmentHash> hashes;
//     // auto tris = getTheTris();
//     // for(int i = 0; i < 3000; i++)
//     // {
//     //     auto tri = tris[i];
//     //     auto hash = testSpeedWithoutFix_s(img, tri);
//     //     hashes.push_back(hash);
//     // }
//     // return hashes;
// }

FragmentHash testSpeedWithoutFix2_s(const cv::Mat img, Triangle tri)
{
    int width_outputImage_x = 8+1;
    int width_outputImage_y = 8;
    cv::Mat outputImage(width_outputImage_y, width_outputImage_x, CV_8UC3, cv::Scalar(0,0,0));    
    auto transformation_matrix = getATransformationMatrix2(tri, width_outputImage_x, width_outputImage_y);
    cv::Mat m = formatTransformationMat(transformation_matrix);
    cv::warpAffine(img, outputImage, m, outputImage.size());

    //now do the resize
    cv::Mat resized_input_mat;
    int height = 8;
	int width = 8+1;
	resize(outputImage, resized_input_mat, cvSize(width, height));


    cv::imwrite("./hash_from_org_test.jpg", resized_input_mat);


    return FragmentHash(cv::dHashSlowWithResizeAndGrayscale(resized_input_mat));
}

std::vector<FragmentHash> findNearestneighbour_slow(FragmentHash targetHash, std::vector<FragmentHash> hashList, int threshold=3)
{
    std::vector<FragmentHash> ret;
    for(auto tempHash : hashList)
    {
        int dist = cv::getHashDistance(targetHash, tempHash);
        if (dist <= threshold)
        {
            ret.push_back(tempHash);
        }
    }
    return ret;
}

std::vector<FragmentHash> getTheHashesFromRedisReply(redisReply *reply)
{
    std::vector<FragmentHash> ret;
    if (reply->type == REDIS_REPLY_ARRAY) {
        int j;
        for (j = 0; j < reply->elements; j++) {
            auto hash = cv::hex_str_to_hash(reply->element[j]->str);
            ret.push_back(hash);
        }
    }
    return ret;
}


// std::vector<FragmentHash> testSpeedWithoutFix2()
// {
//     // cv::Mat img = cv::imread("../input/rick1.jpg");
//     // std::vector<FragmentHash> hashes;
//     // auto tris = getTheTris();
//     // for(int i = 0; i < 3000; i++)
//     // {
//     //     auto tri = tris[i];
//     //     auto hash = testSpeedWithoutFix2_s(img, tri);
//     //     hashes.push_back(hash);
//     // }
//     // return hashes;
// }


std::vector<FragmentHash> loadHashes(std::string filename)
{
    std::vector<FragmentHash> ret;
    std::ifstream file(filename);
    std::string str = ""; 
    while (true)
    {
        if(!std::getline(file, str)){
            break;
        }

        auto fraghash = cv::hex_str_to_hash(str);
        ret.push_back(fraghash);
        //std::cout << str << " should match: " << cv::convertHashToString(fraghash) << std::endl;
    }
    return ret;
}

vector<string> loadImageNames(string filename)
{
    vector<string> filenames;

    std::ifstream file(filename);
    std::string str = ""; 
    while (true)
    {
        if(!std::getline(file, str)){
            break;
        }
        ret.push_back(str);
    }

    return filenames;
}

vector<string> loadExcludeList(string filename)
{
    vector<string> filenames;

    std::ifstream file(filename);
    std::string str = ""; 
    while (true)
    {
        if(!std::getline(file, str)){
            break;
        }
        ret.push_back(str);
    }

    return filenames;
}


bool isInExcludeList(string name, vector<string> excludeList, string imageName){
    if(name == imageName){
        return true;
    }
    for (auto e: excludeList){
        if(name == e){
            return true;
        }   
    }
    return false;
}


int main(int argc, char* argv[])
{

    unsigned int j;
    redisContext *c;
    redisReply *reply;
    const char *hostname = "127.0.0.1";
    int port = 6379;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    //auto vals = testSpeedWithoutFix2();
    if (argc == 1){
        printf("error: no args!!!\n");
        return -1;
    }

    
    std::string imageName = (argc > 2)? argv[2]: "img1";
    std::string imageFullPath =  "../inputImages/"+ imageName + "/" + imageName + ".jpg";
    std::string imagePoints =  "../inputImages/"+ imageName + "/keypoints.txt";


    if (argc > 1 && strcmp(argv[1], "add") == 0){
        printf("add detected\n");
        cv::Mat img = cv::imread(imageFullPath);
        auto tris = getTheTris(imagePoints.c_str());
        auto img_s = ShapeAndPositionInvariantImage("", img, std::vector<Keypoint>(), "");
        auto vals = cv::getAllTheHashesForImage_debug(img_s, tris, tris.size());
        for(FragmentHash v: vals){
            auto hash = cv::convertHashToString(v);
            //std::cout << hash.c_str() << std::endl;
            reply = (redisReply *) redisCommand(c,"SET %s %s", hash.c_str(), imageFullPath.c_str());
            printf("SET: %s\n", reply->str);
        }
    } else if (argc > 1 && strcmp(argv[1], "test") == 0){
        printf("running test\n");
        cv::Mat img1 = cv::imread("../input/img1.jpg");
        cv::Mat img2 = cv::imread("../input/img2.jpg");
        auto tris1 = getTheTris("../src/tri1.txt");
        auto tris2 = getTheTris("../src/tri2.txt");
        auto img1_s = ShapeAndPositionInvariantImage("", img1, std::vector<Keypoint>(), "");
        auto img2_s = ShapeAndPositionInvariantImage("", img2, std::vector<Keypoint>(), "");
        auto vals1 = cv::getAllTheHashesForImage_debug(img1_s, tris1, tris1.size());
        auto vals2 = cv::getAllTheHashesForImage_debug(img2_s, tris2, tris2.size());

        // reply = (redisReply *) redisCommand(c,"Keys *");
        // std::vector<FragmentHash> hashList = getTheHashesFromRedisReply(reply);
        // for (auto t_hash: hashList)
        // {
        //     printf("hash: %s\n", cv::convertHashToString(t_hash).c_str());
        // }

        std::vector<FragmentHash> hashList  = vals2;
        
        int idx = 0;
        for(int i = 0; idx < vals1.size(); i++, idx = i + (6*(i/3))){

            auto v1 = vals1[idx];
            auto shape1 = v1.getShape();
            auto hash1 = cv::convertHashToString(v1);
            cv::drawLines(img1, shape1);

            auto vals2_ret = findNearestneighbour_slow(v1, hashList);
            if (vals2_ret.size() > 0)
            {
                for(int j = 0; j < vals2_ret.size(); j++){
                    auto v2 = vals2_ret[j];
                    auto whatV2shouldHaveBeen = vals2[i];
                    auto shape2 = v2.getShape();
                    auto hash2 = cv::convertHashToString(v2);
                    // cv::drawLines(img2, shape2);
                    cv::Mat hash1img = cv::imread("../output/"+hash1+".jpg");
                    cv::Mat hash2img = cv::imread("../output/"+hash2+".jpg");

                    cv::imshow("img1", hash1img);
                    cv::imshow("img2", hash2img);
                    cv::waitKey();

                    std::cout << "Matches: " << vals2_ret.size() <<  "\t distance: " << cv::getHashDistance(v1, v2) << "\t from: " << hash1.c_str() << " : " << hash2.c_str() << std::endl;
                }
            }else{
                printf("no match\n");
            }
        }        
    } else if (argc > 1 && strcmp(argv[1], "compare") == 0){
        printf("running compare.....\n");
        cv::Mat img1 = cv::imread(imageFullPath);
        auto tris1 = getTheTris(imagePoints.c_str());

        std::string imageName2 = (argc > 3)? argv[3]: "img2";
        std::string imageFullPath2 =  "../inputImages/"+ imageName2 + "/" + imageName2 + ".jpg";
        std::string imagePoints2 =  "../inputImages/"+ imageName2 + "/keypoints.txt";
        cv::Mat img2 = cv::imread(imageFullPath2);
        auto tris2 = getTheTris(imagePoints2.c_str());

        auto img1_s = ShapeAndPositionInvariantImage("", img1, std::vector<Keypoint>(), "");
        auto img2_s = ShapeAndPositionInvariantImage("", img2, std::vector<Keypoint>(), "");
        auto vals1 = cv::getAllTheHashesForImage_debug(img1_s, tris1, tris1.size());
        auto vals2 = cv::getAllTheHashesForImage_debug(img2_s, tris2, tris2.size());

        //findNearestneighbour_slow();
        int idx = 0;
        std::vector<FragmentHash> hashList  = vals2;        
        for(int i = 0; idx < vals1.size(); i++, idx = i + (6*(i/3))){

            auto v1 = vals1[idx];
            auto shape1 = v1.getShape();
            auto hash1 = cv::convertHashToString(v1);
            cv::drawLines(img1, shape1);

            auto vals2_ret = findNearestneighbour_slow(v1, hashList);
            if (vals2_ret.size() > 0)
            {
                for(int j = 0; j < vals2_ret.size(); j++){
                    auto v2 = vals2_ret[j];
                    auto whatV2shouldHaveBeen = vals2[i];
                    auto shape2 = v2.getShape();
                    auto hash2 = cv::convertHashToString(v2);
                    // cv::drawLines(img2, shape2);
                    cv::Mat hash1img = cv::imread("../output/"+hash1+".jpg");
                    cv::Mat hash2img = cv::imread("../output/"+hash2+".jpg");

                    cv::imshow("img1", hash1img);
                    cv::imshow("img2", hash2img);
                    cv::waitKey();

                    std::cout << "Matches: " << vals2_ret.size() <<  "\t distance: " << cv::getHashDistance(v1, v2) << "\t from: " << hash1.c_str() << " : " << hash2.c_str() << std::endl;
                }
            }else{
                printf("no match\n");
            }
        }
    } else if (argc > 1 && strcmp(argv[1], "comp_hard") == 0){
        printf("running hard coded compare...\n");
        cv::Mat img1 = cv::imread("../input/img1.jpg");
        cv::Mat img2 = cv::imread("../input/img2.jpg");
        auto tris1 = getTheTris("../src/tri1.txt");
        auto tris2 = getTheTris("../src/tri2.txt");
        auto img1_s = ShapeAndPositionInvariantImage("", img1, std::vector<Keypoint>(), "");
        auto img2_s = ShapeAndPositionInvariantImage("", img2, std::vector<Keypoint>(), "");
        auto vals1 = cv::getAllTheHashesForImage_debug(img1_s, tris1, tris1.size());
        auto vals2 = cv::getAllTheHashesForImage_debug(img2_s, tris2, tris2.size());

        // reply = (redisReply *) redisCommand(c,"Keys *");
        // std::vector<FragmentHash> hashList = getTheHashesFromRedisReply(reply);
        // for (auto t_hash: hashList)
        // {
        //     printf("hash: %s\n", cv::convertHashToString(t_hash).c_str());
        // }

        std::vector<FragmentHash> hashList  = vals2;
        
        int idx = 0;
        for(int i = 0; idx < vals1.size(); i++, idx = i + (6*(i/3))){

            auto v1 = vals1[idx];
            auto shape1 = v1.getShape();
            auto hash1 = cv::convertHashToString(v1);
            cv::drawLines(img1, shape1);

            auto v2 = vals2[idx];
            auto shape2 = v2.getShape();
            auto hash2 = cv::convertHashToString(v2);
            cv::drawLines(img2, shape2);
            
            cv::Mat hash1img = cv::imread("../output/"+hash1+".jpg");
            cv::Mat hash2img = cv::imread("../output/"+hash2+".jpg");

            cv::imshow("img1", hash1img);
            cv::imshow("img2", hash2img);
            cv::waitKey();

            std::cout << "Distance: " << cv::getHashDistance(v1, v2) << "\t from: " << hash1.c_str() << " : " << hash2.c_str() << std::endl;
        }      
    } else if (argc > 1 && strcmp(argv[1], "lookup") == 0){
        printf("lookup detected\n");
        cv::Mat img = cv::imread(imageFullPath);
        auto tris = getTheTris(imagePoints.c_str());
        auto img_s = ShapeAndPositionInvariantImage("", img, std::vector<Keypoint>(), "");
        auto vals = cv::getAllTheHashesForImage_debug(img_s, tris, tris.size());
        int count_number_of_matches = 0;
        for(FragmentHash v: vals){
            auto hash = cv::convertHashToString(v);
            //std::cout << hash.c_str() << std::endl;
            reply = (redisReply *) redisCommand(c,"GET %s", hash.c_str());
            if (reply->str == NULL  || strcmp(reply->str, "(null)") == 0){

            }else{
                //printf("GET: %s\n", reply->str);            
                count_number_of_matches++;
            }
        }        
        printf("matched: %d number of times\n", count_number_of_matches);
    } else if (argc > 1 && strcmp(argv[1], "dump") == 0){

        cv::Mat img = cv::imread(imageFullPath);
        auto tris = getTheTris(imagePoints.c_str());
        auto img_s = ShapeAndPositionInvariantImage("", img, std::vector<Keypoint>(), "");
        auto vals = cv::getAllTheHashesForImage_debug(img_s, tris, tris.size());
        printf("{\"vals\": [");
        // for(FragmentHash v: vals)
        // {
        int end = vals.size();
        for(int i = 0; i< end; i++)
        {
            auto v = vals[i];
            printf("{ \"hash\": \"%s\", \"shape\": \"%s\"}", cv::convertHashToString(v).c_str(), cv::getShapeStr(v.getShape()).c_str());
            if (i != end-1)
            {
                printf(",");
            }
        }
        printf("]}");
        //also save all the hashes to a file
    } else if (argc > 1 && strcmp(argv[1], "dumpHashesToFile") == 0){
        
        cv::Mat img = cv::imread(imageFullPath);
        auto tris = getTheTris(imagePoints.c_str());
        auto img_s = ShapeAndPositionInvariantImage("", img, std::vector<Keypoint>(), "");
        auto vals = cv::getAllTheHashesForImage_debug(img_s, tris, tris.size());
        std::ofstream outputFile;
        outputFile.open("../inputImages/"+ imageName + "/hashes.txt", std::ios::out);
        // printf(("../inputImages/"+ imageName + "/hashes.txt\n").c_str());
        for (auto val: vals)
        {
            //std::cout << "the hash: " << cv::convertHashToString(val) << std::endl;
            outputFile << cv::convertHashToString(val) << std::endl; 
        }
        outputFile.close();

    } else if (argc > 1 && strcmp(argv[1], "printConflicts") == 0){
        printf("running printConflicts.....\n");

        auto hashes = loadHashes("../inputImages/"+ imageName + "/hashes.txt");

        //we still need to load the image names for non-conflicts
        auto imageNames = loadImageNames("../inputImages/imageNames.txt");
        auto excludeList = loadExcludeList("../inputImages/"+ imageName + "/excludeList.txt");
        for (auto name: imageNames)
        {
            if ( !isInExcludeList(name, excludeList, imageName) ){
                auto toCompareHashes = loadHashes("../inputImages/"+ name + "/hashes.txt");
                for (auto hash : hashes){
                    auto ret_vals = findNearestneighbour_slow(hash, toCompareHashes);
                    cout << "number of matches: " << ret_vals << endl;
                }
            } 
        }
        //use the called image!!
        //  just load the hashes
        //  for each NON conflict
        //      just load the hashes
        //      compare the hashes and count any matches

    }else{
        printf("arg didn't match anything...\n");
    }

	return 0;
}