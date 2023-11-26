#pragma once

#include <windows.h>
#include <vector>

class Statistics
{
public:
	static float MathExpectation(std::vector<POINT> points);
	static float StandartDeviation(std::vector<POINT> points);
	static float Dispersion(std::vector<POINT> points);

	static int Distance(POINT p1, POINT p2);
};

