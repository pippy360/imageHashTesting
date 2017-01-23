#pragma once
#include "Keypoint.h"

class Triangle
{
public:
	inline Triangle(Keypoint one, Keypoint two, Keypoint three){
		keypoints_[0] = one;
		keypoints_[1] = two;
		keypoints_[2] = three;
	}
	Keypoint keypoints_[3];
	std::vector<Keypoint> toKeypoints() const;
};

inline std::vector<Keypoint> Triangle::toKeypoints() const
{
	auto ret = std::vector<Keypoint>();
	for (int i = 0; i < 3; i++)
	{
		ret.push_back(keypoints_[i]);
	}
	return ret;
}
