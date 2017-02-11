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
#include "img_hash/PerceptualHash_Fast.h"

//#include "img_hash/FragmentHash.h"
//#include "ShapeAndPositionInvariantImage.h"
#include "Triangle.h"
#include "mainImageProcessingFunctions.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include "utils/utils.hpp"
#include "hiredis/hiredis.h"
#include <map>

using namespace std;


//template<typename T> void dumpHashes(string imageName, string imagePoints, string imageFullPath)
//{
//    auto triangles = getTheTris_random(imagePoints);
//    auto loadedImage = getLoadedImage(imageFullPath);
//    auto hashes = cv::getAllTheHashesForImage<T>(loadedImage, triangles, "inputImages/"+imageName+"/outputFragments");
//    writeHashObjectsToFile<T>("inputImages/"+ imageName + "/hashes.txt", hashes);
//}
//
//template <typename T> void testNonMatchingFragmentsForFalsePositive(string imageName, string imagePoints, string imageFullPath, int threshold = 3)
//{
//    const string hashesFileFullPath = "inputImages/"+ imageName + "/hashes.txt";
//    const string excludeListFullPath = "inputImages/"+ imageName + "/excludeList.txt";
//    auto triangles = getTheTris(imagePoints);
//    auto loadedImage = getLoadedImage(imageFullPath);
//    auto hashes = loadHashesFromFile<T>(hashesFileFullPath);
//    cout << hashes.size() << " hashes found." << endl;
//    auto imageNames = loadImageNames("inputImages/imageNames.txt");
//    auto excludeList = loadExcludeList(excludeListFullPath);
//    cout << imageNames.size() << " image names found." << endl;
//    int finOutputArr[65] = {0};
//    for (auto name: imageNames)
//    {
//        int outputArr[65] = {0};
//        if ( !isInImageNameExcludeList(name, excludeList, imageName) ){
//            cout << "Output for image: " << name << endl;
//            auto toCompareHashes = loadHashesFromFile<T>("inputImages/"+ name + "/hashes.txt");
//            for (auto hash : hashes){
//                for (auto comp: toCompareHashes){
//                    int dist = hash.getHammingDistance(comp);
//                    if (dist < threshold){
//                        cout << "ERROR: dist below threshold" << endl;
//                    }
//
//                    if (dist <= 64){
//                        outputArr[dist] += 1;
//                    }else{
//                        cout << "ERROR: bad hamming distance: " << dist << endl;
//                        exit(1);
//                    }
//                }
//            }
//            for (unsigned int i = 0; i<64;i++)
//            {
//                cout << i << ": " << outputArr[i] << endl;
//                finOutputArr[i] += outputArr[i];
//            }
//        }
//    }
//    cout << "finoutput: " << endl;
//    for (unsigned int i = 0; i<64;i++)
//    {
//        cout << i << ": " << finOutputArr[i] << endl;
//    }
//}
//
//template<typename T> vector<int> testMatchingFragments(string imageName) {
//    int finOutputArr[65] = {0};
//    vector<Triangle> imageTris1;
//    vector<Triangle> imageTris2;
//    tie(imageTris2, imageTris1) = readMatchingTrianglesFromJsonFile("imageMatchingPairs/"+imageName+"/matchingTriangles.json");
//    auto loadedImage1 = getLoadedImage("imageMatchingPairs/"+imageName+"/img1.jpg");
//    auto loadedImage2 = getLoadedImage("imageMatchingPairs/"+imageName+"/img2.jpg");
//    auto hashes1 = cv::getAllTheHashesForImage<T>(loadedImage1, imageTris1, "imageMatchingPairs/"+imageName+"/outputFragments", "1");
//    auto hashes2 = cv::getAllTheHashesForImage<T>(loadedImage2, imageTris2, "imageMatchingPairs/"+imageName+"/outputFragments", "2");
//    for (unsigned int i = 0; i < hashes1.size(); i++)
//    {
//        int dist = hashes1[i].getHammingDistance(hashes2[i]);
//        finOutputArr[dist] += 1;
//        //cout << "Distance of: " << hashes1[i].toString() << " and: " << hashes2[i].toString() << " is: " << dist << endl;
//    }
//    vector<int> ret;
//    for (int i = 0; i < 65; i++) {
//        ret.push_back(finOutputArr[i]);
//    }
//    return ret;
//}
//
//template<typename T> void testMatchingFragmentsForAllInputImages() {
//    //TODO:
//    auto imageNames = loadImageNames("inputImages/imageNames.txt");
//    int finOutputArr[65] = {0};
//    for(auto name: imageNames)
//    {
//        auto tempRes = testMatchingFragments<T>(name);
//        for (int i = 0; i < 65; i++){
//            finOutputArr[i] += tempRes[i];
//        }
//    }
//    for (int i = 0; i < 65; i++) {
//        cout << i << ": " << finOutputArr[i] << endl;
//    }
//}
//
//template<typename T> int hasingSpeedTestInner(string imageName, vector<Triangle> tris, ShapeAndPositionInvariantImage loadedImage)
//{
//    auto hashes1 = cv::getAllTheHashesForImage<T>(loadedImage, tris, "imageMatchingPairs/"+imageName+"/outputFragments", "1");
//    return 0;
//}


//template<typename T> vector<T> hasingSpeedTestInner_full(string imageName, vector<Triangle> tris, ShapeAndPositionInvariantImage loadedImage)
//{
//    return cv::getAllTheHashesForImage<T>(loadedImage, tris, "imageMatchingPairs/"+imageName+"/outputFragments", "1");
//}

template<typename T> void hasingSpeedTestFull(string imageName) {
//    auto triangles = getTriangles("inputImages/"+imageName+"/keypoints2.json");
//    cv::Mat img = cv::imread("imageMatchingPairs/"+imageName+"/img1.jpg");
//    auto loadedImage1 = ShapeAndPositionInvariantImage("", img, std::vector<Keypoint>(), "");
//    cout << "About to processs " << triangles.size() << " triangles" << endl;
//    auto def = hasingSpeedTestInner_full<T>(imageName, triangles, loadedImage1);
//    cout << def.size() << endl;
}

template<typename T> void hasingSpeedTest(string imageName) {
//    vector<Triangle> imageTris1;
//    vector<Triangle> imageTris2;
//    tie(imageTris2, imageTris1) = readMatchingTrianglesFromJsonFile("imageMatchingPairs/"+imageName+"/matchingTriangles.json");
//    cv::Mat gray_image;
//    cv::Mat img = cv::imread("imageMatchingPairs/"+imageName+"/img1.jpg");
//    cv::cvtColor( img, gray_image, CV_BGR2GRAY );
//    auto loadedImage1 = ShapeAndPositionInvariantImage("", gray_image, std::vector<Keypoint>(), "");
//    // auto loadedImage1 = ShapeAndPositionInvariantImage("", img, std::vector<Keypoint>(), "");
//    for (int i = 0; i < 7; i++) {
//        imageTris2.insert(std::end(imageTris2), std::begin(imageTris2), std::end(imageTris2));
//    }
//    cout << "About to processs " << imageTris2.size() << " triangles" << endl;
//    auto def = hasingSpeedTestInner<T>(imageName, imageTris2, loadedImage1);
//    cout << def << endl;
}

void dumpThem(string imageName)
{
//    vector<Triangle> imageTris1;
//    vector<Triangle> imageTris2;
//    tie(imageTris2, imageTris1) = readMatchingTrianglesFromJsonFile("imageMatchingPairs/"+imageName+"/matchingTriangles.json");
//    auto loadedImage1 = getLoadedImage("imageMatchingPairs/"+imageName+"/img1.jpg");
//    auto loadedImage2 = getLoadedImage("imageMatchingPairs/"+imageName+"/img2.jpg");
//    auto hashes1 = cv::getAllTheHashesForImage<hashes::PerceptualHash>(loadedImage1, imageTris1, "imageMatchingPairs/"+imageName+"/outputFragments", "1");
//
//    dumpHashesToJsonFile<hashes::PerceptualHash>("c_src/test/resources/savedHashes.json", hashes1);
}

void addAllHashesToRedis(string imageName){
    vector<Triangle> tris = getTriangles("../inputImages/"+imageName+"/keypoints2.json");
    auto loadedImage = getLoadedImage("../inputImages/"+imageName+"/"+imageName+".jpg");
    auto hashTrianglePairs = cv::getAllTheHashesForImage<hashes::PerceptualHash>(loadedImage, tris, "../inputImages/"+imageName+"/outputFragments", "1");

    redisContext *c;
//    redisReply *reply;
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

    for (auto hashTriangle : hashTrianglePairs)
    {
        string redisEntry = convertToRedisEntryJson(imageName, hashTriangle.first);
        redisCommand(c,"SADD %s %s", hashTriangle.second.toString().c_str(), redisEntry.c_str());
    }
}

void findMatchingHashInRedis(string imageName){
    vector<Triangle> tris = getTriangles("../inputImages/"+imageName+"/keypoints2.json");
    auto loadedImage = getLoadedImage("../inputImages/"+imageName+"/"+imageName+".jpg");
    auto hashTrianglePairs = cv::getAllTheHashesForImage<hashes::PerceptualHash>(loadedImage, tris, "../inputImages/"+imageName+"/outputFragments", "1");

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
    cout << "finished hashing" << endl;
//    vector<hashes::PerceptualHash_Fast> result;
    vector<string> result;
//    for (auto hash : hashes)
//    {
    unsigned int batchSize = 1000;
    for (unsigned int i = 0; i < hashTrianglePairs.size(); i++)
    {
        unsigned int j = 0;
        for(;i < hashTrianglePairs.size() && j < batchSize; j++, i++){
            auto hashTriangle = hashTrianglePairs[i];
            redisAppendCommand(c,"SMEMBERS %s", hashTriangle.second.toString().c_str());
        }

        for(; j > 0; j--){
            redisGetReply(c, (void **) &reply );
            //unsigned int r = redisGetReply(c, (void **) &reply );
            for (unsigned int k = 0; k < reply->elements; k++)
            {
                string str(reply->element[k]->str);
                result.push_back(str);
            }
        }

    }
    std::map<string,vector<Triangle>> resultMap;
    for (auto t_str : result)
    {
        auto redisReplyImageName = getImageNameFromRedisEntry(t_str);
        if(redisReplyImageName == imageName){
            continue;
        }
        auto redisReplyTriangle = getTriangleFromRedisEntry(t_str);
        resultMap[redisReplyImageName];
        resultMap[redisReplyImageName].push_back(redisReplyTriangle);
    }
    cout << "Matches:" << endl;
    for(auto const& ent1 : resultMap)
    {
        if(ent1.first == imageName){
            continue;
        }
        auto tempImg = cv::imread("../inputImages/"+ent1.first+"/"+ent1.first+".jpg");
        drawTrianglesOntoImage(ent1.second, tempImg);
        cv::imwrite("../outputFromSearch_"+ent1.first+".jpg", tempImg);

        cout << ent1.first << ": " << ent1.second.size() << endl;
    }

    cout << "Number of matches: " << result.size() << endl;
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
//        dumpHashes<hashes::PerceptualHash>(imageName, imagePoints, imageFullPath);
//    }else if (argc > 2 && !strcmp(argv[1], "printConflicts")){
//        cout << "Printing conflicts: " << imageName << endl;
//        testNonMatchingFragmentsForFalsePositive<hashes::PerceptualHash>(imageName, imagePoints, imageFullPath);
//    }else if (argc > 2 && !strcmp(argv[1], "testMatching")){
//        testMatchingFragments<hashes::PerceptualHash>(imageName);
//    }else if (argc > 2 && !strcmp(argv[1], "testAllMatching")){
//        testMatchingFragmentsForAllInputImages<hashes::PerceptualHash_Fast>();
    }else if (argc > 2 && !strcmp(argv[1], "speedTest")){
        hasingSpeedTestFull<hashes::PerceptualHash_Fast>(imageName);
    }else if (argc > 2 && !strcmp(argv[1], "dumpThem")){
        dumpThem(imageName);
    }else if (argc > 2 && !strcmp(argv[1], "addRedisImage")){
        addAllHashesToRedis(imageName);
    }else if (argc > 2 && !strcmp(argv[1], "checkRedisImage")){
        findMatchingHashInRedis(imageName);
    }else{
        cout << "Bad argument: " << argv[1] << endl;
    }
}
