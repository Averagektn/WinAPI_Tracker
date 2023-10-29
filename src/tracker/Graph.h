#pragma once

#include <vector>
#include <cmath>
#include <d2d1.h>
#include <windows.h>

#include "FileReader.h"
#include "Converter.h"

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
	double GetAngle(POINT point);
	std::vector<POINT> points;

private:
	int GetMaxLength(std::vector<std::vector<double>> angles);
	double ToRadians(double angle);

};
