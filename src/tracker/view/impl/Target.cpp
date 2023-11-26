#include "../header/Target.h"

Target::Target(int x, int y, int radius, RECT rect) : Circle(x, y, radius, rect)
{
	delay = INFINITE;
}

Target::Target(POINT center, int radius, RECT rect) : Circle(center, radius, rect)
{
	delay = INFINITE;
}

Target::Target(int x, int y, int radius) : Circle(x, y, radius)
{  
	delay = INFINITE;
}

Target::Target(POINT center, int radius) : Circle(center, radius) 
{  
	delay = INFINITE;
}

void Target::SetCenter(POINT center)
{
	Circle::SetCenter(center);
}

void Target::SetDelay(int delay)
{
	this->delay = delay;
}

int Target::GetDelay() const
{
	return delay;
}
