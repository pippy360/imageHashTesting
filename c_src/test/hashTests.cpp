#include "gtest/gtest.h"
#include "img_hash/AverageHash.h"

#include <stdio.h>


using namespace hashes;

TEST(AverageHash, BasicTests){
    AverageHash testHash = AverageHash (vector<bool>());
    AverageHash* testHash2 = testHash.buildHashFromString("7ca4a6eee2a32515");
    EXPECT_EQ("7ca4a6eee2a32515", testHash2->toString());
}

