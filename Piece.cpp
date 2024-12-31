#include "Piece.h"

Piece::Piece(const std::string& type, const bool team) : _type(type), _team(team)
{
}

/*
* Function will get piece type
*/
std::string Piece::getType() const
{
	return _type;
}

/*
* Function will get piece team
*/
bool Piece::getTeam() const
{
	return _team;
}
