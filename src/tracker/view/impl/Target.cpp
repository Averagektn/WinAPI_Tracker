#include "../header/Target.h"

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

int Target::GetDelay()
{
	return delay;
}
