#include "bomb.h"
#include "const.h"

Bomb::Bomb(BombType type, sf::Vector2f position) {
	switch (type) {
	case HP:
		this->type = type;
		texture.loadFromFile("bomb.png");
		sprite.setTexture(texture);
		sprite.setPosition(position);
		break;
	}
}
void Bomb::update() { sprite.move(0.f, 10.f); }
void Bomb::draw(sf::RenderWindow& window) { window.draw(sprite); }
size_t Bomb::getWidth() { return sprite.getLocalBounds().width; }
size_t Bomb::getHeight() { return sprite.getLocalBounds().height; }
sf::FloatRect Bomb::getHitBox() { return sprite.getGlobalBounds(); }
sf::Vector2f Bomb::getPosition() { return sprite.getPosition(); }
bool Bomb::getDel() { return del; }
void Bomb::setDel(bool x) { del = x; }