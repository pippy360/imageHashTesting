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

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

namespace pt = boost::property_tree;


static unsigned long x=123456789, y=362436069, z=521288629;

unsigned long xorshf96(void) {          //period 2^96-1
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

void drawSingleTriangleOntoImage(Triangle tri, cv::Mat inputImage, bool randomColours = true){
    auto keypoints = tri.toKeypoints();
    auto prevPoint = keypoints.back();
//    for (auto currentPoint: keypoints)
//    {
    int r = (int) xorshf96();
    int g = (int) xorshf96();
    int b = (int) xorshf96();
    for (int i = 0; i < 3; i++){
        auto currentPoint = keypoints[i];

        cv::line(inputImage, cv::Point(prevPoint.x, prevPoint.y), cv::Point(currentPoint.x, currentPoint.y),
                 cv::Scalar(b,g,r));
        cv::imshow("something", inputImage);
        cv::waitKey(10);
        prevPoint = currentPoint;
    }
}


void drawTrianglesOntoImage(vector<Triangle> tris, cv::Mat inputImage, bool randomColours = true)
{
    for (auto tri: tris){
        drawSingleTriangleOntoImage(tri, inputImage, randomColours);
    }
}

Triangle getTriangleFromRedisEntry(string redisEntry)
{
    pt::ptree root;
    std::stringstream ss;
    ss << redisEntry;
    pt::read_json(ss, root);

    vector<Keypoint> keypoints;
    for (auto pt_j: root.get_child("triangle"))
    {
        double x = pt_j.second.get<double>("x");
        double y = pt_j.second.get<double>("y");
        keypoints.push_back(Keypoint(x,y));        
    }
    return Triangle(keypoints);
}

string getImageNameFromRedisEntry(string redisEntry)
{
    pt::ptree root;
    std::stringstream ss;
    ss << redisEntry;
    pt::read_json(ss, root);
    return root.get<string>("imageName");
}

string convertToRedisEntryJson(string imageName, Triangle tri){
    pt::ptree root;
    root.put("imageName", imageName);

    //add each point of the triangle
    pt::ptree points;
    for (auto pt : tri.toKeypoints())
    {
        pt::ptree point;
        point.put("x", pt.x);
        point.put("y", pt.y);
        points.push_back(std::make_pair("", point));
    }
    root.add_child("triangle", points);

    std::ostringstream buf;
    write_json(buf, root, false);
    return buf.str();
}

vector<Keypoint> readKeypointsFromJsonFile(std::ifstream *file)
{
    vector<Keypoint> result;
    try {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(*file, pt);

        for (auto label0 : pt) {
            if (label0.first == "output") {
                for (auto label1: label0.second) {
                    if (label1.first == "keypoints") {
                        for (auto kp : label1.second){
                            double x, y;
                            for (auto pt : kp.second){
                                if(pt.first == "x"){
                                    x = pt.second.get_value<double>();
                                }else{
                                    y = pt.second.get_value<double>();
                                }
                            }
                            result.push_back(Keypoint(x, y));
                        }
                    }
                }
            }
        }
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
    return result;
}

vector<Keypoint> readKeypointsFromJsonFile(string filename)
{
    std::ifstream file(filename);
    return readKeypointsFromJsonFile(&file);
}

void print(boost::property_tree::ptree const &pt) {
}

double getKeypointDistance(Keypoint one, Keypoint two)
{
	return sqrt( pow( one.x-two.x, 2.0 ) + pow( one.y-two.y, 2.0 ) );
}

vector<Keypoint> findKeypointsWithInRangeFromTwoPoints(Keypoint one, Keypoint two, vector<Keypoint> otherKeypoints, double lowerThreshold, double upperThreshold)
{
	vector<Keypoint> result;
	for (auto cmpKp : otherKeypoints)
	{
        double distanceFromPointOne = getKeypointDistance(one, cmpKp);
        double distanceFromPointTwo = getKeypointDistance(two, cmpKp);
		if(distanceFromPointOne > lowerThreshold && distanceFromPointOne < upperThreshold
                && distanceFromPointTwo > lowerThreshold && distanceFromPointTwo < upperThreshold)
		{
			result.push_back(cmpKp);
		}
	}
	return result;
}

bool isInKeypointExcludeList(Keypoint keypoint, vector<Keypoint> excludeList) {
    for (auto kp : excludeList)
    {
        if(kp.x == keypoint.x && kp.y == keypoint.y){
            return true;
        }
    }
    return false;
}

bool shouldPointBeExcluded(Keypoint pt, vector<Keypoint> previouslyProcessedPoints, vector<Keypoint> currentProcessedPoints, Keypoint currentTopLevelPoint, Keypoint currentSecondLevelPoint)
{
    return isInKeypointExcludeList(pt, previouslyProcessedPoints)
           || isInKeypointExcludeList(pt, currentProcessedPoints)
           || currentTopLevelPoint == pt
           || currentSecondLevelPoint == pt
            ;
}

//NOTE: otherKeypoints may contain centerKeypoint
vector<Triangle> buildTrianglesForSingleKeypoint(Keypoint centerKeypoint, vector<Keypoint> otherKeypoints, vector<Keypoint> previouslyProcessedPoints, double lowerThreshold, double upperThreshold)
{
	vector<Triangle> result;
    vector<Keypoint> currentProcessedPoints;//a collection of points we have processed since entering this function
	for (auto iterKeypoint: otherKeypoints)
	{
        if(isInKeypointExcludeList(iterKeypoint, previouslyProcessedPoints) || iterKeypoint == centerKeypoint) {
            continue;
        }

        double distance = getKeypointDistance(iterKeypoint, centerKeypoint);
		if(distance > lowerThreshold && distance < upperThreshold)
		{
			vector<Keypoint> finalKeypoints = findKeypointsWithInRangeFromTwoPoints(iterKeypoint, centerKeypoint, otherKeypoints, lowerThreshold, upperThreshold);
			for (auto finKp : finalKeypoints)
			{
                //check if this combination of points will make a triangle we have already created
                if(shouldPointBeExcluded(finKp, previouslyProcessedPoints, currentProcessedPoints, centerKeypoint, iterKeypoint)){
                    continue;
                }
                Triangle testingTri(centerKeypoint, iterKeypoint, finKp);
                if(testingTri.calcArea() > 200){
                    result.push_back(testingTri);
                }
			}
		}
        currentProcessedPoints.push_back(iterKeypoint);
	}
	return result;
}

vector<Triangle> buildTrianglesFromKeypoints(vector<Keypoint> keypoints, double lowerThreshold=150, double upperThreshold=300)
{
	vector<Triangle> outputTriangles;
//	for (auto keypoint: keypoints)
//	{
    //FIXME: this multi-threading needs to be improved
    #pragma omp parallel
    {
        vector<Triangle> vec_private;
        #pragma omp for nowait schedule(static)
        for (unsigned int i = 0; i < keypoints.size(); i++)
        {
            vector<Keypoint>::const_iterator first = keypoints.begin();
            vector<Keypoint>::const_iterator last = keypoints.begin() + i;
            vector<Keypoint> processedPoints(first, last);
            auto keypoint = keypoints[i];
            auto triangles = buildTrianglesForSingleKeypoint(keypoint, keypoints, processedPoints, lowerThreshold, upperThreshold);
            for (auto tri : triangles){
                vec_private.push_back(tri);
            }
            processedPoints.push_back(keypoint);
        }
        #pragma omp critical
        outputTriangles.insert(outputTriangles.end(), vec_private.begin(), vec_private.end());
    }
	return outputTriangles;
}

vector<Triangle> buildTrianglesFromKeypointJsonFile(string filename){
    vector<Keypoint> output = readKeypointsFromJsonFile(filename);
    vector<Triangle> ret = buildTrianglesFromKeypoints(output, 50, 400);
    return ret;
}

vector<Triangle> getTriangles(string filename){
    return buildTrianglesFromKeypointJsonFile(filename);
}

const pair<vector<Triangle>, vector<Triangle>> readMatchingTrianglesFromJsonFile(std::ifstream *file) {
    vector<Triangle> image1OutputTriangles;
    vector<Triangle> image2OutputTriangles;
    try {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(*file, pt);

        using boost::property_tree::ptree;
        for (auto it : pt) {
            if (it.first == "count") {
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
    catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }

    return pair<vector<Triangle>, vector<Triangle>>(image1OutputTriangles, image2OutputTriangles);
}

const pair<vector<Triangle>, vector<Triangle>> readMatchingTrianglesFromJsonFile(const string filename) {
    std::ifstream file(filename);
    return readMatchingTrianglesFromJsonFile(&file);
}

template<typename T>
const vector<T> readJsonHashesFile(std::ifstream *file) {
    vector<T> ret;
    vector<Triangle> image1OutputTriangles;
    vector<Triangle> image2OutputTriangles;
    try {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(*file, pt);

        for (auto label0 : pt) {
            if (label0.first == "output") {
                for (auto label1: label0.second) {
                    if (label1.first == "imageName") {
                        //save the imageName
                    } else if (label1.first == "hashes") {
                        for (auto hash_item: label1.second) {
                            ret.push_back(T(hash_item.second.get_value<std::string>()));
                            //cout << "hash: " << hash_item.second.get_value<std::string>() << endl;
                        }
                    }
                }
            }
        }

        print(pt);
    }
    catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }

    return ret;
}

template<typename T>
const vector<T> readJsonHashesFile(const string filename) {
    std::ifstream file(filename);
    return readJsonHashesFile<T>(&file);
}

template<typename T>
void dumpHashesToJsonFile(std::ofstream *file, vector<T> hashes) {
    ptree outputTree, hashesTree;
    for(auto hash: hashes){
        hashesTree.push_back(std::make_pair( "", ptree(hash.toString()) ));
    }
    outputTree.put_child("output.hashes", hashesTree);
    std::stringstream ss;
    write_json(ss, outputTree);
    *file << ss.str();
}

template<typename T> void dumpHashesToJsonFile(const string filename, vector<T> hashes) {
    std::ofstream ofs;
    ofs.open (filename, std::ofstream::out);
    dumpHashesToJsonFile<T>(&ofs, hashes);
}

ShapeAndPositionInvariantImage getLoadedImage(string imageFullPath) {
    cv::Mat img = cv::imread(imageFullPath);
    return ShapeAndPositionInvariantImage("", img, std::vector<Keypoint>(), "");
}

void writeHashesToFile(string fullFilePath, vector<string> hashes) {
    std::ofstream outputFile;
    outputFile.open(fullFilePath, std::ios::out);
    for (auto hash: hashes) {
        outputFile << hash << endl;
    }
}

template<typename T>
void writeHashObjectsToFile(string fullFilePath, vector<T> hashes) {
    vector<string> hashesToString;
    for (auto hash: hashes) {
        hashesToString.push_back(hash.toString());
    }
    writeHashesToFile(fullFilePath, hashesToString);
}

vector<string> loadImageNames(string filename) {
    vector<string> filenames;

    std::ifstream file(filename);
    std::string str = "";
    while (true) {
        if (!std::getline(file, str)) {
            break;
        }
        filenames.push_back(str);
    }

    return filenames;
}

vector<string> loadExcludeList(string filename) {
    vector<string> filenames;

    std::ifstream file(filename);
    std::string str = "";
    while (true) {
        if (!std::getline(file, str)) {
            break;
        }
        filenames.push_back(str);
    }

    return filenames;
}

template<typename T>
std::vector<T> loadHashesFromFile(std::string filename) {
    std::vector<T> ret;
    std::ifstream file(filename);
    std::string str = "";
    while (true) {
        if (!std::getline(file, str)) {
            break;
        }

        T fraghash(str);
        ret.push_back(fraghash);
        //std::cout << str << " should match: " << cv::convertHashToString(fraghash) << std::endl;
    }
    return ret;
}

bool isInImageNameExcludeList(string name, vector<string> excludeList, string imageName) {
    if (name == imageName) {
        return true;
    }
    for (auto e: excludeList) {
        if (name == e) {
            return true;
        }
    }
    return false;
}

#endif//utils_utils_hpp
