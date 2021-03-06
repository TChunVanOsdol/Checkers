// Checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Game.h"
#include "Piece.h"
#include "Title.h"

const int windowW = 800;
const int windowH = 800;
const int tilesPerRow = 8;
const int tilesPerCol = 8;

enum state {
	title,
	newgame,
	game,
	win
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowW, windowH), "Checkers");

	state gameState = title;

	//Objects for title screen
	Title titleScreen;

	//Objects for gameplay
	Board GameBoard(window, windowW, windowH, tilesPerRow, tilesPerCol);

	//int piecesPerTeam = (tilesPerRow / 2) * 3;
	int piecesPerTeam = 2;
	int startingPlayer = 0;
	Game GameHandler(startingPlayer, piecesPerTeam);
	bool declareWinner = false;
	//Container for all the pieces
	std::vector<Piece> checker;
	//Pointers for all pieces to manipulate in class functions
	std::vector<Piece*> checkerPtr;

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
		switch (gameState) {
		case title:
			//Title stuff
			titleScreen.drawTitle(window);
			switch (titleScreen.menuLayer) {
				//Title Screen, no menus open
			case 0:
				if (GameBoard.newClick == true && titleScreen.playBox.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
					gameState = newgame;
				}
				if (GameBoard.newClick == true && titleScreen.optBox.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
					titleScreen.setMenu1();
				}
				if (GameBoard.newClick == true && titleScreen.quitBox.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
					window.close();
				}
				break;
				
				//First menu layer
			case 1:
				if (GameBoard.newClick == true && titleScreen.optionText[0].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
					//Set first player selected
					titleScreen.setMenu2(0);
				}
				if (GameBoard.newClick == true && titleScreen.optionText[1].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
					//Set piece count selected
					titleScreen.setMenu2(1);
				}
				if (GameBoard.newClick == true && titleScreen.optionText[2].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
					//Return to layer 0
					titleScreen.closeMenu();
				}
				break;

				//Second menu layer
			case 2:
				if (GameBoard.newClick == true && titleScreen.optionText[0].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
					//Set red as first player
					if (titleScreen.menuType == 0) {
						startingPlayer = 0;
					}
					//OR increment starting piece count
					if (titleScreen.menuType == 1) {
						piecesPerTeam++;
						if (piecesPerTeam > 12) {
							piecesPerTeam = 12;
						}
					}
				}
				if (GameBoard.newClick == true && titleScreen.optionText[1].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
					//Set white as first player
					if (titleScreen.menuType == 0) {
						startingPlayer = 1;
					}
					//OR decrement starting piece count
					if (titleScreen.menuType == 1) {
						piecesPerTeam--;
						if (piecesPerTeam < 1) {
							piecesPerTeam = 1;
						}
					}
				}
				if (GameBoard.newClick == true && titleScreen.optionText[2].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
					//Return to layer 1
					titleScreen.setMenu1();
				}
				break;
			}
			break;

		case newgame:
			//Reset Game Handler
			GameHandler.restartGame(startingPlayer, piecesPerTeam);
			//Reset effects of winning move
			GameBoard.pieceJumping = false;
			declareWinner = false;
			//Spawn all the pieces for a new game
			int spawnPos;
			checker.clear();
			checkerPtr.clear();
			for (int i = 0; i < piecesPerTeam; i++) {
				spawnPos = (2 * i + 1) - (i / (tilesPerRow / 2)) % 2;
				checker.push_back(Piece(redteam, spawnPos, GameBoard, GameHandler));
				checker.push_back(Piece(whiteteam, (GameBoard.tileCount - 1) - spawnPos, GameBoard, GameHandler));
			}
			for (Piece &p : checker) checkerPtr.push_back(&p);
			//New game setup complete, change state
			gameState = game;
			break;

		case game:
			GameBoard.drawBoard(window);
			GameHandler.drawTurn(window);

			//Iterate through all checker pieces
			for (int i = 0; i < checker.size(); i++) {
				checker[i].update(checkerPtr);
				checker[i].drawPiece(window);
				if (checker[i].alive == false) {
					declareWinner = GameHandler.losePiece(checker[i].color);
					checker.erase(checker.begin() + i);
				}
			}
			if (declareWinner == true) {
				gameState = win;
			}
			break;

		case win:
			//Display message if losePiece returns true
			GameHandler.drawVictory(window);
			if (GameBoard.newClick == true)
				gameState = title;
			break;
		}
		
		window.display();
	}

    return 0;
}

