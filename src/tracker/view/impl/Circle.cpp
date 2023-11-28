#include "../header/Circle.h"

Circle::Circle(int x, int y, int radius, RECT rect) : Circle::Circle(x, y, radius)
{
	oldRect = rect;
}

Circle::Circle(POINT center, int radius, RECT rect) : Circle::Circle(center, radius)
{
	oldRect = rect;
}

Circle::Circle(int x, int y, int radius)
{
	center.x = x;
	center.y = y;

	this->radius = radius;

	this->oldRect = { 0,0,0,0 };
}

Circle::Circle(POINT center, int radius)
{
	oldRect = { 0,0,0,0 };

	this->center = center;
	this->radius = radius;
}

void Circle::SetCenterX(int x)
{
	center.x = x;
}

void Circle::SetCenterY(int y)
{
	center.y = y;
}

void Circle::AddCoordX(int dx)
{
	center.x += dx;
}

void Circle::AddCoordY(int dy)
{
	center.y += dy;
}

void Circle::SetCenter(POINT center)
{
	this->center = center;
}

void Circle::SetOldRect(RECT oldRect)
{
	this->oldRect = oldRect;
}

RECT Circle::GetOldRect() const
{
	return oldRect;
}

void Circle::Scale(RECT newRect)
{
	float xScale = (float)newRect.right / oldRect.right;
	float yScale = (float)newRect.bottom / oldRect.bottom;

	this->SetCenter({ (int)(center.x * xScale), (int)(center.y * yScale) });

	radius *= (xScale + yScale) / 2;

	oldRect = newRect;
}

bool Circle::Contains(POINT point)
{
	float result = std::pow((static_cast<float>(point.x) - center.x) / radius, 2) +
		std::pow((static_cast<float>(point.y) - center.y) / radius, 2);

	return result <= 1.0f;
}

int Circle::GetLeft() const
{
	return center.x - radius;
}

int Circle::GetTop() const
{
	return center.y - radius;
}

int Circle::GetBottom() const
{
	return center.y + radius;
}

int Circle::GetRight() const
{
	return center.x + radius;
}

POINT Circle::GetCenter() const
{
	return center;
}

void Circle::Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &brush);

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2<int>(center.x, center.y), radius, radius);

	if (brush != NULL)
	{
		renderTarget->FillEllipse(ellipse, brush);
	}

	brush->Release();
}
