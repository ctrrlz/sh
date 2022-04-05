#pragma once
#include "SFML/Graphics.hpp"

class Bomb {
public:
	enum BombType { HP, SHIELD, FIRE_RATE };
	Bomb(BombType type, sf::Vector2f position);
	void update();
	void draw(sf::RenderWindow& window);
	size_t getWidth();
	size_t getHeight();
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
	bool getDel();
	void setDel(bool x);
private:
	sf::Sprite sprite;
	sf::Texture texture;
	BombType type;
	bool del = false;
};