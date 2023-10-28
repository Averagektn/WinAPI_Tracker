#pragma once

#include <windows.h>
#include <gdiplus.h>
#include <d2d1.h>

class Cursor
{
public:
	Cursor(int x, int y, int radius);
	Cursor(POINT center, int radius);

	void Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color);
	void SetCenterX(int x);
	void SetCenterY(int y);
	void AddCoordX(int dx);
	void AddCoordY(int dy);
	void SetCenter(POINT center);

	int GetLeft();
	int GetTop();
	int GetBottom();
	int GetRight();

	POINT GetCenter();

protected:

private:
	POINT center;
	int radius;

};
