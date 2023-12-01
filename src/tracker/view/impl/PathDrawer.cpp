#include "../header/PathDrawer.h"

VOID PathDrawer::Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color, std::string filePath)
{
	FileReader reader(filePath);
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &brush);

	if (brush != NULL)
	{
		POINT prev{}, curr{};
		std::string newLine = reader.ReadLn();
		curr = Converter::ToCoord(newLine);
		while (!newLine.empty())
		{
			prev = curr;
			curr = Converter::ToCoord(newLine);

			renderTarget->DrawLine(D2D1::Point2<INT>(prev.x, prev.y), D2D1::Point2<INT>(curr.x, curr.y), brush);

			newLine = reader.ReadLn();
		}
	}

	brush->Release();
}
