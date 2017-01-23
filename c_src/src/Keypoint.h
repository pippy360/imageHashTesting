#pragma once
class Keypoint
{
public:
	double x, y;
	Keypoint() {};
	Keypoint(double _x, double _y);
};

inline Keypoint::Keypoint(double _x, double _y)
{
	x = _x;
	y = _y;
}
