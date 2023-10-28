#pragma once

#include <vector>
#include <d2d1.h>

class PathDrawer
{
public:
	static void Draw(ID2D1HwndRenderTarget* renderTarget, D2D1::ColorF color, std::vector<POINT> path);

protected:

private:

};
