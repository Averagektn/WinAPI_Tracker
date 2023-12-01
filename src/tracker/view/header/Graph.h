#pragma once

#include <vector>
#include <cmath>
#include <d2d1.h>
#include <windows.h>

#include "../../data/header/FileReader.h"
#include "../../calculations/header/Converter.h"

/// <summary>
///		Draws wind rose by provided dataset. WARNING: (0, 0) coordinate belongs to top left quater(fro 4 part wind rose)
/// </summary>
class Graph
{
public:
	/// <summary>
	///		Initializaes drawer
	/// </summary>
	/// <param name="filePath">
	///		Dataset
	/// </param>
	/// <param name="converter">
	///		Converter to receive coordinates
	/// </param>
	Graph(std::string filePath, Converter converter);

	/// <summary>
	///		Initializaes drawer
	/// </summary>
	/// <param name="filePath">
	///		Dataset provider
	/// </param>
	/// <param name="converter">
	///		Converter to receive coordinates
	/// </param>
	Graph(FileReader reader, Converter converter);

	/// <summary>
	/// 	Initializaes drawer
	/// </summary>
	/// <param name="points">
	///		Dataset
	/// </param>
	Graph(std::vector<POINT> points);

	/// <summary>
	///		Draws wind rose
	/// </summary>
	/// <param name="renderTarget">
	///		Drawer
	/// </param>
	/// <param name="color">
	///		Wind rose area color
	/// </param>
	/// <param name="converter">
	///		Coordinate converter
	/// </param>
	/// <param name="segmentsNum">
	///		Number of wind rose nodes
	/// </param>
	/// <param name="radius">
	///		Wind rose radius
	/// </param>
	VOID DrawWindRose(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color, Converter converter, INT segmentsNum,
		INT radius);
private:
	/// <summary>
	///		Returns points divided into classes according to their coordinates. 
	///		Point coordinate is converted into polar coordinate atnd then divided depending on it's angle
	/// </summary>
	/// <param name="segmentsNum">
	///		Number of classes
	/// </param>
	/// <returns>
	///		Classes of points. Points are in polar coordiantes
	/// </returns>
	std::vector<std::vector<DOUBLE>> GetClasses(INT segmentsNum);

	/// <summary>
	///		Calculates coordinates of wind rose nodes
	/// </summary>
	/// <param name="angles">
	///		Angles list
	/// </param>
	/// <param name="converter">
	///		Converter to logical(center is screen center) coordinates
	/// </param>
	/// <param name="segmentsNum">
	///		Number of nodes
	/// </param>
	/// <param name="radius">
	///		Wind rose radius
	/// </param>
	/// <returns>
	///		Points in logical coordinates
	/// </returns>
	std::vector<POINT> GetGeometryPoints(std::vector<std::vector<DOUBLE>> angles, Converter converter,
		INT segmentsNum, INT radius);

	/// <summary>
	///		Conveter to polar coordiantes
	/// </summary>
	/// <param name="point">
	///		Point ro convert
	/// </param>
	/// <returns>
	///		It's polar angle
	/// </returns>
	DOUBLE GetAngle(POINT point);

	/// <summary>
	///		Finds the biggest class length
	/// </summary>
	/// <param name="angles">
	///		Classes
	/// </param>
	/// <returns>
	///		Biggest class length
	/// </returns>
	INT GetMaxLength(std::vector<std::vector<DOUBLE>> angles);

	std::vector<POINT> points;
};
