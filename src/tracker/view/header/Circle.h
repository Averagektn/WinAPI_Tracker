#pragma once

#include <windows.h>
#include <d2d1.h>
#include <cmath>

/// <summary>
/// 
/// </summary>
class Circle
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
	/// <param name="rect">
	/// 
	/// </param>
	Circle(INT x, INT y, INT radius, RECT rect);
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
	Circle(POINT center, INT radius, RECT rect);
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
	Circle(INT x, INT y, INT radius);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="center">
	/// 
	/// </param>
	/// <param name="radius">
	/// 
	/// </param>
	Circle(POINT center, INT radius);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	POINT GetCenter() const;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	BOOL Contains(POINT point);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	INT GetLeft() const;
	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	INT GetTop() const;
	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	INT GetBottom() const;
	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	INT GetRight() const;

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

	/// <summary>
	/// 
	/// </summary>
	/// <param name="x">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID SetCenterX(INT x);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="y">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID SetCenterY(INT y);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="dx">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID AddCoordX(INT dx);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="dy">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID AddCoordY(INT dy);
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
	/// <param name="oldRect">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID SetOldRect(RECT oldRect);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>
	/// 
	/// </returns>
	RECT GetOldRect() const;

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
protected:
	RECT oldRect;
	POINT center;
	INT radius;
};
