#include "../header/Cursor.h"

Cursor::Cursor(INT x, INT y, INT radius, RECT oldRect, INT speed) : Circle(x, y, radius, oldRect) 
{  
	this->speed = speed;
}

Cursor::Cursor(POINT center, INT radius, RECT oldRect, INT speed) : Circle(center, radius, oldRect) 
{  
	this->speed = speed;
}

VOID Cursor::Scale(RECT newRect)
{
	FLOAT coeffX = (FLOAT)newRect.right / oldRect.right;
	FLOAT coeffY = (FLOAT)newRect.bottom / oldRect.bottom;

	speed *= (coeffX + coeffY) / 2;

	Circle::Scale(newRect);
}

VOID Cursor::SetSpeed(INT speed)
{
	this->speed = speed;
}

INT Cursor::GetSpeed() const
{
	return speed;
}

POINT Cursor::Shot() const
{
	return GetCenter();
}

VOID Cursor::Move(BOOL moveTop, BOOL moveRight, BOOL moveBottom, BOOL moveLeft, RECT bounds)
{
	INT xSpeed = 0;
	INT ySpeed = 0;
	INT speed = this->speed;

	if ((moveTop || moveBottom) && (moveRight || moveLeft))
	{
		speed /= DIAGONAL_SPEED_CORRECTION;
	}

	if (moveTop)
	{
		ySpeed -= speed;
	}
	if (moveBottom)
	{
		ySpeed += speed;
	}
	if (moveLeft)
	{
		xSpeed -= speed;
	}
	if (moveRight)
	{
		xSpeed += speed;
	}

	if (GetLeft() <= bounds.left && xSpeed < 0)
	{
		xSpeed = 0;
	}
	if (GetRight() >= bounds.right && xSpeed > 0)
	{
		xSpeed = 0;
	}
	if (GetTop() <= bounds.top && ySpeed < 0)
	{
		ySpeed = 0;
	}
	if (GetBottom() >= bounds.bottom && ySpeed > 0)
	{
		ySpeed = 0;
	}

	AddCoordX(xSpeed);
	AddCoordY(ySpeed);
}
