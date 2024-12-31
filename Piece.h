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
	virtual ~Piece() = default;
	/*
	* Function will get piece type
	*/
	std::string getType() const;
	/*
	* Function will get piece team
	*/
	bool getTeam() const;
};