#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Game.h"
#include <iostream>

//Enumerator for checkertype moved to Game.h

class Piece {
public:
	Board* boardref;
	Game* gameref;
	int position;
	bool alive = true;
	bool selected = false;
	bool selectable = true;
	checkertype color;
	bool kinged = false;
	sf::CircleShape checkerShape;
	bool jumpable = false;
	std::vector<int> endPositions;

	Piece();
	Piece(checkertype col, int pos, Board &ref, Game &gref);
	void drawPiece(sf::RenderWindow &window);
	void update(std::vector<Piece*> checkers);
	void selectPiece();
	void placePiece(std::vector<Piece*> checkers);
	void filterPiece(std::vector<Piece*> checkers);
	void searchTree(std::vector<Piece*> checkers);
};
