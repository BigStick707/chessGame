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

	/*
	* Function will check if there is figure in the position it got from parametrs
	*/
	bool isThereFigure(const Point& position) const;

	/*
	* Function will place figure that he got from parametrs to position that it got from parametrs
	*/
	void placeFigure(const Point& position, Piece* figure);

	/*
	* Function will remove figure from position it got from parametrs
	*/
	bool removeFigure(const Point& position);

	/*
	* Function will return figure in the position it got from parametrs
	*/
	Piece* getFigure(const Point& position) const;

	/*
	* Function will get king position with the team it got from parametrs
	*/
	Point getKingPos(const bool team) const;

	/*
	* Function will move figure from source to dest (points)
	*/
	void moveFigure(Point& src, Point& dst);

	/*
	* Function will get x and y and save the point if the move is possible
	*/
	void deleteOrAdd(const int x, const int y);

	/*
	* Function will get x and y and save the point if the move is possible, the move is possible ONLY if there is enemy figure.
	*/
	void deleteOrAdd(const int x, const int y, const bool team);

	/*
	* Function will get x and y and save the point if the move is possible. The move is possible if there is no teammate figure, if there is enemy figure OR there is empty place.
	*/
	void deleteOrAddPlacesDot(const int x, const int y, const bool team);

	//Function will check direction. Will get x and y
	//Right: dx = 1, dy = 0
	//Left: dx = -1, dy = 0
	//Down: dx = 0, dy = -1
	//Up: dx = 0, dy = 1
	//Top right: dx = 1, dy = 1
	//Top left : dx = -1, dy = 1
	//down right : dx = 1, dy = -1
	//down left : dx = -1, dy = -1
	void checkDirection(const int x, const int y, const int dx, const int dy, const bool team);

	/*
	* Function will get point and additional Parameter onlyEat to calculate the figure possible moves (points).
	* "only Eat" basiacally needed for check calculation with pawn units. onlyEat = true - pawn regular move will not be calculated
	*/
	void validPlaces(const Point& figure, bool onlyEat);

	/*
	* Function will check, if the figure can be moved to the user position. Function gets position and returns true if everything okay and false if figure cannot be moved
	*/
	bool isMoveValid(const Point& position) const;
	
	/*
	* Function will check if the king of the team is under check
	*/
	bool isCheck(const bool team);

	/*
	* Function will clear Available places vector and delete/free allocated points.
	*/
	void clearAvailablePlaces();
};