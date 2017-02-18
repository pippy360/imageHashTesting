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
//    }else if (argc > 2 && !strcmp(argv[1], "speedTest")){
//        hasingSpeedTestFull<hashes::PerceptualHash_Fast>(imageName);
//    }else if (argc > 2 && !strcmp(argv[1], "dumpThem")){
//        dumpThem(imageName);
    }else if (argc > 2 && !strcmp(argv[1], "addRedisImage")){
        addAllHashesToRedis(imageName);
    }else if (argc > 2 && !strcmp(argv[1], "checkRedisImage")){
        findMatchingHashInRedis(imageName);
    }else{
        cout << "Bad argument: " << argv[1] << endl;
    }
}
