#include "stdafx.h"
#include "Title.h"

Title::Title() {
	menuFont.loadFromFile("Assets/Arial.ttf");

	titleBox.setSize(sf::Vector2f(400.f, 100.f));
	titleBox.setPosition(200.f, 200.f);
	titleBox.setFillColor(sf::Color::White);
	titleText.setString("Checkers");
	titleText.setFillColor(sf::Color::Red);
	titleText.setCharacterSize(80);
	titleText.setPosition(230.f, 200.f);
	titleText.setFont(menuFont);

	playBox.setSize(sf::Vector2f(100.f, 50.f));
	playBox.setPosition(350.f, 400.f);
	playBox.setFillColor(sf::Color::White);
	playText.setString("Play");
	playText.setFillColor(sf::Color::Red);
	playText.setCharacterSize(40);
	playText.setPosition(360.f, 400.f);
	playText.setFont(menuFont);

	optBox.setSize(sf::Vector2f(100.f, 50.f));
	optBox.setPosition(350.f, 500.f);
	optBox.setFillColor(sf::Color::White);
	optText.setString("Options");
	optText.setFillColor(sf::Color::Red);
	optText.setCharacterSize(24);
	optText.setPosition(357.f, 510.f);
	optText.setFont(menuFont);

	quitBox.setSize(sf::Vector2f(100.f, 50.f));
	quitBox.setPosition(350.f, 600.f);
	quitBox.setFillColor(sf::Color::White);
	quitText.setString("Quit");
	quitText.setFillColor(sf::Color::Red);
	quitText.setCharacterSize(40);
	quitText.setPosition(360.f, 600.f);
	quitText.setFont(menuFont);

	menuBox.setSize(sf::Vector2f(300.f, 200.f));
	menuBox.setPosition(250.f, 200.f);
	menuBox.setFillColor(sf::Color(100, 100, 100));
	for (int i = 0; i < optionTotal; i++) {
		optionText[i].setFillColor(sf::Color::Green);
		optionText[i].setCharacterSize(50);
		optionText[i].setFont(menuFont);
		//Calculate position on menu based on index number
		optionText[i].setPosition(250.f, 200.f + i * 70);
	}
	//Default strings for option text items
	optionText[0].setString("First Player");
	optionText[1].setString("Piece Count");
	optionText[2].setString("Back");
}

void Title::drawTitle(sf::RenderWindow &window) {
	window.draw(titleBox);
	window.draw(titleText);
	window.draw(playBox);
	window.draw(playText);
	window.draw(optBox);
	window.draw(optText);
	window.draw(quitBox);
	window.draw(quitText);
	//Draw the options menu only when needed
	if (menuLayer > 0) {
		window.draw(menuBox);
		for (sf::Text option : optionText) {
			window.draw(option);
		}
	}
}

void Title::setMenu1() {
	menuLayer = 1;
	//Restore menu options to layer 1
	optionText[0].setString("First Player");
	optionText[1].setString("Piece Count");
	optionText[2].setString("Back");
}

void Title::setMenu2(int option) {
	menuLayer = 2;
	menuType = option;
	switch (option) {
	case 0:
		optionText[0].setString("Red");
		optionText[1].setString("White");
		break;
	case 1:
		optionText[0].setString("+1");
		optionText[1].setString("-1");
	}
}

void Title::closeMenu() {
	menuLayer = 0;
}

