#pragma once
#include "stdafx.h"
#include "Piece.h"
#include <iostream>

Piece::Piece(checkertype col, int pos, Board &ref) {
	//Create a game piece with red or white team at a position index.
	color = col;
	position = pos;
	boardref = &ref;
	if (color == whiteteam) {
		checkerShape.setFillColor(sf::Color::White);
	}
	else {
		checkerShape.setFillColor(sf::Color::Red);
	}
	checkerShape.setOutlineColor(sf::Color::Green);
	checkerShape.setOutlineThickness(0.f);
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

void Piece::update(sf::RenderWindow &window) {
	if (boardref->clickPos == position && selected == false && boardref->newClick == true) {
		boardref->pieceSelected = true;
		selected = true;
		checkerShape.setOutlineThickness(8.f);
		std::cout << boardref->newClick << std::endl;
	}
	else if (boardref->clickPos == position && selected == true && boardref->newClick == true) {
		//Clicked on piece again
		checkerShape.setOutlineThickness(0.f);
		boardref->pieceSelected = false;
		selected = false;
		std::cout << boardref->newClick << std::endl;
	}
	else if (boardref->clickPos != position) {
		//Clicked off of piece
		checkerShape.setOutlineThickness(0.f);
		boardref->pieceSelected = false;
		selected = false;
	}
}

void Piece::selectPiece() {

}

void Piece::placePiece() {

}