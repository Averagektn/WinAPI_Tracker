#include "PathDrawer.h"

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

void PathDrawer::Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color)
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
