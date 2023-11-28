#pragma once

#include <windows.h>
#include <d2d1.h>
#include <cmath>

class Circle
{
public:
	Circle(INT x, INT y, INT radius, RECT rect);
	Circle(POINT center, INT radius, RECT rect);
	Circle(INT x, INT y, INT radius);
	Circle(POINT center, INT radius);

	POINT GetCenter() const;

	BOOL Contains(POINT point);

	INT GetLeft() const;
	INT GetTop() const;
	INT GetBottom() const;
	INT GetRight() const;

	VOID Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color);
	VOID SetCenterX(INT x);
	VOID SetCenterY(INT y);
	VOID AddCoordX(INT dx);
	VOID AddCoordY(INT dy);
	VOID SetCenter(POINT center);
	VOID SetOldRect(RECT oldRect);

	RECT GetOldRect() const;

	VOID Scale(RECT newRect);
protected:
	RECT oldRect;
	POINT center;
	INT radius;
};
