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
#include "utils/utils.hpp"

using namespace std;


template<typename T> void dumpHashes(string imageName, string imagePoints, string imageFullPath)
{
    auto triangles = getTheTris_random(imagePoints);
    auto loadedImage = getLoadedImage(imageFullPath);
    auto hashes = cv::getAllTheHashesForImage<T>(loadedImage, triangles, imageName);
    writeHashObjectsToFile<T>("inputImages/"+ imageName + "/hashes.txt", hashes);
}

template <typename T> void testNonMatchingFragmentsForFalsePositive(string imageName, string imagePoints, string imageFullPath, int threshold = 3)
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
        testNonMatchingFragmentsForFalsePositive<hashes::PerceptualHash>(imageName, imagePoints, imageFullPath);
    }else{
        testNonMatchingFragmentsForFalsePositive<hashes::PerceptualHash>(imageName, imagePoints, imageFullPath);
        cout << "Bad argument: " << argv[1] << endl;
    }
}
