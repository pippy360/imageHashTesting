#ifndef average_hash_h
#define average_hash_h

#include <string>
#include <vector>
#include "Keypoint.h"
#include "FragmentHash.h"

using namespace std;

template <typename T> class AverageHash : public FragmentHash<string>
{
private:
    vector<bool> hash;
    vector<Keypoint> shape;

    static std::string convertHashToString(vector<bool> hash) const
    {
        std::string ret = "";
        int h = 0;
        for (int i = 0; i < hash.size(); i++)
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
        return FragmentHash(hash);
    }

public:

    AverageHash(T hash, std::vector<Keypoint> shape=vector<Keypoint>()):
        hash(hash),
        shape(shape) 
    {}

    string toString() override 
    {
        return convertHashToString(this);
    }

    AverageHash& buildHashFromString(string fragmentHashString, vector<Keypoint> shape=vector<Keypoint>()) override 
    {
        return hex_str_to_hash(fragmentHashString);
    }


};

#endif // average_hash_h
