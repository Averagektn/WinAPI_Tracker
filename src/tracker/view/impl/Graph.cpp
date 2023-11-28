#include "../header/Graph.h"

Graph::Graph(std::string filePath, Converter converter)
{
	FileReader reader(filePath);
	std::string line = reader.ReadLn();

	while (!line.empty())
	{
		points.push_back(converter.ToLogCoord(line));
		line = reader.ReadLn();
	}
}

Graph::Graph(FileReader reader, Converter converter)
{
	std::string line = reader.ReadLn();

	while (!line.empty())
	{
		points.push_back(converter.ToCoord_FromLogCoordString(line));
		line = reader.ReadLn();
	}
}

Graph::Graph(std::vector<POINT> points)
{
	this->points = points;
}

VOID Graph::DrawWindRose(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color, Converter converter, INT segmentsNum,
	INT radius)
{
	std::vector<std::vector<DOUBLE>> angles = GetClasses(segmentsNum);
	std::vector<POINT> nodes = GetGeometryPoints(angles, converter, segmentsNum, radius);

	ID2D1Factory* d2dFactory = NULL;
	renderTarget->GetFactory(&d2dFactory);

	ID2D1PathGeometry* polygonGeometry = NULL;
	d2dFactory->CreatePathGeometry(&polygonGeometry);

	ID2D1GeometrySink* polygonSink = NULL;
	polygonGeometry->Open(&polygonSink);

	polygonSink->BeginFigure(D2D1::Point2F(nodes[0].x, nodes[0].y), D2D1_FIGURE_BEGIN_FILLED);

	for (size_t i = 1; i < nodes.size(); i++)
	{
		polygonSink->AddLine(D2D1::Point2F(nodes[i].x, nodes[i].y));
	}

	polygonSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	polygonSink->Close();
	polygonSink->Release();

	ID2D1SolidColorBrush* brush = NULL;
	renderTarget->CreateSolidColorBrush(color, &brush);

	if (polygonGeometry != NULL && brush != NULL)
	{
		renderTarget->FillGeometry(polygonGeometry, brush);
	}

	brush->Release();
	polygonGeometry->Release();
}

std::vector<std::vector<DOUBLE>> Graph::GetClasses(INT segmentsNum)
{
	std::vector<std::vector<DOUBLE>> segments(segmentsNum);
	DOUBLE angleDelta = 360.0f / segmentsNum;
	DOUBLE angle;
	INT part;

	for (INT i = 0; i < points.size(); i++)
	{
		angle = GetAngle(points[i]);

		if (isnan(angle))
		{
			angle = 0;
		}

		part = static_cast<INT>(angle / (360.0 / segmentsNum));
		segments[part].push_back(angle);
	}

	return segments;
}

std::vector<POINT> Graph::GetGeometryPoints(std::vector<std::vector<DOUBLE>> angles, Converter converter,
	INT segmentsNum, INT radius)
{
	std::vector<POINT> res;

	INT coeff = GetMaxLength(angles);

	DOUBLE ang = 360.0f / segmentsNum / 2;
	DOUBLE angleStep = 360.0f / segmentsNum;

	for (INT i = 0; i < segmentsNum; i++)
	{
		DOUBLE x = radius * cos(ToRadians(ang));
		x *= (FLOAT)angles[i].size() / coeff;

		DOUBLE y = radius * sin(ToRadians(ang));
		y *= (FLOAT)angles[i].size() / coeff;

		x = converter.ToCoordX_Log((INT)x);
		y = converter.ToCoordY_Log((INT)y);

		res.push_back({ (INT)x, (INT)y });
		ang += angleStep;
	}

	return res;
}

DOUBLE Graph::GetAngle(POINT point)
{
	DOUBLE angle = atan2(static_cast<DOUBLE>(point.y), static_cast<DOUBLE>(point.x)) * (180.0 / 3.14);

	if (angle < 0) 
	{
		angle += 360.0;
	}

	return angle;
}

INT Graph::GetMaxLength(std::vector<std::vector<DOUBLE>> angles)
{
	INT res = angles[0].size();

	for (INT i = 1; i < angles.size(); i++)
	{
		if (res < angles[i].size())
		{
			res = angles[i].size();
		}
	}

	return res;
}

DOUBLE Graph::ToRadians(DOUBLE angle)
{
	return angle * 3.14 / 180;
}
