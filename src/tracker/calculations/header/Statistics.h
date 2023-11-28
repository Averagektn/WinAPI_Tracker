#pragma once

#include <windows.h>
#include <vector>

class Statistics
{
public:
	static FLOAT MathExpectation(std::vector<POINT> points);
	static FLOAT StandartDeviation(std::vector<POINT> points);
	static FLOAT Dispersion(std::vector<POINT> points);

	static INT Distance(POINT p1, POINT p2);
};

