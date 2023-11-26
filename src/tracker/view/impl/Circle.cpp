#include "../header/Circle.h"

Circle::Circle(int x, int y, int radius)
{
	center.x = x;
	center.y = y;
	this->radius = radius;
}

Circle::Circle(POINT center, int radius)
{
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

bool Circle::Contains(POINT point)
{
	double centerX = center.x;
	double centerY = center.x;
	double distance = sqrt(pow((point.x - centerX) / radius, 2) + pow((point.y - centerY) / radius, 2));

	return distance <= 1;
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

	if (brush != 0)
	{
		renderTarget->FillEllipse(ellipse, brush);
	}

	brush->Release();
}
