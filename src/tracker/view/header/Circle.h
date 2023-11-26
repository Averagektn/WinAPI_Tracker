#pragma once

#include <windows.h>
#include <d2d1.h>
#include <math.h>

class Circle
{
public:
	Circle(int x, int y, int radius, RECT rect);
	Circle(POINT center, int radius, RECT rect);
	Circle(int x, int y, int radius);
	Circle(POINT center, int radius);

	POINT GetCenter() const;

	bool Contains(POINT point);

	int GetLeft() const;
	int GetTop() const;
	int GetBottom() const;
	int GetRight() const;

	void Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color);
	void SetCenterX(int x);
	void SetCenterY(int y);
	void AddCoordX(int dx);
	void AddCoordY(int dy);
	void SetCenter(POINT center);
	void SetOldRect(RECT oldRect);
	RECT GetOldRect() const;

	void Scale(RECT newRect);

protected:
	RECT oldRect;
	POINT center;
	int radius;
};
