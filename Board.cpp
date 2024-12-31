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

            // Determine the team and normalize the piece character to lowercase
            if (std::isupper(current))
            {
                team = 0; // Uppercase indicates Team 0
                current = tolower(current);
            }
            else
            {
                team = 1; // Lowercase indicates Team 1
            }

            // Handle empty spaces ('#') or create a new Piece object
            if (current == '#')
            {
                _Board[i][j] = nullptr; // Empty space
            }
            else
            {
                std::string str(1, current); // Convert character to string
                _Board[i][j] = new Piece(str, team); // Create new piece
            }
        }
        bordStatRow++; // Move to the next row in the input array
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

/*
* Function will check if there is figure in the position it got from parametrs
*/
bool Board::isThereFigure(const Point& position) const
{
    bool figure = false;
    if (_Board[position.getY()][position.getX()] != nullptr)
    {
        figure = true;
    }

    return figure;
}


/*
* Function will place figure that he got from parametrs to position that it got from parametrs
*/
void Board::placeFigure(const Point& position, Piece* figure)
{

    _Board[position.getY()][position.getX()] = figure;


}

/*
* Function will remove figure from position it got from parametrs
*/
bool Board::removeFigure(const Point& position)
{
    delete _Board[position.getY()][position.getX()];
    _Board[position.getY()][position.getX()] = nullptr;

    return true;
}

/*
* Function will return figure in the position it got from parametrs
*/
Piece* Board::getFigure(const Point& position) const
{
    return _Board[position.getY()][position.getX()];
}

/*
* Function will get king position with the team it got from parametrs
*/
Point Board::getKingPos(const bool team) const
{
    int i = 0, j = 0;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            if (_Board[i][j] && (_Board[i][j]->getType()) == "k" && (_Board[i][j]->getTeam()) == team)
            {
                return Point(j, i);
            }
        }
    }
}

/*
* Function will get x and y and save the point if the move is possible
*/
void Board::deleteOrAdd(const int x, const int y)
{
    Point* point = new Point(x, y);
    if (isThereFigure(*point))
    {
        delete point;
    }
    else
    {
        _availablePlaces.push_back(point);
    }
}

/*
* Function will get x and y and save the point if the move is possible, the move is possible ONLY if there is enemy figure.
*/
void Board::deleteOrAdd(const int x, const int y, const bool team)
{
    Point* point = new Point(x, y);
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

/*
* Function will get x and y and save the point if the move is possible. The move is possible if there is no teammate figure, if there is enemy figure OR there is empty place.
*/
void Board::deleteOrAddPlacesDot(const int x, const int y, const bool team)
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
void Board::checkDirection(const int x, const int y, const int dx, const int dy, const bool team)
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


/*
* Function will get point and additional Parameter onlyEat to calculate the figure possible moves (points).
* "only Eat" basiacally needed for check calculation with pawn units. onlyEat = true - pawn regular move will not be calculated
*/
void Board::validPlaces(const Point& figure, bool onlyEat)
{
    std::string type = _Board[figure.getY()][figure.getX()]->getType();
    bool team = _Board[figure.getY()][figure.getX()]->getTeam();
    int x = figure.getX(), y = figure.getY();

    if (type == "r") // Rook
    {
        checkDirection(x, y, 1, 0, team); // Check -> (right)
        checkDirection(x, y, -1, 0, team);// Check <- (left)
        checkDirection(x, y, 0, -1, team);// Check (down)
        checkDirection(x, y, 0, 1, team); // Check (up)
    }
    else if (type == "p") // Pawn
    {
        if (team)
        {
            if (!onlyEat)
            {
                if (y == 6) //Check if first time moving
                {
                    deleteOrAdd(x, y - 2);
                }
                deleteOrAdd(x, y - 1);
            }
            //Eating
            deleteOrAdd(x + 1, y - 1, team);
            deleteOrAdd(x - 1, y - 1, team);


        }
        else
        {
            if (!onlyEat)
            {
                if (y == 1) //Check if first time moving
                {
                    deleteOrAdd(x, y + 2);
                }
                deleteOrAdd(x, y + 1);
            }
            //Eating
            deleteOrAdd(x + 1, y + 1, team);
            deleteOrAdd(x - 1, y + 1, team);
        }
    }
    else if (type == "q") // Queen
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
    else if (type == "b") // Bishop
    {
        checkDirection(x, y, 1, 1, team);  // Check top right
        checkDirection(x, y, -1, 1, team); // Check top left
        checkDirection(x, y, 1, -1, team); // Check down right
        checkDirection(x, y, -1, -1, team);// Check down left
    }
    else if (type == "n") // Knight
    {
        //Right part
        deleteOrAddPlacesDot(x + 1, y + 2, team);
        deleteOrAddPlacesDot(x + 2, y + 1, team);
        deleteOrAddPlacesDot(x + 2, y - 1, team);
        deleteOrAddPlacesDot(x + 1, y - 2, team);

        //----------------------------------------------------------

        //Left part
        deleteOrAddPlacesDot(x - 1, y + 2, team);
        deleteOrAddPlacesDot(x - 2, y + 1, team);
        deleteOrAddPlacesDot(x - 2, y - 1, team);
        deleteOrAddPlacesDot(x - 1, y - 2, team);
    }
    else if (type == "k") // King
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

/*
* Function will check, if the figure can be moved to the user position. Function gets position and returns true if everything okay and false if figure cannot be moved
*/
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


/*
* Function will check if the king of the team is under check
*/
bool Board::isCheck(const bool team)
{
    Point kingPos = getKingPos(!team);
    int size = 0, i = 0, j = 0;
    // Iterate over all squares on the board
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            // If the square contains a piece of the given team, calculate its valid moves
            if (_Board[i][j] && _Board[i][j]->getTeam() == team)
            {
                Point piecePos(j, i); // Create a point for the piece position
                validPlaces(piecePos, true); // Generate valid moves for the piece
            }
        }
    }
    size = _availablePlaces.size(); // Get the total number of valid moves for the team
    // Check if any valid move can reach the opponent's king
    for (i = 0; i < size; i++)
    {
        if (kingPos.getX() == _availablePlaces[i]->getX() && kingPos.getY() == _availablePlaces[i]->getY())
        {
            clearAvailablePlaces(); // Clear the list of available places
            return true; // The king is in check
        }
    }
    clearAvailablePlaces(); // Clear the list of available places
    return false; // The king is not in check
}

/*
* Function will clear Available places vector and delete/free allocated points.
*/
void Board::clearAvailablePlaces()
{
    // Delete all dynamically allocated Points in the _availablePlaces vector
    for (int i = 0; i < _availablePlaces.size(); i++)
    {
        delete _availablePlaces[i];
    }
    _availablePlaces.clear(); // Clear the vector
}

/*
* Function will move figure from source to dest (points)
*/
void Board::moveFigure(Point& src, Point& dst)
{
    // Move the piece from the source position to the destination position
    _Board[dst.getY()][dst.getX()] = _Board[src.getY()][src.getX()];
    _Board[src.getY()][src.getX()] = nullptr; // Set the source position to empty
}
