#include "../header/PathDrawer.h"

PathDrawer::PathDrawer(std::string filePath, Converter converter)
{
	FileReader reader(filePath);
	std::string line = reader.ReadLn();

	while (!line.empty())
	{
		path.push_back(converter.ToCoord_FromLogCoordString(line));
		line = reader.ReadLn();
	}
}

PathDrawer::PathDrawer(FileReader reader, Converter converter)
{
	std::string line = reader.ReadLn();

	while (!line.empty())
	{
		path.push_back(converter.ToCoord_FromLogCoordString(line));
		line = reader.ReadLn();
	}
}

PathDrawer::PathDrawer(std::vector<POINT> path)
{
	this->path = path;
}

VOID PathDrawer::Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color)
{
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &brush);

	for (INT i = 0; i < path.size() - 1; i++)
	{
		renderTarget->DrawLine(D2D1::Point2<INT>(path[i].x, path[i].y),
			D2D1::Point2<INT>(path[static_cast<std::vector<POINT, std::allocator<POINT>>::size_type>(i) + 1].x,
				path[static_cast<std::vector<POINT, std::allocator<POINT>>::size_type>(i) + 1].y), brush);
	}

	brush->Release();
}
