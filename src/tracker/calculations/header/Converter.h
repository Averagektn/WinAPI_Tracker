#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <windows.h>

/// <summary>
/// 
/// </summary>
class Converter
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="width">
	/// 
	/// </param>
	/// <param name="height">
	/// 
	/// </param>
	/// <param name="maxAngleX">
	/// 
	/// </param>
	/// <param name="maxAngleY">
	/// 
	/// </param>
	Converter(INT width, INT height, FLOAT maxAngleX, FLOAT maxAngleY);

	// Window coordinates
	/// <summary>
	/// 
	/// </summary>
	/// <param name="angle">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	INT ToCoordX(FLOAT angle);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="angle">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	INT ToCoordY(FLOAT angle);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="logCoord">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	INT ToCoordX_Log(INT logCoord) const;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="logCoord">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	INT ToCoordY_Log(INT logCoord) const;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="str">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	static POINT ToCoord(std::string str);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns><
	/// 
	/// /returns>
	POINT ToCoord(POINTFLOAT point);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="logPoint">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	POINT ToCoord(POINT logPoint);

	// Angle coordinates
	/// <summary>
	/// 
	/// </summary>
	/// <param name="coord">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	FLOAT ToAngleX(INT coord) const;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="coord">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	FLOAT ToAngleY(INT coord) const;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="logCoord">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	FLOAT ToAngleX_Log(INT logCoord) const;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="logCoord">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	FLOAT ToAngleY_Log(INT logCoord) const;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="str">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	POINTFLOAT ToAngle(std::string str);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	POINTFLOAT ToAngle(POINT point);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="logPoint">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	POINTFLOAT ToAngle_Log(POINT logPoint);

	// Logical coordinates
	/// <summary>
	/// 
	/// </summary>
	/// <param name="coord">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	INT ToLogCoordX(INT coord) const;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="coord">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	INT ToLogCoordY(INT coord) const;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="angle">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	INT ToLogCoordX_Angle(FLOAT angle);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="angle">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	INT ToLogCoordY_Angle(FLOAT angle);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	POINT ToLogCoord(POINTFLOAT point);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	POINT ToLogCoord(POINT point);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="str">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	POINT ToLogCoord(std::string str);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="str">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	POINT ToLogCoord_FromCoordString(std::string str);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="str">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	POINT ToLogCoord_FromAngleString(std::string str);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="str">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	POINT ToCoord_FromLogCoordString(std::string str);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="str">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	POINT ToCoord_FromAngleString(std::string str);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="str">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	POINTFLOAT ToAngle_FromLogCoordString(std::string str);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="str">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	POINTFLOAT ToAngle_FromCoordString(std::string str);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="radian">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	static FLOAT ToAngle_FromRadian(FLOAT radian);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="angle">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	static FLOAT ToRadian_FromAngle(FLOAT angle);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="radian">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	static POINTFLOAT ToAngle_FromRadian(POINTFLOAT radian);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="angle">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	static POINTFLOAT ToRadian_FromAngle(POINTFLOAT angle);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="hWnd">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	static FLOAT GetFloat_FromWindowText(HWND hWnd);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="str">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	static INT GetValue(std::string str);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="str">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	std::string ReplaceCommas(std::string str);
private:
	INT maxCoordX;
	INT maxCoordY;

	FLOAT maxAngleX;
	FLOAT maxAngleY;
	FLOAT angleWidth;
	FLOAT angleHeight;

	INT maxLogCoordX;
	INT maxLogCoordY;
};
