#pragma once
#include "Piece.h"
#include <vector>
#include <string>

class Piece;

class Board
{
protected:
	Piece* _Board[8][8];
	std::vector<Point*> _availablePlaces;

public:
	Board(char* bordStat);
	~Board();
	bool isThereFigure(const Point& position) const;
	bool placeFigure(const Point& position, Piece* figure);
	bool removeFigure(const Point& position);
	Piece* getFigure(const Point& position) const;
	Point* getKingPos(const bool team) const;
	void moveFigure(Point& src, Point& dst);

	void validPlaces(const Point& figure);
	bool isMoveValid(const Point& position) const;
	bool isCheck(const bool team) const;
};