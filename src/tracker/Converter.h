#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <windows.h>

// Example
// Angles from -180 to 180
// Coords from 0 to 720
// LogCoords from - 360 to 360

class Converter
{
public:
	Converter(int width, int height, float maxAngleX, float maxAngleY);

	int ToCoordX(float angle);
	int ToCoordY(float angle);
	int ToCoordX_Log(int logCoord);
	int ToCoordY_Log(int logCoord);
	POINT ToCoord(std::string str);
	POINT ToCoord(POINTFLOAT point);
	POINT ToCoord(POINT logPoint);

	float ToAngleX(int coord);
	float ToAngleY(int coord);
	float ToAngleX_Log(int logCoord);
	float ToAngleY_Log(int logCoord);
	POINTFLOAT ToAngle(std::string str);
	POINTFLOAT ToAngle(POINT point);
	POINTFLOAT ToAngle_Log(POINT logPoint);

	int ToLogCoordX(int coord);
	int ToLogCoordY(int coord);
	int ToLogCoordX_Angle(float angle);
	int ToLogCoordY_Angle(float angle);
	POINT ToLogCoord(POINTFLOAT point);
	POINT ToLogCoord(POINT point);
	POINT ToLogCoord(std::string str);

protected:
	int maxCoordX;
	int maxCoordY;

	float maxAngleX;
	float maxAngleY;
	float angleWidth;
	float angleHeight;

	int maxLogCoordX;
	int maxLogCoordY;

private:

};

