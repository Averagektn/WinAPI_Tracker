#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>

class Converter
{
public:
	static int FromAngleToCoord(float angle, int maxCoord, float maxAngle);
	static float FromCoordToAngle(int coord, int maxCoord, float maxAngle);

	static std::vector<float> FromStringToAngles(std::string str);
	static std::vector<int> FromStringToInt(std::string str);

protected:

private:

};

