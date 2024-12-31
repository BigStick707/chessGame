#pragma once
#include <string>
class Point
{
private:
	int _x;
	int _y;

public:
	Point(int x, int y);
	/*
	* Function will get X
	*/
	int getX() const;

	/*
	* Function will get Y
	*/
	int getY() const;
};