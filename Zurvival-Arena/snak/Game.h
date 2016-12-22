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
	inline void setPositionCharacter(unsigned i);
	inline void setAnimXCharacter(unsigned i, Direction direction);
	inline void setAnimYCharacter(unsigned i, Direction direction);
	inline void setStateCharacter(unsigned i);
	inline void stateInitializerCharacters();
	inline void manageGame(unsigned i, float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);

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

void Game::setPositionCharacter(unsigned i) {
	players_.at(i).setPositionSprite( (players_.at(i).getHitbox().getPosition()) );
}

void Game::setAnimXCharacter(unsigned i, Direction direction) {
	players_.at(i).setAnimX(direction);
}
void Game::setAnimYCharacter(unsigned i, Direction direction) {
	players_.at(i).setAnimY(direction);
}

void Game::setStateCharacter(unsigned i) {
	players_.at(i).setState(Moving);
}
void Game::stateInitializerCharacters() {
	for (unsigned i = 0;i < players_.size();i++) {
		players_.at(i).setState(Idle);
	}
}

void Game::manageGame(unsigned i, float fpsCount, float fpsSpeed, float switchFps, sf::Clock time) {
	players_.at(i).manageSprite(fpsCount, fpsSpeed, switchFps, time);
}