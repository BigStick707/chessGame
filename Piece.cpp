#include "Piece.h"

Piece::Piece(const std::string& type, const bool team) : _type(type), _team(team)
{
}

std::string Piece::getType() const
{
	return _type;
}

bool Piece::getTeam() const
{
	return _team;
}
