#pragma once
#include "Point.h"
#include "Board.h"

class Board;

class Piece
{
protected:
	std::string _type;
	bool _team;

public:
	Piece(const std::string& type, const bool team);
	std::string getType() const;
	bool getTeam() const;
	virtual ~Piece() = default;
	virtual bool move(const Point& position) const = 0;
};