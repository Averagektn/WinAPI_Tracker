#pragma once

#include <windows.h>
#include <string>

#include "Circle.h"

/// <summary>
///		Realization of target as a circle
/// </summary>
class Target : public Circle
{
public:
	/// <summary>
	///		Inititializes target with specified coordinates
	/// </summary>
	/// <param name="x">
	///		x coordinate
	/// </param>
	/// <param name="y">
	///		y coordinate
	/// </param>
	/// <param name="radius">
	///		radius of target circle
	/// </param>
	/// <param name="rect">
	///		rectangle which specifies bounds of the playing zone 
	/// </param>
	Target(INT x, INT y, INT radius, RECT rect);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="center">
	/// 
	/// </param>
	/// <param name="radius">
	/// 
	/// </param>
	/// <param name="rect">
	/// 
	/// </param>
	Target(POINT center, INT radius, RECT rect);

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
	Target(INT x, INT y, INT radius);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="center">
	/// 
	/// </param>
	/// <param name="radius">
	/// 
	/// </param>
	Target(POINT center, INT radius);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="center">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID SetCenter(POINT center);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="delay">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID SetDelay(INT delay);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	INT GetDelay() const;
private:
	INT delay;
};
