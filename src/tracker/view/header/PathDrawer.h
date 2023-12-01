#pragma once

#include <vector>
#include <string>
#include <d2d1.h>

#include "../../data/header/FileReader.h"
#include "../../calculations/header/Converter.h"

/// <summary>
///		Generates and draws path from given file with dataset. File format: "INT INT\n". Window coordinate system
/// </summary>
class PathDrawer
{
public:
	/// <summary>
	///		Draws path from file
	/// </summary>
	/// <param name="renderTarget">
	///		Drawer
	/// </param>
	/// <param name="color">
	///		Path color
	/// </param>
	static VOID Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color, std::string reader);
};
