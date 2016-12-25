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
	for (int j = 0; j < getEnemies().size(); j++) {
		if (intersects(getEnemies().at(j).getHitbox(), futurePosition)) {
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

void Game::addEnemy(float posX, float posY, int pv) {
	enemies_.push_back(Enemy(Position(posX, posY), pv));
}

const std::vector<Enemy> & Game::getEnemies() const {
	return enemies_;
}
void Game::functionMovingEnemies() {
	using namespace std::chrono_literals;
	Vector2f p;
	while (!gameFinish) {
		for (unsigned i = 0;i < enemies_.size();i++) {
			
			enemies_.at(i).move(0, 0.00006);
			enemies_.at(i).setAnimY(Down);
			enemies_.at(i).uptadeSpritePosition();
			enemies_.at(i).setState(Moving);
			//enemies_.at(i).manageSprite(fpsCount, fpsSpeed, switchFps, time);
			//arena_.updateMatrice(enemies_.at(i).getHitbox().getPosition(), float x,float y );
		}

	}
	threadEnemies->detach();
}

void Game::startMovingEnemies() {
	threadEnemies = std::unique_ptr < std::thread > (new std::thread(&Game::functionMovingEnemies,this));
	
}

void Game::manageEnemi(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time) {
	
	for (unsigned i = 0;i < enemies_.size();i++) {
		enemies_.at(i).manageSprite(fpsCount, fpsSpeed, switchFps, time);
		enemies_.at(i).setState(Idle);
	}
	
}