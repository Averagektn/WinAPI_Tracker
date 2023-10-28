#include "PathDrawer.h"

void PathDrawer::Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color, std::vector<POINT> path)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &brush);

	for (int i = 0; i < path.size() - 1; i++)
	{
		renderTarget->DrawLine(D2D1::Point2<int>(path[i].x, path[i].y), 
			D2D1::Point2<int>(path[i + 1].x, path[i + 1].y), brush);
	}

	brush->Release();
}
