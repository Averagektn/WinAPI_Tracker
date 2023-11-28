#pragma once

#include <vector>
#include <cmath>
#include <d2d1.h>
#include <windows.h>

#include "../../data/header/FileReader.h"
#include "../../calculations/header/Converter.h"

class Graph
{
public:
	Graph(std::string filePath, Converter converter);
	Graph(FileReader reader, Converter converter);
	Graph(std::vector<POINT> points);

	VOID DrawWindRose(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color, Converter converter, INT segmentsNum,
		INT radius);
protected:
	std::vector<std::vector<DOUBLE>> GetClasses(INT segmentsNum);
	std::vector<POINT> GetGeometryPoints(std::vector<std::vector<DOUBLE>> angles, Converter converter,
		INT segmentsNum, INT radius);
	std::vector<POINT> points;

	DOUBLE GetAngle(POINT point);
private:
	INT GetMaxLength(std::vector<std::vector<DOUBLE>> angles);

	DOUBLE ToRadians(DOUBLE angle);
};
