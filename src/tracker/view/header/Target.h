#pragma once

#include <windows.h>
#include <string>

#include "Circle.h"

class Target : public Circle
{
public:
	Target(INT x, INT y, INT radius, RECT rect);
	Target(POINT center, INT radius, RECT rect);
	Target(INT x, INT y, INT radius);
	Target(POINT center, INT radius);

	VOID SetCenter(POINT center);
	VOID SetDelay(INT delay);

	INT GetDelay() const;
private:
	INT delay;
};
