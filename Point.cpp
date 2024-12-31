#include "Point.h"

Point::Point(int x, int y) : _x(x), _y(y)
{
}

/*
* Function will get X
*/
int Point::getX() const
{
	return _x;
}


/*
* Function will get Y
*/
int Point::getY() const
{
	return _y;
}
