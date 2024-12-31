/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Board.h"
#include "Point.h"

using std::cout;
using std::endl;
using std::string;


void main()
{
	srand(time_t(NULL));

	Piece* destPiece = nullptr;
	Pipe p;
	bool isConnect = p.connect();
	
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return;
		}
	}
	

	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol

	strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0"); // just example...


	Board board(msgToGraphics);
	bool turn = msgToGraphics[64] - '0';

	p.sendMessageToGraphics(msgToGraphics);   // send the board string
	
	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// Extract the source point
		char sourceX_char = msgFromGraphics[0];
		char sourceY_char = msgFromGraphics[1];
		int sourceX = sourceX_char - 'a'; 
		int sourceY = sourceY_char - '0' - 1;

		Point sourcePoint(sourceX, sourceY);

		// Extract the destination point
		char destX_char = msgFromGraphics[2];
		char destY_char = msgFromGraphics[3];
		int destX = destX_char - 'a'; 
		int destY = destY_char - '0' - 1; 

		Point destPoint(destX, destY);

		msgToGraphics[1] = 0;

		if (!(board.isThereFigure(sourcePoint)) || board.getFigure(sourcePoint)->getTeam() != turn) {
			msgToGraphics[0] = (char)(2 + '0');
		}

		else if (board.getFigure(destPoint) && board.getFigure(destPoint)->getTeam() == board.getFigure(sourcePoint)->getTeam()) {
			msgToGraphics[0] = (char)(3 + '0');
		}

		else if (sourcePoint.getX() == destPoint.getX() && sourcePoint.getY() == destPoint.getY()) {
			msgToGraphics[0] = (char)(7 + '0');
		}
		
		else {
			board.validPlaces(sourcePoint, false);
			if (board.isMoveValid(destPoint)) {
				board.clearAvailablePlaces();
				destPiece = board.getFigure(destPoint);

				board.moveFigure(sourcePoint, destPoint);
				
				
				if (board.isCheck(!turn)) {
					board.moveFigure(destPoint, sourcePoint);
					board.placeFigure(destPoint, destPiece);
					msgToGraphics[0] = (char)(4 + '0');

				}
				else {

					if (board.isCheck(turn)) {
						msgToGraphics[0] = (char)(1 + '0');
					}
					else {
						msgToGraphics[0] = (char)(0 + '0');
						
					}
					turn = !turn;
				}				
			}
			else {
				board.clearAvailablePlaces();
				msgToGraphics[0] = (char)(6 + '0');
			}
		}

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);   

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}