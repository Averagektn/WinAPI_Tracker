#pragma once

#include <windows.h>
#include <d2d1.h>

#include "Circle.h"

/// <summary>
/// 
/// </summary>
class Cursor : public Circle
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x">
	/// 
	/// </param>
	/// <param name="y">
	/// 
	/// </param>
	/// <param name="radius">
	/// 
	/// </param>
	/// <param name="oldRect">
	/// 
	/// </param>
	/// <param name="speed">
	/// 
	/// </param>
	Cursor(INT x, INT y, INT radius, RECT oldRect, INT speed);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="center">
	/// 
	/// </param>
	/// <param name="radius">
	/// 
	/// </param>
	/// <param name="oldRect">
	/// 
	/// </param>
	/// <param name="speed">
	/// 
	/// </param>
	Cursor(POINT center, INT radius, RECT oldRect, INT speed);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="speed">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID SetSpeed(INT speed);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	INT GetSpeed() const;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="newRect">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID Scale(RECT newRect);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	POINT Shot() const;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="moveTop">
	/// 
	/// </param>
	/// <param name="moveRight">
	/// 
	/// </param>
	/// <param name="moveBottom">
	/// 
	/// </param>
	/// <param name="moveLeft">
	/// 
	/// </param>
	/// <param name="bounds">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID Move(BOOL moveTop, BOOL moveRight, BOOL moveBottom, BOOL moveLeft, RECT bounds);
private:
	INT speed;
	const FLOAT DIAGONAL_SPEED_CORRECTION = 1.41;
};
