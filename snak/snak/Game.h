#pragma once
#include "Arena.h"
#include <vector>
#include "Heroes.h"
#include "Enemy.h"

class Game {
private:
	Arena arena_;
	unsigned nbPlayer_;
	std::vector<Heroes> players;
	std::vector<Enemy> enemies;

public:
	inline Game(unsigned width, unsigned height, unsigned nbPlayer);
	bool hasCollision();
	bool intersects(const RectangleShape & rect1, const RectangleShape & rect2);
};

Game::Game(unsigned width, unsigned height , unsigned nbPlayer): nbPlayer_(nbPlayer) {
	arena_ = Arena(width, height);
	for (int i = 0; i < nbPlayer_; i++) {
		players.emplace_back(Heroes());
	}
}

