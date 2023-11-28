#pragma once

#include <windows.h>
#include <d2d1.h>

class Axis
{
public:
	Axis(int xLeft, int yLeft, int xRight, int yRight);
	Axis(POINT left, POINT right);

	void Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color);
protected:
	POINT left, right;
};
