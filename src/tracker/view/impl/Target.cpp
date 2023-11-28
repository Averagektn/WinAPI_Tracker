#include "../header/Target.h"

Target::Target(INT x, INT y, INT radius, RECT rect) : Circle(x, y, radius, rect)
{
	delay = INFINITE;
}

Target::Target(POINT center, INT radius, RECT rect) : Circle(center, radius, rect)
{
	delay = INFINITE;
}

Target::Target(INT x, INT y, INT radius) : Circle(x, y, radius)
{
	delay = INFINITE;
}

Target::Target(POINT center, INT radius) : Circle(center, radius)
{
	delay = INFINITE;
}

VOID Target::SetCenter(POINT center)
{
	Circle::SetCenter(center);
}

VOID Target::SetDelay(INT delay)
{
	this->delay = delay;
}

INT Target::GetDelay() const
{
	return delay;
}
