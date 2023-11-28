#include "../header/Axis.h"

Axis::Axis(int xLeft, int yLeft, int xRight, int yRight)
{
	left.x = xLeft;
	left.y = yLeft;

	right.x = xRight;
	right.y = yRight;
}

Axis::Axis(POINT left, POINT right)
{
	this->left = left;
	this->right = right;
}

void Axis::Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &brush);

	if (brush != NULL)
	{
		renderTarget->DrawLine(D2D1::Point2<int>(left.x, left.y), D2D1::Point2<int>(right.x, right.y), brush);
	}

	brush->Release();
}
