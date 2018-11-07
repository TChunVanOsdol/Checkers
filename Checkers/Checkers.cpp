// Checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"
#include <iostream>

const int windowW = 800;
const int windowH = 800;
const int tilesPerRow = 8;
const int tilesPerCol = 8;

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowW, windowH), "Checkers");
	Board GameBoard(window, windowW, windowH, tilesPerRow, tilesPerCol);
	std::vector<Piece> checker;
	checker.push_back(Piece(redteam, 12, GameBoard));
	checker.push_back(Piece(redteam, 14, GameBoard));
	checker.push_back(Piece(whiteteam, 17, GameBoard));
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
					//Register a mouse click
					GameBoard.newClick = true;
					//Find the tile that was clicked in
					GameBoard.clickPos = GameBoard.getTileN(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					std::cout << GameBoard.clickPos << std::endl;
				}
			}
		}
		GameBoard.drawBoard(window);
		for (int i = 0; i < checker.size(); i++) {
			checker[i].update(window);
			checker[i].drawPiece(window);
		}
		window.display();
	}

    return 0;
}

