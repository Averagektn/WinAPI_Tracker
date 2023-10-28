#include "Cursor.h"

Cursor::Cursor(int x, int y, int radius)
{
	center.x = x;
	center.y = y;
	this->radius = radius;
}

Cursor::Cursor(POINT center, int radius)
{
	this->center = center;
	this->radius = radius;
}

void Cursor::SetCenterX(int x)
{
	center.x = x;
}

void Cursor::SetCenterY(int y)
{
	center.y = y;
}

void Cursor::AddCoordX(int dx)
{
	center.x += dx;
}

void Cursor::AddCoordY(int dy)
{
	center.y += dy;
}

void Cursor::SetCenter(POINT center)
{
	this->center = center;
}

int Cursor::GetLeft()
{
	return center.x - radius;
}

int Cursor::GetTop()
{
	return center.y - radius;
}

int Cursor::GetBottom()
{
	return center.y + radius;
}

int Cursor::GetRight()
{
	return center.x + radius;
}

POINT Cursor::GetCenter()
{
	return center;
}

void Cursor::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &brush);

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2(center.x, center.y), radius, radius);
	renderTarget->FillEllipse(ellipse, brush);

	brush->Release();
}
