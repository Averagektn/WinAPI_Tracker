#pragma once

#include <windows.h>
#include <d2d1.h>

/// <summary>
///		Axis implementation
/// </summary>
class Axis
{
public:
	/// <summary>
	///		Initializes axis with specified starting and ending points
	/// </summary>
	/// <param name="xLeft">
	///		Starting point X coordinate
	/// </param>
	/// <param name="yLeft">
	///		Starting point Y coordinate
	/// </param>
	/// <param name="xRight">
	///		Ending point X coordinate
	/// </param>
	/// <param name="yRight">
	///		Ending point Y coordinate
	/// </param>
	Axis(INT xLeft, INT yLeft, INT xRight, INT yRight);
	/// <summary>
	///		Initializes axis with specified staring and ending points
	/// </summary>
	/// <param name="left">
	///		Starting point
	/// </param>
	/// <param name="right">
	///		Ending point
	/// </param>
	Axis(POINT left, POINT right);

	/// <summary>
	///		Draws axis
	/// </summary>
	/// <param name="renderTarget">
	///		Drawer
	/// </param>
	/// <param name="color">
	///		Color of the axis
	/// </param>
	VOID Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color);
private:
	POINT left, right;
};
