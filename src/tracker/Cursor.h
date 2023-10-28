#pragma once

#include <windows.h>
#include <gdiplus.h>

class Cursor
{
public:
	Cursor(Gdiplus::Color color, int x, int y, int diameter);
	Cursor(Gdiplus::Color color, POINT center, int diameter);
	void Draw(HDC hdc);
	void SetX(int x);
	void SetY(int y);
	void SetCenter(POINT center);
	int GetLeft();
	int GetTop();
	int GetBottom();
	int GetRight();
	POINT GetCenter();

protected:
	Gdiplus::Rect GetDrawingRect();
private:
	POINT center;
	Gdiplus::Color color;
	int diameter;

};

