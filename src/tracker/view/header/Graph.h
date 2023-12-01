#pragma once

#include <vector>
#include <cmath>
#include <d2d1.h>
#include <windows.h>

#include "../../data/header/FileReader.h"
#include "../../calculations/header/Converter.h"

/// <summary>
/// 
/// </summary>
class Graph
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="filePath">
	/// 
	/// </param>
	/// <param name="converter">
	/// 
	/// </param>
	Graph(std::string filePath, Converter converter);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="reader">
	/// 
	/// </param>
	/// <param name="converter">
	/// 
	/// </param>
	Graph(FileReader reader, Converter converter);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="points">
	/// 
	/// </param>
	Graph(std::vector<POINT> points);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderTarget">
	/// 
	/// </param>
	/// <param name="color">
	/// 
	/// </param>
	/// <param name="converter">
	/// 
	/// </param>
	/// <param name="segmentsNum">
	/// 
	/// </param>
	/// <param name="radius">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID DrawWindRose(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color, Converter converter, INT segmentsNum,
		INT radius);
private:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="segmentsNum">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	std::vector<std::vector<DOUBLE>> GetClasses(INT segmentsNum);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="angles">
	/// 
	/// </param>
	/// <param name="converter">
	/// 
	/// </param>
	/// <param name="segmentsNum">
	/// 
	/// </param>
	/// <param name="radius">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	std::vector<POINT> GetGeometryPoints(std::vector<std::vector<DOUBLE>> angles, Converter converter,
		INT segmentsNum, INT radius);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="point">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	DOUBLE GetAngle(POINT point);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="angles">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	INT GetMaxLength(std::vector<std::vector<DOUBLE>> angles);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="angle">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	DOUBLE ToRadians(DOUBLE angle);

	std::vector<POINT> points;
};
