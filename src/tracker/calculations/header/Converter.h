#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <windows.h>

class Converter
{
public:
	Converter(INT width, INT height, FLOAT maxAngleX, FLOAT maxAngleY);

	// Window coordinates
	INT ToCoordX(FLOAT angle);
	INT ToCoordY(FLOAT angle);
	INT ToCoordX_Log(INT logCoord) const;
	INT ToCoordY_Log(INT logCoord) const;
	static POINT ToCoord(std::string str);
	POINT ToCoord(POINTFLOAT point);
	POINT ToCoord(POINT logPoint);

	// Angle coordinates
	FLOAT ToAngleX(INT coord) const;
	FLOAT ToAngleY(INT coord) const;
	FLOAT ToAngleX_Log(INT logCoord) const;
	FLOAT ToAngleY_Log(INT logCoord) const;
	POINTFLOAT ToAngle(std::string str);
	POINTFLOAT ToAngle(POINT point);
	POINTFLOAT ToAngle_Log(POINT logPoint);

	// Logical coordinates
	INT ToLogCoordX(INT coord) const;
	INT ToLogCoordY(INT coord) const;
	INT ToLogCoordX_Angle(FLOAT angle);
	INT ToLogCoordY_Angle(FLOAT angle);
	POINT ToLogCoord(POINTFLOAT point);
	POINT ToLogCoord(POINT point);
	POINT ToLogCoord(std::string str);

	POINT ToLogCoord_FromCoordString(std::string str);
	POINT ToLogCoord_FromAngleString(std::string str);

	POINT ToCoord_FromLogCoordString(std::string str);
	POINT ToCoord_FromAngleString(std::string str);

	POINTFLOAT ToAngle_FromLogCoordString(std::string str);
	POINTFLOAT ToAngle_FromCoordString(std::string str);

	static FLOAT ToAngle_FromRadian(FLOAT radian);
	static FLOAT ToRadian_FromAngle(FLOAT angle);

	static POINTFLOAT ToAngle_FromRadian(POINTFLOAT radian);
	static POINTFLOAT ToRadian_FromAngle(POINTFLOAT angle);

	static FLOAT GetFloat_FromWindowText(HWND hWnd);
	static INT GetValue(std::string str);
protected:
	INT maxCoordX;
	INT maxCoordY;

	FLOAT maxAngleX;
	FLOAT maxAngleY;
	FLOAT angleWidth;
	FLOAT angleHeight;

	INT maxLogCoordX;
	INT maxLogCoordY;
private:
	std::string ReplaceCommas(std::string str);
};
