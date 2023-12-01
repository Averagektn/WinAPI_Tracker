#pragma once

#include <vector>
#include <string>
#include <d2d1.h>

#include "../../data/header/FileReader.h"
#include "../../calculations/header/Converter.h"

/// <summary>
///		Generates and draws path from given file with dataset. File format: "INT INT". Window coordinate system
/// </summary>
class PathDrawer
{
public:
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
	static VOID Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color, std::string reader);
};
