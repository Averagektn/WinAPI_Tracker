#include "../header/Circle.h"

Circle::Circle(INT x, INT y, INT radius, RECT rect) : Circle::Circle(x, y, radius)
{
	oldRect = rect;
}

Circle::Circle(POINT center, INT radius, RECT rect) : Circle::Circle(center, radius)
{
	oldRect = rect;
}

Circle::Circle(INT x, INT y, INT radius)
{
	center.x = x;
	center.y = y;

	this->radius = radius;

	this->oldRect = { 0,0,0,0 };
}

Circle::Circle(POINT center, INT radius)
{
	oldRect = { 0,0,0,0 };

	this->center = center;
	this->radius = radius;
}

VOID Circle::SetCenterX(INT x)
{
	center.x = x;
}

VOID Circle::SetCenterY(INT y)
{
	center.y = y;
}

VOID Circle::AddCoordX(INT dx)
{
	center.x += dx;
}

VOID Circle::AddCoordY(INT dy)
{
	center.y += dy;
}

VOID Circle::SetCenter(POINT center)
{
	this->center = center;
}

VOID Circle::SetOldRect(RECT oldRect)
{
	this->oldRect = oldRect;
}

RECT Circle::GetOldRect() const
{
	return oldRect;
}

VOID Circle::Scale(RECT newRect)
{
	FLOAT xScale = (FLOAT)newRect.right / oldRect.right;
	FLOAT yScale = (FLOAT)newRect.bottom / oldRect.bottom;

	this->SetCenter({ (INT)(center.x * xScale), (INT)(center.y * yScale) });

	radius *= (xScale + yScale) / 2;

	oldRect = newRect;
}

BOOL Circle::Contains(POINT point)
{
	FLOAT result = std::pow((static_cast<FLOAT>(point.x) - center.x) / radius, 2) +
		std::pow((static_cast<FLOAT>(point.y) - center.y) / radius, 2);

	return result <= 1.0f;
}

INT Circle::GetLeft() const
{
	return center.x - radius;
}

INT Circle::GetTop() const
{
	return center.y - radius;
}

INT Circle::GetBottom() const
{
	return center.y + radius;
}

INT Circle::GetRight() const
{
	return center.x + radius;
}

POINT Circle::GetCenter() const
{
	return center;
}

VOID Circle::Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &brush);

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2<INT>(center.x, center.y), radius, radius);

	if (brush != NULL)
	{
		renderTarget->FillEllipse(ellipse, brush);
	}

	brush->Release();
}
