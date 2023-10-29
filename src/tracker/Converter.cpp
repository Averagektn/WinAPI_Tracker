#include "Converter.h"

int Converter::FromAngleToCoord(float angle, int maxCoord, float maxAngle)
{
	return (int)round(angle * maxCoord / maxAngle);
}

float Converter::FromCoordToAngle(int coord, int maxCoord, float maxAngle)
{
	float res = coord * maxAngle / maxCoord;
	return res;
}

std::vector<float> Converter::FromStringToAngles(std::string str)
{
    std::vector<float> angles;
    std::istringstream iss(str);
    float angle;

    while (iss >> angle) 
    {
        angles.push_back(angle);
    }

    return angles;
}

std::vector<int> Converter::FromStringToInt(std::string str)
{
    std::vector<int> integers;
    std::istringstream iss(str);
    int number;

    while (iss >> number) 
    {
        integers.push_back(number);
    }

    return integers;
}
