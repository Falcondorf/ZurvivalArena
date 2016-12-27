#pragma once
#include "Arena.h"
#include <vector>
#include "Heroes.h"
#include "Enemy.h"
#include <thread>
#include <chrono>
#include <map>
#include <utility>
using namespace sf;
using namespace std;
struct Node {
	sf::Vector2f parent;
	sf::Vector2f position;
	unsigned gValue;
	unsigned hValue;
	unsigned fValue;
};
class Game {
private:
	Arena arena_;
	vector<Character> players_;
	vector<Enemy> enemies_;
	unique_ptr<thread> threadEnemies;
	void functionMovingEnemies();
	bool gameFinish = false;
	unsigned spaceCase(Vector2f pos);
	map <pair<int, int>, Node> openList;
	map <pair<int, int>, Node> closedList;
	/*void generateSuccessors(Vector2f pos, std::vector<Node> *successors, Node parent);
	bool parcourOpen(std::vector<Node> openList, sf::Vector2f position, int fValue);
	bool parcourClosed(std::vector<Node> closedList, sf::Vector2f position, int fValue);*/
	bool inversion = false;

public:
	inline const vector<Character> &  getPlayers() const;
	inline Game(unsigned width, unsigned height);
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
	inline void manageGame(unsigned i, float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);
	void manageEnemi(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);
	void brain(Enemy &e);
	void startMovingEnemies();
	bool nodeExistInList(pair<int, int> n, map <pair<int, int>, Node>& l);
	void addAdjectentCell(pair <int, int>& n);
	float distance(int x1, int y1, int x2, int y2);
	pair<int, int> bestNode(map <pair<int, int>, Node> l);
	void addToClosedList(pair<int, int>& p);
	vector<pair<int,int>> recoverPath(Node start,Node objectif);
	inline Arena getArena();
	sf::Vector2f getNextPos(unsigned idEnemy);
	int findDirection(unsigned idEnemy);
	void moveToPos(unsigned idEnemy);

};

Game::Game(unsigned width, unsigned height) {
	arena_ = Arena(width, height);
}

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