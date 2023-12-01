#pragma once

#include <vector>
#include <string>
#include <d2d1.h>

#include "../../data/header/FileReader.h"
#include "../../calculations/header/Converter.h"

/// <summary>
/// 
/// </summary>
class PathDrawer
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
	PathDrawer(std::string filePath, Converter converter);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="reader">
	/// 
	/// </param>
	/// <param name="converter">
	/// 
	/// </param>
	PathDrawer(FileReader reader, Converter converter);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="path">
	/// 
	/// </param>
	PathDrawer(std::vector<POINT> path);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderTarget">
	/// 
	/// </param>
	/// <param name="color">
	/// 
	/// </param>
	/// <returns>
	/// 
	/// </returns>
	VOID Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color);
protected:
	std::vector<POINT> path;
};
