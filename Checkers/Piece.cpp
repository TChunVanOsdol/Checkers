#pragma once
#include "stdafx.h"
#include "Piece.h"

Piece::Piece() {}

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
	checkerShape.setRadius(boardref->tileW * 0.4); //Sets a radius to 40% of a tile's width
	checkerShape.setOrigin(-boardref->tileW * 0.1, -boardref->tileH * 0.1);
}

void Piece::drawPiece(sf::RenderWindow &window) {
	checkerShape.setPosition(boardref->getTilePos(position));
	window.draw(checkerShape);
}

void Piece::update(std::vector<Piece*> checkers) {
	//Update function can be created as a series of functions to help organize what should happen each game loop
}

void Piece::selectPiece() {
	//Select piece
	//Deselect piece
}

void Piece::placePiece(std::vector<Piece*> checkers) {
	//Place a piece by checking if the next click is in a valid location
}
