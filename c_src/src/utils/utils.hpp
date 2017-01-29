#ifndef utils_utils_hpp
#define utils_utils_hpp
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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include "utils/utils.hpp"
#include <tuple>

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

void print(boost::property_tree::ptree const& pt)
{
}

const pair<vector<Triangle>, vector<Triangle>> readMatchingTrianglesFromJsonFile(std::ifstream *file){
    vector<Triangle> image1OutputTriangles;
    vector<Triangle> image2OutputTriangles;
    cout << "here..." << endl;
    try
    {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(*file, pt);

        using boost::property_tree::ptree;
        for (auto it : pt) {
            if (it.first == "count"){
                //save count
                cout << "Number of triangles read: " << it.second.get_value<std::string>() << endl;
            }

            if (it.first == "triangles") {
                for (auto tri: it.second) {
                    vector<Keypoint> one, two;
                    for (auto tri_point : tri.second) {
                        vector<Keypoint> bothKp;
                        for (auto pt_u : tri_point.second) {
                            vector<double> tempPoint;
                            for (auto pt : pt_u.second) {
                                double coord = pt.second.get_value<double>();
                                tempPoint.push_back(coord);
                            }
                            Keypoint kp(tempPoint[0], tempPoint[1]);
                            bothKp.push_back(kp);
                        }
                        one.push_back(bothKp[0]);
                        two.push_back(bothKp[1]);
                    }
                    Triangle one_t(one);
                    Triangle two_t(two);
                    image1OutputTriangles.push_back(one_t);
                    image2OutputTriangles.push_back(two_t);
                }
            }
        }

        print(pt);
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return pair<vector<Triangle>, vector<Triangle>>(image1OutputTriangles, image2OutputTriangles);
}

const pair<vector<Triangle>, vector<Triangle>> readMatchingTrianglesFromJsonFile(const string filename) {
    std::ifstream file(filename);
    return readMatchingTrianglesFromJsonFile(&file);
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

#endif//utils_utils_hpp
