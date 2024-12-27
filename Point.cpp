#include "Point.h"

Point::Point(int x, int y) : _x(x), _y(y)
{
}

int Point::getX() const
{
	return _x;
}

int Point::getY() const
{
	return _y;
}
