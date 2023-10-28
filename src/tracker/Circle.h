#pragma once

#include <windows.h>
#include <d2d1.h>

class Circle
{
public:
	Circle(int x, int y, int radius);
	Circle(POINT center, int radius);

	void Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color);
	void SetCenterX(int x);
	void SetCenterY(int y);
	void AddCoordX(int dx);
	void AddCoordY(int dy);
	void SetCenter(POINT center);

	bool Contains(POINT point);

	int GetLeft();
	int GetTop();
	int GetBottom();
	int GetRight();

	POINT GetCenter();

protected:
	POINT center;
	int radius;

private:

};
