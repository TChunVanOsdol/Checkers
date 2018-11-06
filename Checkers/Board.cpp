#pragma once
#include "stdafx.h"
#include "Board.h"

Board::Board(sf::RenderWindow &window, int height, int width, int tilesInRow, int tilesInCol) {
	boardH = height;
	boardW = width;
	tilesPerRow = tilesInRow;
	tilesPerCol = tilesInCol;
	tileH = boardH / tilesPerCol;
	tileW = boardW / tilesPerRow;
	tileShape = sf::RectangleShape(sf::Vector2f(tileW, tileH));
	tileTypes = std::vector<tiletype>(tileCount);
	for (int i = 0; i < tileCount; i++) {
		if ((i % 2 - (i / tilesPerRow) % 2) == 0) {
			tileTypes[i] = white;
		}
		else {
			tileTypes[i] = black;
		}
	}
}

void Board::drawBoard(sf::RenderWindow &window) {
	sf::Vector2f tilePos;
	for (int i = 0; i < tileCount; i++) {
		tilePos = getTilePos(i);
		tileShape.setPosition(tilePos);
		if (tileTypes[i] == white) {
			tileShape.setFillColor(sf::Color::White);
		}
		else {
			tileShape.setFillColor(sf::Color::Black);
		}
		window.draw(tileShape);
	}
}

int Board::getTileN(float x, float y) {
	//Find the index number starting at 0,0 going right then down
	//For C4B, use the 2D approach
	int tileX, tileY;
	tileX = int(x / tileW);
	tileY = int(y / tileH);
	return tileX + (tileY * tilesPerCol);
}

sf::Vector2f Board::getTilePos(int N) {
	//Return position of tile's origin in pixels
	float posX, posY;
	posX = (N % tilesPerRow) * tileW;
	posY = (N / tilesPerCol) * tileH;
	return sf::Vector2f(posX, posY);
}