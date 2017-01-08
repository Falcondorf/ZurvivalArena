#pragma once

#include "Arena.h"
#include <vector>
#include "Heroes.h"
#include "Enemy.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <map>
#include <utility>
#include <SFML\Graphics.hpp>
#include <iostream>

struct Node {
	sf::Vector2f parent;
	sf::Vector2f position;
	unsigned gValue;
	unsigned hValue;
	unsigned fValue;
};
struct Level {
	std::string pathPics;
	unsigned nbPv;
};

class Game {
private:
	std::vector<Level> levels;
	unsigned idLevel=0;
	bool brainLock = false;
	unsigned nbEnemies;
	Arena arena_;
	std::vector<Character> players_;
	std::vector<Enemy> enemies_; 
	// always make a limit of 4 enemies when an ennemy dies, replace with a new one decrement from nbEnemies
	bool gameFinish = false;
public:
	bool isFinishGame() const;
	inline const std::vector<Character> &  getPlayers() const;
	Game(unsigned width, unsigned height, int fiboNbEnemies);
	bool hasCollision(int idPlayer, float movex, float movey);
	static bool intersects(const sf::RectangleShape & rect1, const sf::RectangleShape & rect2);
	void move(int idplayer, float xMove, float yMove);
	unsigned getNbPlayers()const;
	const sf::RectangleShape &getHitBoxChar(int i)const;
	inline void addPlayer(float posX, float posY, int pv = 3);
	void addEnemy(float posX, float posY, int pv = 1);
	const std::vector<Enemy> & getEnemies() const;
	inline unsigned getNbObstacles() const;
	inline sf::RectangleShape getObstacle(unsigned i) const;
	inline void setPositionCharacter(unsigned i);
	inline void setAnimXCharacter(unsigned i, Direction direction);
	inline void setAnimYCharacter(unsigned i, Direction direction);
	inline void setStateCharacter(unsigned i);
	inline void setEnemyPlayerMoving(int i, bool isMoving);
	inline void setEnemyHitTextureDepart(int i);
	inline void stateInitializerCharacters();
	inline void finishGame();
	inline void manageGame(unsigned i, float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);
	void manageEnemi(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);
	void startMovingEnemies();
	inline Arena getArena() const;
	void shoot(int idPlayer);
	void slice(int idPlayer);
	std::vector<std::pair<float, float>> trajectoireBalle(int idPlayer) const;
	void moveBall(std::vector<std::pair<float, float>> vec);
	inline const  sf::RectangleShape & getlifebarre() const;
	inline bool isBrainLocked()const;
	inline void setBrainLock(bool lock);
	void nextLevel();
	bool allEnemiesIsDead() const;
	/////// Interaction Joueur Ennemi
	void removePvOfPlayer(unsigned i);
	void setLifeBarOfPlayer(unsigned i, sf::RectangleShape rce);

};

const std::vector<Character> &  Game::getPlayers() const {
	return players_;
}

void Game::addPlayer(float posX, float posY, int pv)
{
	players_.push_back(Heroes(Position(posX, posY), pv, players_.size()));
}

unsigned Game::getNbObstacles() const
{
	return arena_.getNbObstacles();
}

sf::RectangleShape Game::getObstacle(unsigned i) const
{
	return arena_.getObstacle(i);
}

void Game::setPositionCharacter(unsigned i) {
	players_.at(i).setPositionSprite((players_.at(i).getHitbox().getPosition()));
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
	for (unsigned i = 0; i < players_.size(); i++) {
		players_.at(i).setState(Idle);
	}
}

void Game::manageGame(unsigned i, float fpsCount, float fpsSpeed, float switchFps, sf::Clock time) {
	players_.at(i).manageSprite(fpsCount, fpsSpeed, switchFps, time);
}

void Game::finishGame() {
	gameFinish = true;
}
Arena Game::getArena() const {
	return arena_;
}

const sf::RectangleShape & Game::getlifebarre() const {
	return	players_.at(0).getlifebar();
}

bool Game::isBrainLocked()const {
	return brainLock;
}
void Game::setBrainLock(bool lock) {
	brainLock = lock;
}


void Game::setEnemyPlayerMoving(int i, bool isMoving) {
	enemies_.at(i).setPlayerMoving(isMoving);
}

void Game::setEnemyHitTextureDepart(int i)
{
	if (!enemies_.empty()) {
		enemies_.at(i).setHitTextureDepart();
	}
	
}

