#pragma once
#include <SFML/Graphics.hpp>
#include <string>

const int playerCount = 2;

enum checkertype {
	redteam,
	whiteteam
};

class Game {
public:
	int playerTurn;
	sf::RectangleShape turnIndicator;
	checkertype turnColor;
	int pieceTotal[playerCount];
	int moveTotal[playerCount];

	bool newTurn = true;
	bool turnChanged = false;

	std::string victoryMsg [playerCount];
	sf::Text victoryText;
	sf::Font victoryFont;

	Game(int startPlayer, int startingPieces);
	void changeTurn();
	void drawTurn(sf::RenderWindow &window);
	void drawVictory(sf::RenderWindow &window);
	bool losePiece(checkertype color);
	bool countMoves(int player);
	void restartGame(int startPlayer, int startingPieces);
};