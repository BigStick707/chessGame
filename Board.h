#pragma once
#include "Piece.h"
class Board
{
private:
	Piece* _Board[8][8];

public:
	Board();
	~Board();
	bool isThereFigure(const Point& position) const;
	bool placeFigure(const Point& position, Piece* figure);
	bool removeFigure(const Point& position);
	Piece* getFigure(const Point& position) const;
};