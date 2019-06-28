// Checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"

const int windowW = 800;
const int windowH = 800;
const int tilesPerRow = 8;
const int tilesPerCol = 8;

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowW, windowH), "Checkers");

	Board GameBoard(window, windowW, windowH, tilesPerRow, tilesPerCol);

	int piecesPerTeam = (tilesPerRow / 2) * 3;
	bool declareWinner = false;

	//Container for all the pieces
	std::vector<Piece> checker;
	//Pointers for all pieces to manipulate in class functions
	std::vector<Piece*> checkerPtr;
	//Add the pieces to the vectors
	checker.push_back(Piece(redteam, 10, GameBoard));
	checker.push_back(Piece(whiteteam, 17, GameBoard));
	checker.push_back(Piece(redteam, 12, GameBoard));
	for (Piece &p : checker) checkerPtr.push_back(&p);

	//Game Loop
	while (window.isOpen())
	{
		//Reset game loop values
		window.clear();
		GameBoard.newClick = false;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					//Register a new mouse click for piece selection functions
					GameBoard.newClick = true;
					//Find the tile that was clicked in
					GameBoard.clickPos = GameBoard.getTileN(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				}
			}
		}

		GameBoard.drawBoard(window);
		for (int i = 0; i < checker.size(); i++) {
			checker[i].selectPiece();
			checker[i].drawPiece(window);
		}
		window.display();
	}
	//End of game loop
	return 0;
}

