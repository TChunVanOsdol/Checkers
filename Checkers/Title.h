#pragma once
#include <SFML/Graphics.hpp>

const int optionTotal = 3;

class Title {
public:
	sf::Font menuFont;
	sf::RectangleShape titleBox;
	sf::Text titleText;
	sf::RectangleShape playBox;
	sf::Text playText;
	sf::RectangleShape optBox;
	sf::Text optText;
	sf::RectangleShape quitBox;
	sf::Text quitText;

	int menuLayer = 0;
	int menuType = 0;
	sf::RectangleShape menuBox;
	sf::Text optionText[optionTotal];

	Title();
	void drawTitle(sf::RenderWindow &window);
	void setMenu1();
	void setMenu2(int option);
	void closeMenu();
};