#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <windows.h>

/// <summary>
///		Converter implementation
/// </summary>
class Converter
{
public:
	/// <summary>
	///		Creates converter
	/// </summary>
	/// <param name="width">
	///		Width of the screen
	/// </param>
	/// <param name="height">
	///		Height of the screen
	/// </param>
	/// <param name="maxAngleX">
	///		Width in angles
	/// </param>
	/// <param name="maxAngleY">
	///		Height in angles
	/// </param>
	Converter(INT width, INT height, FLOAT maxAngleX, FLOAT maxAngleY);

	// Window coordinates
	/// <summary>
	///		Converts to window coordinate system
	/// </summary>
	INT ToCoordX(FLOAT angle);
	/// <summary>
	///		Converts to window coordinate system
	/// </summary>
	INT ToCoordY(FLOAT angle);
	/// <summary>
	///		Converts to window coordinate system
	/// </summary>
	INT ToCoordX_Log(INT logCoord) const;
	/// <summary>
	///		Converts to window coordinate system
	/// </summary>
	INT ToCoordY_Log(INT logCoord) const;
	/// <summary>
	///		Converts to window coordinate system
	/// </summary>
	static POINT ToCoord(std::string str);
	/// <summary>
	///		Converts to window coordinate system
	/// </summary>
	POINT ToCoord(POINTFLOAT point);
	/// <summary>
	///		Converts to window coordinate system
	/// </summary>
	POINT ToCoord(POINT logPoint);
	/// <summary>
	///		Converts to window coordinate system
	/// </summary>
	POINT ToCoord_FromLogCoordString(std::string str);
	/// <summary>
	///		Converts to window coordinate system
	/// </summary>
	POINT ToCoord_FromAngleString(std::string str);

	// Angle coordinates
	/// <summary>
	///		Converts to angles
	/// </summary>
	FLOAT ToAngleX(INT coord) const;
	/// <summary>
	///		Converts to angles
	/// </summary>
	FLOAT ToAngleY(INT coord) const;
	/// <summary>
	///		Converts to angles
	/// </summary>
	FLOAT ToAngleX_Log(INT logCoord) const;
	/// <summary>
	///		Converts to angles
	/// </summary>
	FLOAT ToAngleY_Log(INT logCoord) const;
	/// <summary>
	///		Converts to angles
	/// </summary>
	POINTFLOAT ToAngle(std::string str);
	/// <summary>
	///		Converts to angles
	/// </summary>
	POINTFLOAT ToAngle(POINT point);
	/// <summary>
	///		Converts to angles
	/// </summary>
	POINTFLOAT ToAngle_Log(POINT logPoint);
	/// <summary>
	///		Converts to angles
	/// </summary>
	POINTFLOAT ToAngle_FromLogCoordString(std::string str);
	/// <summary>
	///		Converts to angles
	/// </summary>
	POINTFLOAT ToAngle_FromCoordString(std::string str);
	/// <summary>
	///		Converts to angles
	/// </summary>
	static FLOAT ToAngle_FromRadian(FLOAT radian);
	/// <summary>
	///		Converts to angles
	/// </summary>
	static POINTFLOAT ToAngle_FromRadian(POINTFLOAT radian);

	// Logical coordinates
	/// <summary>
	///		Converts to logical coordinates(center is in the window center)
	/// </summary>
	INT ToLogCoordX(INT coord) const;
	/// <summary>
	///		Converts to logical coordinates(center is in the window center)
	/// </summary>
	INT ToLogCoordY(INT coord) const;
	/// <summary>
	///		Converts to logical coordinates(center is in the window center)
	/// </summary>
	INT ToLogCoordX_Angle(FLOAT angle);
	/// <summary>
	///		Converts to logical coordinates(center is in the window center)
	/// </summary>
	INT ToLogCoordY_Angle(FLOAT angle);
	/// <summary>
	///		Converts to logical coordinates(center is in the window center)
	/// </summary>
	POINT ToLogCoord(POINTFLOAT point);
	/// <summary>
	///		Converts to logical coordinates(center is in the window center)
	/// </summary>
	POINT ToLogCoord(POINT point);
	/// <summary>
	///		Converts to logical coordinates(center is in the window center)
	/// </summary>
	POINT ToLogCoord(std::string str);
	/// <summary>
	///		Converts to logical coordinates(center is in the window center)
	/// </summary>
	POINT ToLogCoord_FromCoordString(std::string str);
	/// <summary>
	///		Converts to logical coordinates(center is in the window center)
	/// </summary>
	POINT ToLogCoord_FromAngleString(std::string str);

	// Radians
	/// <summary>
	///		Converts to radians
	/// </summary>
	static FLOAT ToRadian_FromAngle(FLOAT angle);
	/// <summary>
	///		Converts to radians
	/// </summary>
	static POINTFLOAT ToRadian_FromAngle(POINTFLOAT angle);

	/// <summary>
	///		Converts to float from control text
	/// </summary>
	static FLOAT GetFloat_FromWindowText(HWND hWnd);

	/// <summary>
	///		Converts to int from control text
	/// </summary>
	static INT GetValue(std::string str);

	/// <summary>
	///		Replaces commas in string
	/// </summary>
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
