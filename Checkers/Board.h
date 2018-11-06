#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum tiletype {
	black,
	white
};

class Board {
public:
	sf::RectangleShape tileShape;
	int boardH, boardW;
	int tileH, tileW;
	int tilesPerRow = 8;
	int tilesPerCol = 8;
	int tileCount = tilesPerCol * tilesPerRow;
	std::vector<tiletype> tileTypes;

	Board(sf::RenderWindow &window, int height, int width);
	void drawBoard(sf::RenderWindow &window);
	int getTileN(float x, float y);
	sf::Vector2f getTilePos(int N);
};