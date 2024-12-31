#include "Board.h"
#include <iostream>
#include <cctype>
#include <string>
#include <iostream>
Board::Board(char* bordStat)
{
    int i = 0, j = 0, bordStatRow = 0;
    std::string type;
    bool team;
    for (i = 7; i >= 0; i--)
    {
        for (j = 0; j < 8; j++)
        {
            unsigned char current = bordStat[bordStatRow * 8 + j];
            if (std::isupper(current)) {
                team = 0;
                current = tolower(current);
            }
            else {
                team = 1;
            }

            if (current == '#') {
                _Board[i][j] = nullptr;
            }
            else {
                std::string str(1, current);
                _Board[i][j] = new Piece(str, team);
            }

            // Bord print to test
            //if (_Board[i][j] != nullptr) {
            //    std::cout << _Board[i][j]->getType() << std::endl;
            //}
            //else
            //{
            //    std::cout << std::endl;
            //}
            
        }
        bordStatRow++;
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

void Board::placeFigure(const Point& position, Piece* figure)
{

    _Board[position.getY()][position.getX()] = figure;


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
            if (_Board[i][j] && (_Board[i][j]->getType()) == "k" && (_Board[i][j]->getTeam()) == team)
            {
                return new Point(j, i);
            }
        }
    }
}


void Board::deleteOrAdd(Point* point)
{
    if (isThereFigure(*point))
    {
        delete point;
    }
    else
    {
        _availablePlaces.push_back(point);
    }
}

void Board::deleteOrAdd(Point* point, bool team)
{
    if (point->getX() >= 0 && point->getX() < 8 && point->getY() >= 0 && point->getY() < 8)
    {
        if (isThereFigure(*point) && getFigure(*point)->getTeam() != team)
        {
            _availablePlaces.push_back(point);
            return;
        }
    }
    delete point;
}

void Board::deleteOrAddPlacesDot(int x, int y, bool team)
{
    Point* point = new Point(x, y);
    if (point->getX() >= 0 && point->getX() < 8 && point->getY() >= 0 && point->getY() < 8)
    {
        if (isThereFigure(*point) && getFigure(*point)->getTeam() != team)
        {
            _availablePlaces.push_back(point);
        }
        else if (!isThereFigure(*point))
        {
            _availablePlaces.push_back(point);
        }
        else
        {
            delete point;
        }
    }
}



//Function will check direction. Will get x and y
//Right: dx = 1, dy = 0
//Left: dx = -1, dy = 0
//Down: dx = 0, dy = -1
//Up: dx = 0, dy = 1
//Top right: dx = 1, dy = 1
//Top left : dx = -1, dy = 1
//down right : dx = 1, dy = -1
//down left : dx = -1, dy = -1
void Board::checkDirection(int x, int y, int dx, int dy, int team)
{
    int i = x + dx;
    int j = y + dy;

    while (i >= 0 && i < 8 && j >= 0 && j < 8)
    {
        Point* newPoint = new Point(i, j);

        if (isThereFigure(*newPoint))
        {
            if (_Board[j][i]->getTeam() != team)
            {
                _availablePlaces.push_back(newPoint); // Opponent figure
            }
            else
            {
                delete newPoint;
            }
            break;
        }

        _availablePlaces.push_back(newPoint);
        i += dx;
        j += dy;
    }
}



void Board::validPlaces(const Point& figure, bool onlyEat)
{
    std::string type = _Board[figure.getY()][figure.getX()]->getType();
    bool team = _Board[figure.getY()][figure.getX()]->getTeam();
    int x = figure.getX(), y = figure.getY();

    if (type == "r")
    {
        checkDirection(x, y, 1, 0, team); // Check -> (right)
        checkDirection(x, y, -1, 0, team);// Check <- (left)
        checkDirection(x, y, 0, -1, team);// Check (down)
        checkDirection(x, y, 0, 1, team); // Check (up)
    }
    else if (type == "p")
    {
        if (team)
        {
            if (!onlyEat)
            {
                if (y == 6)
                {
                    Point* newPoint1 = new Point(x, y - 2);
                    deleteOrAdd(newPoint1);
                }
                Point* newPoint2 = new Point(x, y - 1);
                deleteOrAdd(newPoint2);
            }

            //Eating
            Point* newPoint3 = new Point(x + 1, y - 1);
            deleteOrAdd(newPoint3, team);
            Point* newPoint4 = new Point(x - 1, y - 1);
            deleteOrAdd(newPoint4, team);


        }
        else
        {
            if (!onlyEat)
            {
                if (y == 1)
                {
                    Point* newPoint1 = new Point(x, y + 2);
                    deleteOrAdd(newPoint1);
                }
                Point* newPoint2 = new Point(x, y + 1);
                deleteOrAdd(newPoint2);
            }


            //Eating
            Point* newPoint3 = new Point(x + 1, y + 1);
            deleteOrAdd(newPoint3, team);
            Point* newPoint4 = new Point(x - 1, y + 1);
            deleteOrAdd(newPoint4, team);
        }
    }

    else if (type == "q")
    {
        checkDirection(x, y, 1, 0, team); // Check -> (right)
        checkDirection(x, y, -1, 0, team);// Check <- (left)
        checkDirection(x, y, 0, -1, team);// Check (down)
        checkDirection(x, y, 0, 1, team); // Check (up)

        checkDirection(x, y, 1, 1, team); // Check top right
        checkDirection(x, y, -1, 1, team);// Check top left
        checkDirection(x, y, 1, -1, team);// Check down right
        checkDirection(x, y, -1, -1, team); // Check down left
    }
    else if (type == "b")
    {
        checkDirection(x, y, 1, 1, team);  // Check top right
        checkDirection(x, y, -1, 1, team); // Check top left
        checkDirection(x, y, 1, -1, team); // Check down right
        checkDirection(x, y, -1, -1, team);// Check down left
    }
    else if (type == "n")
    {
        deleteOrAddPlacesDot(x + 1, y + 2, team);
        deleteOrAddPlacesDot(x + 2, y + 1, team);
        deleteOrAddPlacesDot(x + 2, y - 1, team);
        deleteOrAddPlacesDot(x + 1, y - 2, team);

        //----------------------------------------------------------

        deleteOrAddPlacesDot(x - 1, y + 2, team);
        deleteOrAddPlacesDot(x - 2, y + 1, team);
        deleteOrAddPlacesDot(x - 2, y - 1, team);
        deleteOrAddPlacesDot(x - 1, y - 2, team);
    }
    else if (type == "k")
    {
        deleteOrAddPlacesDot(x, y + 1, team); //middle top
        deleteOrAddPlacesDot(x + 1, y + 1, team); //right top
        deleteOrAddPlacesDot(x - 1, y + 1, team); //left top
        deleteOrAddPlacesDot(x + 1, y, team); //right
        deleteOrAddPlacesDot(x - 1, y, team); //left
        deleteOrAddPlacesDot(x, y - 1, team); //middle down
        deleteOrAddPlacesDot(x + 1, y - 1, team); //right down
        deleteOrAddPlacesDot(x - 1, y - 1, team); //left down

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



bool Board::isCheck(const bool team)
{
    Point* kingPos = getKingPos(!team);
    int size = 0, i = 0, j = 0;

    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            if (_Board[i][j]&&_Board[i][j]->getTeam() == team)
            {
                Point piecePos(j, i);
                validPlaces(piecePos, true);
            }
        }
    }
    
    size = _availablePlaces.size();

    for (i = 0; i < size; i++)
    {
        if (kingPos->getX() == _availablePlaces[i]->getX() && kingPos->getY() == _availablePlaces[i]->getY())
        {
            clearAvailablePlaces();
            return true;
        }
    }

    clearAvailablePlaces();
    return false;
}

void Board::clearAvailablePlaces()
{
    for (int i = 0; i < _availablePlaces.size(); i++)
    {
        delete _availablePlaces[i];
    }
    _availablePlaces.clear();
}


void Board::moveFigure(Point& src, Point& dst)
{
    //if (isThereFigure(dst))
    //{
    //    removeFigure(dst);
    //}
    _Board[dst.getY()][dst.getX()] = _Board[src.getY()][src.getX()];
    _Board[src.getY()][src.getX()] = nullptr;
}