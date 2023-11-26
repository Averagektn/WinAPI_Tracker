#include "../header/Cursor.h"

Cursor::Cursor(int x, int y, int radius, RECT oldRect) : Circle(x, y, radius, oldRect) {  }

Cursor::Cursor(POINT center, int radius, RECT oldRect) : Circle(center, radius, oldRect) {  }

POINT Cursor::Shot() const
{
	return GetCenter();
}
