#pragma once

#include <windows.h>
#include "Circle.h"

class Target : public Circle
{
public:
	Target(int x, int y, int radius);
	Target(POINT center, int radius);

protected:

private:

};
