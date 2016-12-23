#include "Game.h"
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
using namespace sf;

bool Game::hasCollision(int idPlayer,float movex, float movey) {
	if (idPlayer < 0 || idPlayer>1) {
		//throw invalid_argument();
	}
	RectangleShape futurePosition = players_.at(idPlayer).getHitbox();
	futurePosition.move(movex, movey);
	for (int i = 0; i< getNbObstacles(); i++) {
		if (intersects( getObstacle(i), futurePosition)) {
			return true;
		}
	}
	return false;
}

bool Game::intersects(const RectangleShape & rect1, const RectangleShape & rect2)
{
	FloatRect r1 = rect1.getGlobalBounds();
	FloatRect r2 = rect2.getGlobalBounds();
	return r1.intersects(r2);
}

void Game::move(int idplayer, float xMove, float yMove) {
	players_.at(idplayer).move(xMove, yMove);
}

unsigned Game::getNbPlayers() const
{
	return players_.size();
}

const RectangleShape & Game::getHitBoxChar(int i)const
{
	return players_.at(i).getHitbox();
}

void Game::addEnemy(Enemy e) {
	if (!enemies_.empty()) {
		e.move(400, 0);
	}
	enemies_.push_back(e);
}

const std::vector<Enemy> & Game::getEnemies() const {
	return enemies_;
}
void Game::functionMovingEnemies() {
	using namespace std::chrono_literals;
	Vector2f p;
	while (!gameFinish) {
		for (unsigned i = 0;i < enemies_.size();i++) {
			
			enemies_.at(i).move(0, 0.0125);
			std::cout <<  " " << std::endl;
		}
		
		
		
		
	}
	threadEnemies->detach();
}

void Game::startMovingEnemies() {
	threadEnemies = std::unique_ptr < std::thread > (new std::thread(&Game::functionMovingEnemies,this));
	
}
