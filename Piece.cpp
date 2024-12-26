#include "Piece.h"

Piece::Piece(const std::string& type, const bool team) : _type(type), _team(team)
{
}

std::string Piece::getType()
{
	return _type;
}

bool Piece::getTeam()
{
	return _team;
}
