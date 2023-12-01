#pragma once

#include <windows.h>
#include <d2d1.h>

/// <summary>
/// 
/// </summary>
class Axis
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="xLeft">
	/// 
	/// </param>
	/// <param name="yLeft">
	/// 
	/// </param>
	/// <param name="xRight">
	/// 
	/// </param>
	/// <param name="yRight">
	/// 
	/// </param>
	Axis(INT xLeft, INT yLeft, INT xRight, INT yRight);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="left">
	/// 
	/// </param>
	/// <param name="right">
	/// 
	/// </param>
	Axis(POINT left, POINT right);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderTarget">
	/// 
	/// </param>
	/// <param name="color">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color);
private:
	POINT left, right;
};
