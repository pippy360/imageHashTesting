#ifndef average_hash_h
#define average_hash_h

#include <string>
#include <vector>
#include <memory>
#include "Keypoint.h"
#include "FragmentHash.h"

using namespace std;

namespace hashes{

class AverageHash : public FragmentHash<vector<bool>>
{
private:
    vector<bool> hash;
    vector<Keypoint> shape;

    static std::string convertHashToString(vector<bool> hash)
    {
        std::string ret = "";
        int h = 0;
        for (unsigned int i = 0; i < hash.size(); i++)
        {
            if (hash[i]){
                h += pow(2, (i % 8));
            }

            if (i%8 == 7){
                std::stringstream buffer;
                buffer << std::hex << std::setfill('0') << std::setw(2) << h;
                ret += buffer.str();
                h = 0;
            }
        }
        return ret;
    }

    static AverageHash hex_str_to_hash(std::string inputString)
    {
        std::vector<bool> hash;
        int size = inputString.size()/2;
        for (int i = 0; i < size; i++)
        {
            std::string str2 = inputString.substr(i*2,2);
            if (str2.empty()){
                continue;
            }

            unsigned int value = 0;
            std::stringstream SS(str2);
            SS >> std::hex >> value;
            for (int j = 0; j < 8; j++)
            {
                bool check = !!((value>>j)&1);
                hash.push_back(check);			
            }
        }
        return AverageHash(hash);
    }

public:

    AverageHash(vector<bool> hash, std::vector<Keypoint> shape=vector<Keypoint>()):
            FragmentHash<vector<bool>>(hash, shape)
    {}

    AverageHash(const AverageHash& that) :
            FragmentHash<vector<bool>>(that.hash_, that.shape_)
    {}

    string toString() override 
    {
        return convertHashToString(hash_);
    }

    AverageHash* buildHashFromString(string fragmentHashString, vector<Keypoint> shape=vector<Keypoint>()) override
    {
        AverageHash val = hex_str_to_hash(fragmentHashString);
        return new AverageHash(val);
    }


};

}//end of namespace
#endif // average_hash_h


