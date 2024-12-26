#pragma once
#include "Point.h"
#include <vector>
class Piece
{
protected:
	std::string _type;
	std::vector<Point> _availablePlaces;
	bool _team;

public:
	Piece(const std::string& type, const bool team);
	std::string getType();
	bool getTeam();
	virtual ~Piece() = default;
	virtual void validPlaces(const Piece& figure) const = 0;
	bool isMoveValid(const Point& position) const;
	bool isCheck(const Point& position) const;
	virtual bool move(const Point& position) const = 0;
};