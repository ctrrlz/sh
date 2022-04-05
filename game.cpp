#include "game.h"
Game::Game() :
	window(sf::VideoMode(
		static_cast<size_t> (WINDOW_WIDTH),
		static_cast<size_t> (WINDOW_HEIGHT)
	),
		"game",
		sf::Style::Titlebar | sf::Style::Close
	),
	player(WINDOW_WIDTH / 2 - 120 / 2.f,
		WINDOW_HEIGHT - 120.f, "k_.png"),
	hp_text(500, 5, 42, sf::Color::White)
{
	window.setFramerateLimit(60);
	fruit_sprites.reserve(7);
	for (size_t i = 0; i < 7; i++) {
		fruit_sprites.push_back(new Fruit());
	}
	
}
void Game::play() {
	while (window.isOpen()) {
		check_events();
		update();
		check_collisions();
		draw();
	}
}
void Game::check_events() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) window.close();
	}
}
void Game::update() {
	switch (game_state) {
	case PLAY:
		player.update();
		for (size_t i = 0; i < 7; i++) {
			fruit_sprites[i]->update();
		}
		for (auto it = bomb_sprites.begin(); it != bomb_sprites.end(); it++) {
			(*it)->update();
		}
		check_collisions();
		hp_text.update(std::to_string(static_cast<int>(player.getHp())));
		break;
	case GAME_OVER:
		break;
	}
}
void Game::draw() {

	window.clear();
	switch (game_state) {

	case PLAY:
		for (size_t i = 0; i < 7; i++) {
			fruit_sprites[i]->draw(window);
		}
		for (auto it = bomb_sprites.begin(); it != bomb_sprites.end(); it++) {
			(*it)->draw(window);
		}
		player.draw(window);
		hp_text.draw(window);
		break;
	case GAME_OVER:
		window.draw(game_over.getSprite());
	}

	window.display();
}
void Game::check_collisions() {

	for (size_t i = 0; i < 7; i++) {
		if (player.getHitBox().intersects(
			fruit_sprites[i]->getHitBox()))
		{
			player.reduceHp(fruit_sprites[i]->getWidth() / 3);
			fruit_sprites[i]->spawn();
			
	}
	for (auto it = bomb_sprites.begin(); it != bomb_sprites.end(); it++) {
		if (player.getHitBox().intersects((*it)->getHitBox())) {
			player.reduceHp(-30);
			(*it)->setDel(true);
		}
	}

	bomb_sprites.remove_if([](Bomb* bomb) {return bomb->getDel(); });
	if (player.isDead()) game_state = GAME_OVER;
	bomb_sprites.remove_if([](Bomb* bomb) {
		return bomb->getPosition().y > WINDOW_HEIGHT; });
	size_t chance = rand() % 100;
	if (chance < 50) {

		Bomb* new_bomb = new Bomb(static_cast<Bomb::BombType>(0),
			fruit_sprites[i]->getPosition());
		bomb_sprites.push_back(new_bomb);
	}
}