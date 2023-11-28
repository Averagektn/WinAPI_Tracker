#pragma once

#include <windows.h>
#include <d2d1.h>

class Axis
{
public:
	Axis(INT xLeft, INT yLeft, INT xRight, INT yRight);
	Axis(POINT left, POINT right);

	VOID Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color);
protected:
	POINT left, right;
};
