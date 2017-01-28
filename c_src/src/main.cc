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

std::vector<Triangle> getTheTris(const string trisPath){
   std::ifstream file(trisPath);
   //std::string filename = readTheName(&file);
   auto tris = readTheTriangles(&file);
   return tris;
}

std::vector<Triangle> getTheTris_random(string trisPath, int numberOfSamples = 1000){
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

template<typename T> void dumpHashes(string imageName, string imagePoints, string imageFullPath)
{
    auto triangles = getTheTris_random(imagePoints);
    auto loadedImage = getLoadedImage(imageFullPath);
    auto hashes = cv::getAllTheHashesForImage<T>(loadedImage, triangles, imageName);
    writeHashObjectsToFile<T>("inputImages/"+ imageName + "/hashes.txt", hashes);
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
        filenames.push_back(str);
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
        filenames.push_back(str);
    }

    return filenames;
}

template <typename T> std::vector<T> loadHashesFromFile(std::string filename)
{
    std::vector<T> ret;
    std::ifstream file(filename);
    std::string str = "";
    while (true)
    {
        if(!std::getline(file, str)){
            break;
        }

        T fraghash(str);
        ret.push_back(fraghash);
        //std::cout << str << " should match: " << cv::convertHashToString(fraghash) << std::endl;
    }
    return ret;
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


template <typename T> void printConflicts(string imageName, string imagePoints, string imageFullPath, int threshold = 3)
{
    const string hashesFileFullPath = "inputImages/"+ imageName + "/hashes.txt";
    const string excludeListFullPath = "inputImages/"+ imageName + "/excludeList.txt";
    auto triangles = getTheTris(imagePoints);
    auto loadedImage = getLoadedImage(imageFullPath);
    auto hashes = loadHashesFromFile<T>(hashesFileFullPath);
    cout << hashes.size() << " hashes found." << endl;    
    auto imageNames = loadImageNames("inputImages/imageNames.txt");
    auto excludeList = loadExcludeList(excludeListFullPath);
    cout << imageNames.size() << " image names found." << endl;
    int finOutputArr[64] = {0};
    for (auto name: imageNames)
    {
        int outputArr[64] = {0};
        if ( !isInExcludeList(name, excludeList, imageName) ){
            cout << "Output for image: " << name << endl;
            auto toCompareHashes = loadHashesFromFile<T>("inputImages/"+ name + "/hashes.txt");
            for (auto hash : hashes){
                for (auto comp: toCompareHashes){
                    int dist = hash.getHammingDistance(comp);
                    if (dist < threshold){
                        cout << "ERROR: dist below threshold" << endl;
                    }

                    if (dist <= 64){
                        outputArr[dist] += 1;
                    }else{
                        cout << "ERROR: bad hamming distance: " << dist << endl;
                        exit(1);
                    }
                }
            }
            for (int i = 0; i<64;i++)
            {
                cout << i << ": " << outputArr[i] << endl;
                finOutputArr[i] += outputArr[i];
            }
        }
    }
    cout << "finoutput: " << endl;
    for (int i = 0; i<64;i++)
    {
        cout << i << ": " << finOutputArr[i] << endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3){
        printf("error: no args!!!\n");
        return -1;
    }

    string imageName = (argc > 2)? argv[2]: "img1";
    string imageFullPath =  "inputImages/"+ imageName + "/" + imageName + ".jpg";
    string imagePoints =    "inputImages/"+ imageName + "/keypoints.txt";

    if (argc > 2 && !strcmp(argv[1], "dumpRandom")){
        cout << "Dumping image hashes for: " << imageName << endl;
        dumpHashes<hashes::PerceptualHash>(imageName, imagePoints, imageFullPath);
    }else if (argc > 2 && !strcmp(argv[1], "printConflicts")){
        cout << "Printing conflicts: " << imageName << endl;
        printConflicts<hashes::PerceptualHash>(imageName, imagePoints, imageFullPath);
    }else{
        cout << "Bad argument: " << argv[1] << endl;
    }
}
