#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

enum checkertype {
	redteam,
	whiteteam
};

class Piece {
public:
	Board* boardref;
	int position;
	bool alive = true;
	checkertype color;
	bool kinged = false;
	sf::CircleShape checkerShape;

	Piece(checkertype col, int pos);
	void drawPiece(sf::RenderWindow &window);
	//void selectPiece();
	//void placePiece();
};
