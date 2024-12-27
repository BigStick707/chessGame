#pragma once
#include <string>
class Point
{
private:
	int _x;
	int _y;

public:
	Point(int x, int y);
	int getX() const;
	int getY() const;
};