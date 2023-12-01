#pragma once

#include <windows.h>
#include <vector>

/// <summary>
///		Calculates numerical characteristics
/// </summary>
class Statistics
{
public:
	/// <summary>
	///		Calculates mathematical expectation
	/// </summary>
	/// <param name="points">
	///		Dataset
	/// </param>
	/// <returns>
	///		Mathematical expectation 
	/// </returns>
	static FLOAT MathExpectation(std::vector<POINT> points);

	/// <summary>
	///		Calculates standart deviation
	/// </summary>
	/// <param name="points">
	///		Dataset
	/// </param>
	/// <returns>	
	///		Standart deviation
	/// </returns>
	static FLOAT StandartDeviation(std::vector<POINT> points);

	/// <summary>
	///		Calculates dispersion
	/// </summary>
	/// <param name="points">
	///		Dataset
	/// </param>
	/// <returns>
	///		Dispersion
	/// </returns>
	static FLOAT Dispersion(std::vector<POINT> points);

	/// <summary>
	///		Calculates distance between two points
	/// </summary>
	/// <param name="p1">
	///		First point
	/// </param>
	/// <param name="p2">
	///		Second point
	/// </param>
	/// <returns>
	///		Distance
	/// </returns>
	static INT Distance(POINT p1, POINT p2);
};

