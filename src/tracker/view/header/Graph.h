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

	void DrawWindRose(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color, Converter converter, 
		int segmentsNum, int radius);

protected:
	std::vector<std::vector<double>> GetClasses(int segmentsNum);
	std::vector<POINT> GetGeometryPoints(std::vector<std::vector<double>> angles, Converter converter,
		int segmentsNum, int radius);

	double GetAngle(POINT point);
	
	std::vector<POINT> points;
	

private:
	int GetMaxLength(std::vector<std::vector<double>> angles);

	double ToRadians(double angle);

};
