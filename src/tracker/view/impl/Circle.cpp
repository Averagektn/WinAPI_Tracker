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
	this->radiusX = radius;
	this->radiusY = radius;
	this->oldRect = { 0,0,0,0 };
}

Circle::Circle(POINT center, int radius)
{
	oldRect = { 0,0,0,0 };
	this->center = center;
	this->radiusX = radius;
	this->radiusY = radius;
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

	radiusX *= xScale;
	radiusY *= yScale;

	oldRect = newRect;
}

bool Circle::Contains(POINT point)
{
	double centerX = center.x;
	double centerY = center.x;
	double distance = sqrt(pow((point.x - centerX) / radiusX, 2) + pow((point.y - centerY) / radiusY, 2));

	return distance <= 1;
}

int Circle::GetLeft() const
{
	return center.x - radiusX;
}

int Circle::GetTop() const
{
	return center.y - radiusY;
}

int Circle::GetBottom() const
{
	return center.y + radiusY;
}

int Circle::GetRight() const
{
	return center.x + radiusX;
}

POINT Circle::GetCenter() const
{
	return center;
}

void Circle::Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &brush);

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2<int>(center.x, center.y), radiusX, radiusY);

	if (brush != 0)
	{
		renderTarget->FillEllipse(ellipse, brush);
	}

	brush->Release();
}
