#include "Cursor.h"

Cursor::Cursor(Gdiplus::Color color, int left, int top, int diameter)
{
	this->color = color;
	center.x = left - diameter / 2;
	center.y = top - diameter / 2;
	this->diameter = diameter;
}

Cursor::Cursor(Gdiplus::Color color, POINT leftTop, int diameter)
{
	this->color = color;
	this->center = { leftTop.x - diameter / 2, leftTop.y - diameter / 2};
	this->diameter = diameter;
}

void Cursor::Draw(HDC hdc)
{
	Gdiplus::Graphics graphics(hdc);
	Gdiplus::Pen pen(color);
	Gdiplus::SolidBrush brush(color);

	graphics.DrawEllipse(&pen, GetDrawingRect());
	graphics.FillEllipse(&brush, GetDrawingRect());
}

void Cursor::SetX(int x)
{
	center.x = x;
}

void Cursor::SetY(int y)
{
	center.y = y;
}

void Cursor::SetCenter(POINT center)
{
	this->center = center;
}

int Cursor::GetLeft()
{
	return center.x - diameter / 2;
}

int Cursor::GetTop()
{
	return center.y - diameter / 2;
}

int Cursor::GetBottom()
{
	return center.y + diameter / 2;
}

int Cursor::GetRight()
{
	return center.x + diameter / 2;
}

POINT Cursor::GetCenter()
{
	return { center.x + diameter / 2, center.y + diameter / 2 };
}

Gdiplus::Rect Cursor::GetDrawingRect()
{
	return Gdiplus::Rect(center.x, center.y, diameter, diameter);
}
