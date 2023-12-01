#pragma once

#include <windows.h>
#include <vector>

/// <summary>
/// 
/// </summary>
class Statistics
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="points">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	static FLOAT MathExpectation(std::vector<POINT> points);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="points">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	static FLOAT StandartDeviation(std::vector<POINT> points);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="points">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	static FLOAT Dispersion(std::vector<POINT> points);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="p1">
	/// 
	/// </param>
	/// <param name="p2">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	static INT Distance(POINT p1, POINT p2);
};

