#pragma once
#include "SFML/Graphics.hpp"
#include "const.h"

class TextObj {
private:
	sf::Font font;
	sf::Text text;
public:
	TextObj(float x, float y, int size, sf::Color color) {
		font.loadFromFile("DS-DIGI.TTF");
		text.setFont(font);
		text.setFillColor(color);
		text.setCharacterSize(size);
		text.setPosition(x, y);
	}
	void update(std::string str) { text.setString(str); }
	void draw(sf::RenderWindow& window) { window.draw(text); }
};