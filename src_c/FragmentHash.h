#include <vector>
#include "Keypoint.h"

#pragma once
class FragmentHash
{
private:
    std::vector<bool> hash_;
    std::vector<Keypoint> shape_;

public:
    inline FragmentHash(std::vector<bool> hash, std::vector<Keypoint> shape=std::vector<Keypoint>()){
        hash_ = hash;
        shape_ = shape;
    };

    inline std::vector<bool> getHash(){
        return hash_;
    }

    inline std::vector<Keypoint> getShape(){
        return shape_;
    }
};
