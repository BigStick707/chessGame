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
	// YOUR CODE
	

	

	strcpy_s(msgToGraphics, "rnbkqbnrppppppp#################################PPPPPPPPRNBKQBNR1"); // just example...
	Board board(msgToGraphics);
	bool turn = msgToGraphics[64] - '0';
	std::cout << turn << std::endl;
	p.sendMessageToGraphics(msgToGraphics);   // send the board string
	
	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		

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

		// YOUR CODE
		strcpy_s(msgToGraphics, "YOUR CODE"); // msgToGraphics should contain the result of the operation
		msgToGraphics[1] = 0;
		/******* JUST FOR EREZ DEBUGGING ******/
		int r = rand() % 10; // just for debugging......
		
		
		/******* JUST FOR EREZ DEBUGGING ******/

		if (!(board.isThereFigure(sourcePoint)) || board.getFigure(sourcePoint)->getTeam() != turn) {
			msgToGraphics[0] = (char)(2 + '0');
		}

		else if (board.getFigure(destPoint) && board.getFigure(destPoint)->getTeam() == board.getFigure(sourcePoint)->getTeam()) {
			msgToGraphics[0] = (char)(3 + '0');
		}

		else if (sourcePoint.getX() == destPoint.getX() && sourcePoint.getY() == destPoint.getY()) {
			msgToGraphics[0] = (char)(7 + '0');
		}

		

		//else if (true) {
		//	board.validPlaces(sourcePoint);


		//	msgToGraphics[0] = (char)(7 + '0');
		//}
		
		else {
			board.validPlaces(sourcePoint);
			if (board.isMoveValid(sourcePoint)) {
				board.moveFigure(sourcePoint, destPoint);

				board.validPlaces(sourcePoint);
				if (board.isCheck(turn)) {
					msgToGraphics[0] = (char)(1 + '0');
				}
				else{
					msgToGraphics[0] = (char)(0 + '0');
				}
				turn = !turn;
			}
			else {
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