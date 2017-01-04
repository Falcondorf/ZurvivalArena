#pragma once

#include "Arena.h"
#include <vector>
#include "Heroes.h"
#include "Enemy.h"
#include "subject.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <map>
#include <utility>
#include <SFML\Graphics.hpp>

struct Node {
	sf::Vector2f parent;
	sf::Vector2f position;
	unsigned gValue;
	unsigned hValue;
	unsigned fValue;
};

class Game : nvs::Subject {
private:
	int waveLevel = 0; //increment when enemyList empty
	bool brainLock = false;
	unsigned nbEnemies;
	bool textChange = false;
	Arena arena_;
	std::vector<Character> players_;
	std::vector<Enemy> enemies_; // always make a limit of 4 enemies when an ennemy dies, replace with a new one decrement from nbEnemies
	std::unique_ptr<std::thread> threadEnemies;
	/*void functionMovingEnemies();*/
	bool gameFinish = false;
	std::map <std::pair<int, int>, Node> openList;
	std::map <std::pair<int, int>, Node> closedList;
	/*void generateSuccessors(Vector2f pos, std::vector<Node> *successors, Node parent);
	bool parcourOpen(std::vector<Node> openList, sf::Vector2f position, int fValue);
	bool parcourClosed(std::vector<Node> closedList, sf::Vector2f position, int fValue);*/
	bool inversion = false;
	bool playerMove = false;
	std::vector< std::vector<std::pair<int, int>> > pathToEnemy;
	inline int fib(int x) const;

public:
	bool isFinishGame();
	inline void nextWave();
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
	inline int getRemainingEnemies() const;
	inline int getWave() const;
	inline unsigned getNbObstacles();
	inline sf::RectangleShape getObstacle(unsigned i);
	inline void removeDeadEnemies();
	inline void setPositionCharacter(unsigned i);
	inline void setAnimXCharacter(unsigned i, Direction direction);
	inline void setAnimYCharacter(unsigned i, Direction direction);
	inline void setStateCharacter(unsigned i);
	inline void setEnemyPlayerMoving(int i, bool isMoving);
	inline void setEnemyHitTextureDepart(int i);
	inline void stateInitializerCharacters();
	inline void finishGame();
	inline void setNbEnemies(unsigned nb);
	inline void manageGame(unsigned i, float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);
	void manageEnemi(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);

	inline void removeEnemy(unsigned);
	void startMovingEnemies();

	//void brain(unsigned i);
	//bool nodeExistInList(std::pair<int, int> n, map <std::pair<int, int>, Node>& l);
	//void addAdjectentCell(std::pair <int, int>& n);
	//float distance(int x1, int y1, int x2, int y2);
	//std::pair<int, int> bestNode(map <std::pair<int, int>, Node> l);
	//void addToClosedList(std::pair<int, int>& p);
	//vector<std::pair<int, int>> recoverPath(Node start, Node objectif);

	inline Arena getArena();
	//sf::Vector2f getNextPos(unsigned idEnemy, bool eraseFirst);


	/*int findDirection(unsigned idEnemy, vector < std::pair<int, int> >v);*/


	void moveToPos(unsigned idEnemy, std::vector < std::pair<int, int> >v);
	void shoot(int idPlayer);
	void slice(int idPlayer);
	void playerMoving(bool moving);

	std::vector<std::pair<float, float>> trajectoireBalle(int idPlayer);
	void moveBall(std::vector<std::pair<float, float>> vec);
	inline const  sf::RectangleShape & getlifebarre() const;
	inline bool isBrainLocked()const;
	inline void setBrainLock(bool lock);

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

unsigned Game::getNbObstacles()
{
	return arena_.getNbObstacles();
}

sf::RectangleShape Game::getObstacle(unsigned i)
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
Arena Game::getArena() {
	return arena_;
}

const sf::RectangleShape & Game::getlifebarre() const {
	return	players_.at(0).getlifebar();
}

void Game::removeEnemy(unsigned i) {
	/* enemies_.at(i) = Enemy(enemies_.at(i).getPositionFirst(), 1, this);*/
	 // TODO

}

bool Game::isBrainLocked()const {
	return brainLock;
}
void Game::setBrainLock(bool lock) {
	brainLock = lock;
}

void Game::setNbEnemies(unsigned nb) {
	nbEnemies = nb;
}

void Game::nextWave() {
	waveLevel++;
	nbEnemies = fib(waveLevel);
}

int Game::getRemainingEnemies() const {
	return nbEnemies;
}

int Game::fib(int x) const {
	if (x == 0)
		return 0;

	if (x == 1)
		return 1;

	return fib(x - 1) + fib(x - 2);
}

int Game::getWave() const {
	return waveLevel;
}

void Game::setEnemyPlayerMoving(int i, bool isMoving) {
	enemies_.at(i).setPlayerMoving(isMoving);
}

void Game::setEnemyHitTextureDepart(int i)
{
	enemies_.at(i).setHitTextureDepart();
}
#include <iostream>
void Game::removeDeadEnemies() {
	std::cout << "Before erase" << std::endl;
	enemies_.erase(std::remove_if(enemies_.begin(),
		enemies_.end(),
		[](Enemy & enemy) {
		std::cout << "Inside lambda" << std::endl;
		if (!enemy.isDead && enemy.getPv() == 0) {
			enemy.isDead = true;
			enemy.getthreads()->detach();
			return true;
		}
		else {
			return false;
		}
	}), enemies_.end());

	std::cout << "After erase" << std::endl;
}