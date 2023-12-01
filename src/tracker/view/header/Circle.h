#pragma once

#include <windows.h>
#include <d2d1.h>
#include <cmath>

/// <summary>
///		Circle implemetation
/// </summary>
class Circle
{
public:
	/// <summary>
	///		Initializes circle with specified center, radius and rectangle
	/// </summary>
	/// <param name="x">
	///		X coordinate
	/// </param>
	/// <param name="y">
	///		Y coordinate
	/// </param>
	/// <param name="radius">
	///		Radius
	/// </param>
	/// <param name="rect">
	///		Bounds. For scaling
	/// </param>
	Circle(INT x, INT y, INT radius, RECT rect);
	/// <summary>
	///		Initilizes circle with specified center, radius and rectangle
	/// </summary>
	/// <param name="center">
	///		Center of the circle
	/// </param>
	/// <param name="radius">
	///		Radius
	/// </param>
	/// <param name="rect">
	///		Bounds. For scaling
	/// </param>
	Circle(POINT center, INT radius, RECT rect);
	/// <summary>
	///		Initializes circle with specified center, radius and rectangle. Bounds are: 0, 0, 0, 0
	/// </summary>
	/// <param name="x">
	///		X coordinate
	/// </param>
	/// <param name="y">
	///		Y coordinate
	/// </param>
	/// <param name="radius">
	///		Radius
	/// </param>
	Circle(INT x, INT y, INT radius);
	/// <summary>
	///		Initilizes circle with specified center, radius and rectangle. Bounds are: 0, 0, 0, 0
	/// </summary>
	/// <param name="center">
	///		Center of the circle
	/// </param>
	/// <param name="radius">
	///		Radius
	/// </param>
	Circle(POINT center, INT radius);

	/// <summary>
	///		Returns center
	/// </summary>
	/// <returns>
	///		Center
	/// </returns>
	POINT GetCenter() const;

	/// <summary>
	///		Checks if circle contains point
	/// </summary>
	/// <param name="point">
	///		Point to verify
	/// </param>
	/// <returns>
	///		TRUE is contains
	/// </returns>
	BOOL Contains(POINT point);

	/// <summary>
	///		Returns left border
	/// </summary>
	/// <returns>
	///		Left border
	/// </returns>
	INT GetLeft() const;
	/// <summary>
	///		Returns top border
	/// </summary>
	/// <returns>
	///		Top border
	/// </returns>
	INT GetTop() const;
	/// <summary>
	///		Returns bottom border
	/// </summary>
	/// <returns>
	///		Bottom border
	/// </returns>
	INT GetBottom() const;
	/// <summary>
	///		Returns right border
	/// </summary>
	/// <returns>
	///		Right border
	/// </returns>
	INT GetRight() const;

	/// <summary>
	///		Draws circle
	/// </summary>
	/// <param name="renderTarget">
	///		Drawer
	/// </param>
	/// <param name="color">
	///		Cursor color
	/// </param>
	VOID Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color);

	/// <summary>
	///		Sets x coordinate
	/// </summary>
	/// <param name="x">
	///		X coordinate
	/// </param>
	VOID SetCenterX(INT x);
	/// <summary>
	///		Sets y coordinate
	/// </summary>
	/// <param name="y">
	///		Y coordinate
	/// </param>
	VOID SetCenterY(INT y);
	/// <summary>
	///		Adds value to coord x
	/// </summary>
	/// <param name="dx">
	///		Value to add
	/// </param>
	VOID AddCoordX(INT dx);
	/// <summary>
	///		Adds value to coord y
	/// </summary>
	/// <param name="dy">
	///		Value to add
	/// </param>
	VOID AddCoordY(INT dy);
	/// <summary>
	///		Sets new center
	/// </summary>
	/// <param name="center">
	///		New center
	/// </param>
	VOID SetCenter(POINT center);
	/// <summary>
	///		Sets bounds rectangle
	/// </summary>
	/// <param name="oldRect">
	///		Rectangle to set
	/// </param>
	VOID SetOldRect(RECT oldRect);

	/// <summary>
	///		Returns bounds rectangle
	/// </summary>
	/// <returns>
	///		Bounds rectangle
	/// </returns>
	RECT GetOldRect() const;

	/// <summary>
	///		Scales circle 
	/// </summary>
	/// <param name="newRect">
	///		Resolution to scale
	/// </param>
	VOID Scale(RECT newRect);
protected:
	RECT oldRect;
	POINT center;
	INT radius;
};
