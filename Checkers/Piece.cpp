#pragma once
#include "stdafx.h"
#include "Piece.h"

Piece::Piece(checkertype col, int pos) {
	//Create a game piece with red or white team at a position index.
	color = col;
	position = pos;
	if (color == whiteteam) {
		checkerShape.setFillColor(sf::Color::White);
	}
	else {
		checkerShape.setFillColor(sf::Color::Red);
	}
}

void Piece::drawPiece(sf::RenderWindow &window) {
	checkerShape.setRadius(boardref->tileW * 0.4); //Sets a radius to 40% of a tile's width
	sf::Vector2f piecePos = boardref->getTilePos(position);
	//Adjust piece to be on center of tile
	piecePos.x += boardref->tileW * 0.1;
	piecePos.y += boardref->tileW * 0.1;
	checkerShape.setPosition(piecePos);
	window.draw(checkerShape);
}