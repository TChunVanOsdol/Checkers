// Checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Game.h"
#include "Piece.h"

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
	sf::Font menuFont;
	menuFont.loadFromFile("Assets/Arial.ttf");

	sf::RectangleShape titleBox(sf::Vector2f(400.f,100.f));
	titleBox.setPosition(200.f, 200.f);
	titleBox.setFillColor(sf::Color::White);
	sf::Text titleText;
	titleText.setString("Checkers");
	titleText.setFillColor(sf::Color::Red);
	titleText.setCharacterSize(80);
	titleText.setPosition(230.f, 200.f);
	titleText.setFont(menuFont);

	sf::RectangleShape playBox(sf::Vector2f(100.f, 50.f));
	playBox.setPosition(350.f, 400.f);
	playBox.setFillColor(sf::Color::White);
	sf::Text playText;
	playText.setString("Play");
	playText.setFillColor(sf::Color::Red);
	playText.setCharacterSize(40);
	playText.setPosition(360.f, 400.f);
	playText.setFont(menuFont);
	
	sf::RectangleShape quitBox(sf::Vector2f(100.f, 50.f));
	quitBox.setPosition(350.f, 500.f);
	quitBox.setFillColor(sf::Color::White);
	sf::Text quitText;
	quitText.setString("Quit");
	quitText.setFillColor(sf::Color::Red);
	quitText.setCharacterSize(40);
	quitText.setPosition(360.f, 500.f);
	quitText.setFont(menuFont);

	//Objects for gameplay
	Board GameBoard(window, windowW, windowH, tilesPerRow, tilesPerCol);

	//int piecesPerTeam = (tilesPerRow / 2) * 3;
	int piecesPerTeam = 2;
	Game GameHandler(piecesPerTeam);
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
			window.draw(titleBox);
			window.draw(titleText);
			window.draw(playBox);
			window.draw(playText);
			window.draw(quitBox);
			window.draw(quitText);
			if (GameBoard.newClick == true && playBox.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
				gameState = newgame;
			}
			if (GameBoard.newClick == true && quitBox.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
				window.close();
			}
			break;

		case newgame:
			//Spawn all the pieces for a new game
			int spawnPos;
			checker.clear();
			checkerPtr.clear();
			GameHandler.restartGame(piecesPerTeam);
			declareWinner = false;
			for (int i = 0; i < piecesPerTeam; i++) {
				spawnPos = (2 * i + 1) - (i / (tilesPerRow / 2)) % 2;
				checker.push_back(Piece(redteam, spawnPos, GameBoard, GameHandler));
				checker.push_back(Piece(whiteteam, (GameBoard.tileCount - 1) - spawnPos, GameBoard, GameHandler));
			}
			for (Piece &p : checker) checkerPtr.push_back(&p);
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
					//checkerPtr.erase(checkerPtr.begin() + i);
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

