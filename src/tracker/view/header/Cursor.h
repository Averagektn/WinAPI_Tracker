#pragma once

#include <windows.h>
#include <d2d1.h>
#include "Circle.h"

class Cursor : public Circle
{
public:
	Cursor(int x, int y, int radius, RECT oldRect);
	Cursor(POINT center, int radius, RECT oldRect);

	POINT Shot() const;
};
