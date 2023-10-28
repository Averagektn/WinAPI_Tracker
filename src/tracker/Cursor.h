#pragma once

#include <windows.h>
#include <d2d1.h>
#include "Circle.h"

class Cursor : public Circle
{
public:
	Cursor(int x, int y, int radius);
	Cursor(POINT center, int radius);
	POINT Shot();

protected:

private:

};
