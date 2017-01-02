#pragma once
#ifndef Enemy_h
#define Enemy_h


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
using namespace sf;
using namespace std;

struct Node {
	sf::Vector2f parent;
	sf::Vector2f position;
	unsigned gValue;
	unsigned hValue;
	unsigned fValue;
};
extern class Enemy;
class Game : nvs::Subject {
private:
	bool brainLock=false;
	unsigned nbEnemies;
	bool textChange = false;
	Arena arena_;
	vector<Character> players_;
	vector<Enemy> enemies_;
	unique_ptr<thread> threadEnemies;
	/*void functionMovingEnemies();*/
	bool gameFinish = false;
	map <pair<int, int>, Node> openList;
	map <pair<int, int>, Node> closedList;
	/*void generateSuccessors(Vector2f pos, std::vector<Node> *successors, Node parent);
	bool parcourOpen(std::vector<Node> openList, sf::Vector2f position, int fValue);
	bool parcourClosed(std::vector<Node> closedList, sf::Vector2f position, int fValue);*/
	bool inversion = false;
	bool playerMove = false;
	vector< vector<pair<int, int>> > pathToEnemy;
	

public:
	bool isFinishGame();
	inline const vector<Character> &  getPlayers() const;
	Game(unsigned width, unsigned height);
	bool hasCollision(int idPlayer, float movex, float movey);
	static bool intersects(const RectangleShape & rect1, const RectangleShape & rect2);
	void move(int idplayer, float xMove, float yMove);
	unsigned getNbPlayers()const;
	const RectangleShape &getHitBoxChar(int i)const;
	inline void addPlayer(float posX, float posY, int pv = 3);
	void addEnemy(float posX, float posY, int pv = 1);
	vector<Enemy> & getEnemies();
	inline unsigned getNbObstacles();
	inline RectangleShape getObstacle(unsigned i);
	inline void setPositionCharacter(unsigned i);
	inline void setAnimXCharacter(unsigned i, Direction direction);
	inline void setAnimYCharacter(unsigned i, Direction direction);
	inline void setStateCharacter(unsigned i);
	inline void stateInitializerCharacters();
	inline void finishGame();
	inline void setNbEnemies(unsigned nb);
	inline void manageGame(unsigned i, float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);
	void manageEnemi(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);
	
	inline void removeEnemy(unsigned);
	void startMovingEnemies();

	//void brain(unsigned i);
	//bool nodeExistInList(pair<int, int> n, map <pair<int, int>, Node>& l);
	//void addAdjectentCell(pair <int, int>& n);
	//float distance(int x1, int y1, int x2, int y2);
	//pair<int, int> bestNode(map <pair<int, int>, Node> l);
	//void addToClosedList(pair<int, int>& p);
	//vector<pair<int, int>> recoverPath(Node start, Node objectif);

	inline Arena getArena();
	//sf::Vector2f getNextPos(unsigned idEnemy, bool eraseFirst);


	/*int findDirection(unsigned idEnemy, vector < pair<int, int> >v);*/
	
	
	void moveToPos(unsigned idEnemy, vector < pair<int, int> >v);
	void shoot(int idPlayer);
	void slice(int idPlayer);
	void playerMoving(bool moving);

	 std::vector<std::pair<float, float>> trajectoireBalle(int idPlayer);
	 void moveBall(std::vector<std::pair<float, float>> vec);
	 inline const  sf::RectangleShape & getlifebarre() const ;
	 inline bool isBrainLocked()const;
	 inline void setBrainLock(bool lock);

	 /////// Interaction Joueur Ennemi
	 void removePvOfPlayer(unsigned i);
	 void setLifeBarOfPlayer(unsigned i, sf::RectangleShape rce);

};

#endif // !Enemy_h


const vector<Character> &  Game::getPlayers() const {

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

RectangleShape Game::getObstacle(unsigned i)
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

 const sf::RectangleShape & Game::getlifebarre() const  {
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