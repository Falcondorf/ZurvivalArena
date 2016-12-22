#pragma once
#include "Arena.h"
#include <vector>
#include "Heroes.h"
#include "Enemy.h"
using namespace sf;
class Game {
private:
	Arena arena_;
	std::vector<Character> players_;
	std::vector<Enemy> enemies_;
	

public:
	inline const std::vector<Character> &  getPlayers() const;
	inline Game(unsigned width, unsigned height);
	bool hasCollision(int idPlayer,float movex,float movey);
	bool intersects(const RectangleShape & rect1, const RectangleShape & rect2);
	void move(int idplayer, float xMove, float yMove);
	unsigned getNbPlayers()const;
	const RectangleShape &getHitBoxChar(int i)const ;
	inline void addPlayer(float posX, float posY, int pv=3);
	inline unsigned getNbObstacles();
	inline RectangleShape getObstacle(unsigned i);

};

Game::Game(unsigned width, unsigned height){
	arena_ = Arena(width, height);

}

const std::vector<Character> &  Game::getPlayers() const {

	return players_;
}

void Game::addPlayer(float posX, float posY, int pv)
{
	players_.push_back(Character(Position(posX, posY), pv, players_.size()));
}

unsigned Game::getNbObstacles()
{
	return arena_.getNbObstacles();
}

RectangleShape Game::getObstacle(unsigned i)
{
	return arena_.getObstacle(i);
}
