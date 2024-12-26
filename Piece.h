#pragma once
#include "Point.h"
class Piece
{
protected:
	std::string _name;
	std::string _type;
	char _team;

public:
	Piece(const std::string& name, const std::string& type, const std::string team);
	std::string getName();
	std::string getType();
	char getTeam();
	virtual ~Piece() = default;
	virtual bool move(const Point& position) const = 0;
};