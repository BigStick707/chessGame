#include "Board.h"
#include <iostream>

Board::Board()
{
    int i = 0, j = 0;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            _Board[i][j] = nullptr;
        }
    }
}

Board::~Board()
{
    int i = 0, j = 0;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            delete _Board[i][j];
        }
    }
}

bool Board::isThereFigure(const Point& position) const
{
    bool figure = false;

    if (_Board[position.getY()][position.getX()] != nullptr)
    {
        figure = true;
    }

    return figure;
}

bool Board::placeFigure(const Point& position, Piece* figure)
{
    if (!isThereFigure(position))
    {
        _Board[position.getY()][position.getX()] = figure;
        return true;
    }
    return false;
}

bool Board::removeFigure(const Point& position)
{
    delete _Board[position.getY()][position.getX()];
    _Board[position.getY()][position.getX()] = nullptr;

    return true;
}

Piece* Board::getFigure(const Point& position) const
{
    return _Board[position.getY()][position.getX()];
}

Point* Board::getKingPos(const bool team) const
{
    int i = 0, j = 0;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            if (_Board[i][j]->getTeam() == team && _Board[i][j]->getType() == "K" || _Board[i][j]->getType() == "k");
            {
                return new Point(j, i);
            }
        }
    }
}


void Board::validPlaces(const Point& figure)
{
    std::string type = _Board[figure.getY()][figure.getX()]->getType();
    bool team = _Board[figure.getY()][figure.getX()]->getTeam();
    int x = figure.getX(), y = figure.getY();

    if (type == "Rook")
    {
        //Check -> (right)
        for (int i = x + 1; i < 8; i++)
        {
            Point* newPoint = new Point(i, y);
            if (isThereFigure(*newPoint)) {
                if (_Board[y][i]->getTeam() != team)
                {
                    _availablePlaces.push_back(newPoint); //opp figure
                }
                else 
                {
                    delete newPoint;
                }
                break; 
            }
            _availablePlaces.push_back(newPoint); 
        }

        // Check <- (left)
        for (int i = x - 1; i >= 0; i--)
        {
            Point* newPoint = new Point(i, y);
            if (isThereFigure(*newPoint))
            {
                if (_Board[y][i]->getTeam() != team)
                {
                    _availablePlaces.push_back(newPoint); //opp figure
                }
                else {
                    delete newPoint;
                }
                break;
            }
            _availablePlaces.push_back(newPoint); 
        }
    }
}

bool Board::isMoveValid(const Point& position) const
{
    int size = _availablePlaces.size(), i = 0;

    for (i = 0; i < size; i++)
    {
        if (position.getX() == _availablePlaces[i]->getX() && position.getY() == _availablePlaces[i]->getY())
        {
            return true;
        }
    }
    return false;
}



bool Board::isCheck(const bool team) const
{
    Point* kingPos = getKingPos(!team);

    int size = _availablePlaces.size(), i = 0;

    for (i = 0; i < size; i++)
    {
        if (kingPos->getX() == _availablePlaces[i]->getX() && kingPos->getY() == _availablePlaces[i]->getY())
        {
            return true;
        }
    }
    return false;
}