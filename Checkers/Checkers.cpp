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
	Piece checker1(redteam, 12);
	checker1.boardref = &GameBoard;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}

		window.clear();
		GameBoard.drawBoard(window);
		checker1.drawPiece(window);
		window.display();
	}

    return 0;
}

