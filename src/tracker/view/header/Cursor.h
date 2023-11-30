#pragma once

#include <windows.h>
#include <d2d1.h>

#include "Circle.h"

class Cursor : public Circle
{
public:
	Cursor(INT x, INT y, INT radius, RECT oldRect, INT speed);
	Cursor(POINT center, INT radius, RECT oldRect, INT speed);

	VOID SetSpeed(INT speed);

	INT GetSpeed() const;

	VOID Scale(RECT newRect);
	POINT Shot() const;
	VOID Move(BOOL moveTop, BOOL moveRight, BOOL moveBottom, BOOL moveLeft, RECT bounds);
private:
	INT speed;
	const FLOAT DIAGONAL_SPEED_CORRECTION = 1.41;
};
