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
	bool selected = false;
	checkertype color;
	bool kinged = false;
	sf::CircleShape checkerShape;

	Piece(checkertype col, int pos, Board &ref);
	void drawPiece(sf::RenderWindow &window);
	void update(sf::RenderWindow &window, std::vector<Piece*> checkers);
	void selectPiece();
	void placePiece(std::vector<Piece*> checkers);
};
