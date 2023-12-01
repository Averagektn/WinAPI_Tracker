#pragma once

#include <windows.h>
#include <d2d1.h>

#include "Circle.h"

/// <summary>
///		Implementation of user cursor
/// </summary>
class Cursor : public Circle
{
public:
	/// <summary>
	///		Initializes circle with specified center, speed and radius
	/// </summary>
	/// <param name="x">
	///		x coordnate
	/// </param>
	/// <param name="y">
	///		y coordinate
	/// </param>
	/// <param name="radius">
	///		Radius
	/// </param>
	/// <param name="oldRect">
	///		Bounds. For scaling
	/// </param>
	/// <param name="speed">
	///		Circle speed
	/// </param>
	Cursor(INT x, INT y, INT radius, RECT oldRect, INT speed);

	/// <summary>
	///		Initializes circle with specified center, speed and radius
	/// </summary>
	/// <param name="center">
	///		Cursor circle center
	/// </param>
	/// <param name="radius">
	///		Radius
	/// </param>
	/// <param name="oldRect">
	///		Bounds. For scaling
	/// </param>
	/// <param name="speed">
	///		Circle speed
	/// </param>
	Cursor(POINT center, INT radius, RECT oldRect, INT speed);

	/// <summary>
	///		Sets new speed
	/// </summary>
	/// <param name="speed">
	///		New speed
	/// </param>
	VOID SetSpeed(INT speed);

	/// <summary>
	///		Returns current speed
	/// </summary>
	/// <returns>
	///		Speed
	/// </returns>
	INT GetSpeed() const;

	/// <summary>
	///		Scales speed and radius. Moves center
	/// </summary>
	/// <param name="newRect">
	///		Resolution to scale
	/// </param>
	VOID Scale(RECT newRect);

	/// <summary>
	///		Same as GetCenter. Just semantic)
	/// </summary>
	/// <returns>
	///		Coordinate of the shot
	/// </returns>
	POINT Shot() const;

	/// <summary>
	///		Moves cursor to specified direction
	/// </summary>
	/// <param name="moveTop">
	///		Move up?
	/// </param>
	/// <param name="moveRight">
	///		Move right?
	/// </param>
	/// <param name="moveBottom">
	///		Move down?
	/// </param>
	/// <param name="moveLeft">
	///		Move left?
	/// </param>
	/// <param name="bounds">
	///		Rectangle bounds
	/// </param>
	VOID Move(BOOL moveTop, BOOL moveRight, BOOL moveBottom, BOOL moveLeft, RECT bounds);
private:
	INT speed;
	const FLOAT DIAGONAL_SPEED_CORRECTION = 1.41;
};
