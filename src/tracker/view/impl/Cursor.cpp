#include "../header/Cursor.h"

Cursor::Cursor(INT x, INT y, INT radius, RECT oldRect) : Circle(x, y, radius, oldRect) {  }

Cursor::Cursor(POINT center, INT radius, RECT oldRect) : Circle(center, radius, oldRect) {  }

POINT Cursor::Shot() const
{
	return GetCenter();
}
