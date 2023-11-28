#pragma once

#include <windows.h>
#include <d2d1.h>
#include "Circle.h"

class Cursor : public Circle
{
public:
	Cursor(INT x, INT y, INT radius, RECT oldRect);
	Cursor(POINT center, INT radius, RECT oldRect);

	POINT Shot() const;
};
