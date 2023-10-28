#pragma once

#include <string>
#include <vector>

class Converter
{
public:
	static int FromAngleToCoord(float angle);
	static float FromCoordToAngle(int coord);
	static std::vector<float> FromStringToAngles(std::string str);
	static std::vector<int> FromStringToInt(std::string str);

protected:

private:

};

