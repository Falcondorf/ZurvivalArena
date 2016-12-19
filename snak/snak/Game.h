#pragma once
#include "Arena.h"
#include <vector>
#include "Heroes.h"
#include "Enemy.h"
using namespace sf;
class Game {
private:
	Arena arena_;
	unsigned nbPlayer_;
	std::vector<Character> players_;
	std::vector<Enemy> enemies_;

public:
	inline Game(unsigned width, unsigned height,std::vector<Character> listPlayers);
	bool hasCollision(int idPlayer,float movex,float movey);
	bool intersects(const RectangleShape & rect1, const RectangleShape & rect2);

};

Game::Game(unsigned width, unsigned height,std::vector<Character> listPlayers):players_(listPlayers) {
	arena_ = Arena(width, height);

}

