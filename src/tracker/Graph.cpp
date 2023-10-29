#include "Graph.h"

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

void Graph::DrawWindRose(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color, Converter converter, 
    int segmentsNum, int radius)
{
    std::vector<std::vector<double>> angles = GetClasses(segmentsNum);
    std::vector<POINT> nodes = GetGeometryPoints(angles, converter, segmentsNum, radius);

    ID2D1Factory* d2dFactory = nullptr;
    renderTarget->GetFactory(&d2dFactory);

    ID2D1PathGeometry* polygonGeometry = nullptr;
    d2dFactory->CreatePathGeometry(&polygonGeometry);

    ID2D1GeometrySink* polygonSink = nullptr;
    polygonGeometry->Open(&polygonSink);

    polygonSink->BeginFigure(D2D1::Point2F(nodes[0].x, nodes[0].y), D2D1_FIGURE_BEGIN_FILLED);

    for (size_t i = 1; i < nodes.size(); i++) 
    {
        polygonSink->AddLine(D2D1::Point2F(nodes[i].x, nodes[i].y));
    }

    polygonSink->EndFigure(D2D1_FIGURE_END_CLOSED);
    polygonSink->Close();
    polygonSink->Release();

    ID2D1SolidColorBrush* brush = nullptr;
    renderTarget->CreateSolidColorBrush(color, &brush);

    renderTarget->FillGeometry(polygonGeometry, brush);

    brush->Release();
    polygonGeometry->Release();
}

std::vector<std::vector<double>> Graph::GetClasses(int segmentsNum)
{
	std::vector<std::vector<double>> segments(segmentsNum);
	double angleDelta = 360.0f / segmentsNum;
	double angle;
	int part;

	for (int i = 0; i < points.size(); i++)
	{
		angle = GetAngle(points[i]);

        if (isnan(angle))
        {
            angle = 0;
        }

        part = static_cast<int>(angle / (360.0 / segmentsNum));
        segments[part].push_back(angle);
	}

    return segments;
}

std::vector<POINT> Graph::GetGeometryPoints(std::vector<std::vector<double>> angles, Converter converter,
    int segmentsNum, int radius)
{
    std::vector<POINT> res;

    int coeff = GetMaxLength(angles);

    double ang = 360.0f / segmentsNum / 2;
    double angleStep = 360.0f / segmentsNum;

    for (int i = 0; i < segmentsNum; i++)
    {
        double x = radius * cos(ToRadians(ang));
        x = x * (float)angles[i].size() / coeff;

        double y = radius * sin(ToRadians(ang));
        y = y * (float)angles[i].size() / coeff;

        x = converter.ToCoordX_Log((int)x);
        y = converter.ToCoordY_Log((int)y);

        res.push_back({ (int)x, (int)y });
        ang += angleStep;
    }

    return res;
}

double Graph::GetAngle(POINT point)
{
    double angle = atan2(static_cast<double>(point.y), static_cast<double>(point.x)) * (180.0 / 3.14);

    if (angle < 0) {
        angle += 360.0;
    }

    return angle;
}

int Graph::GetMaxLength(std::vector<std::vector<double>> angles)
{
    int res = angles[0].size();

    for (int i = 1; i < angles.size(); i++)
    {
        if (res < angles[i].size())
        {
            res = angles[i].size();
        }
    }

    return res;
}

double Graph::ToRadians(double angle)
{
    return angle * 3.14 / 180;
}
