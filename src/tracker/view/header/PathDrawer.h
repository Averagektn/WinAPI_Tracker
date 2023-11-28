#pragma once

#include <vector>
#include <string>
#include <d2d1.h>

#include "../../data/header/FileReader.h"
#include "../../calculations/header/Converter.h"

class PathDrawer
{
public:
	PathDrawer(std::string filePath, Converter converter);
	PathDrawer(FileReader reader, Converter converter);
	PathDrawer(std::vector<POINT> path);

	void Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color);
protected:
	std::vector<POINT> path;
};
