#include "../header/Cursor.h"

Cursor::Cursor(int x, int y, int radius) : Circle(x, y, radius) {  }

Cursor::Cursor(POINT center, int radius) : Circle(center, radius) {  }

POINT Cursor::Shot()
{
	return GetCenter();
}
