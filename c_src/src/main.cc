#include <vector>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <string>
#include <regex>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "img_hash/AverageHash.h"
#include "img_hash/BlockMeanHash.h"
#include "img_hash/PerceptualHash.h"

//#include "img_hash/FragmentHash.h"
//#include "ShapeAndPositionInvariantImage.h"
#include "Triangle.h"
#include "mainImageProcessingFunctions.hpp"
#include <boost/program_options.hpp>
#include <iostream>


using namespace std;


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

std::vector<Triangle> getTheTris(const char *trisPath){
   std::ifstream file(trisPath);
   //std::string filename = readTheName(&file);
   auto tris = readTheTriangles(&file);
   return tris;
}

std::vector<Triangle> getTheTris_random(const char *trisPath, int numberOfSamples = 1000){
   std::ifstream file(trisPath);
   //std::string filename = readTheName(&file);
   auto tris = readTheTriangles(&file);
   std::vector<Triangle> ret;
   for (int i = 0; i<numberOfSamples; i++)
   {
       int ran = rand() % tris.size();
       ret.push_back(tris[ran]);
   }

   return ret;
}

ShapeAndPositionInvariantImage getLoadedImage(string imageFullPath){
    cv::Mat img = cv::imread(imageFullPath);
    return ShapeAndPositionInvariantImage("", img, std::vector<Keypoint>(), "");
}

void writeHashesToFile(string fullFilePath, vector<string> hashes)
{
    std::ofstream outputFile;
    outputFile.open(fullFilePath, std::ios::out);
    for (auto hash: hashes)
    {
        outputFile << hash << endl;
    }
}

template<typename T> void writeHashObjectsToFile(string fullFilePath, vector<T> hashes)
{
    vector<string> hashesToString;
    for (auto hash: hashes)
    {
        hashesToString.push_back(hash.toString());
    }
    writeHashesToFile(fullFilePath, hashesToString);
}

int main(int argc, char* argv[])
{
    if (argc == 1){
        printf("error: no args!!!\n");
        return -1;
    }

    std::string imageName = (argc > 2)? argv[2]: "img1";
    std::string imageFullPath =  "inputImages/"+ imageName + "/" + imageName + ".jpg";
    std::string imagePoints =  "inputImages/"+ imageName + "/keypoints.txt";

    auto triangles = getTheTris(imagePoints.c_str());
    auto loadedImage = getLoadedImage(imageFullPath);
    auto hashes = cv::getAllTheHashesForImage<hashes::PerceptualHash>(loadedImage, triangles);
    writeHashObjectsToFile<hashes::PerceptualHash>("inputImages/"+ imageName + "/hashes.txt", hashes);
}
