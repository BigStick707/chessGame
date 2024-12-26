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
}
