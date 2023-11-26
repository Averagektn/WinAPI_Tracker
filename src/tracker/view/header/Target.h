#pragma once

#include <windows.h>
#include "Circle.h"
#include <string>

class Target : public Circle
{
public:
	Target(int x, int y, int radius);
	Target(POINT center, int radius);
	void SetCenter(std::string);
	void SetCenter(POINT center);

	int GetDelay();

protected:

private:
	int delay;
};
