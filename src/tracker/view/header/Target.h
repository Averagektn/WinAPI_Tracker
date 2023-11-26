#pragma once

#include <windows.h>
#include "Circle.h"
#include <string>

class Target : public Circle
{
public:
	Target(int x, int y, int radius, RECT rect);
	Target(POINT center, int radius, RECT rect);
	Target(int x, int y, int radius);
	Target(POINT center, int radius);

	void SetCenter(POINT center);
	void SetDelay(int delay);

	int GetDelay() const;

private:
	int delay;
};
