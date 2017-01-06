#pragma once

#include "Character.h"
#include <string>
#include <thread>

struct Node2 {
	sf::Vector2f parent;
	sf::Vector2f position;
	unsigned gValue;
	unsigned hValue;
	unsigned fValue;
};
class Game;
class Enemy : public Character {
private:
	unsigned start = 0;
	unsigned idLevel=1;

	Game * game=nullptr;
	std::vector<std::pair<int, int>> pathToPlayer;
	int indicePath;
	bool textChange = false;
	unsigned id;
	std::thread threadEnemies;

	Position positionFirst;
	std::map <std::pair<int, int>, Node2> openList;
	std::map <std::pair<int, int>, Node2> closedList;
	bool playerMove;
	
	bool inversion = false;
	void brain();
	void addAdjectentCell(std::pair<int, int>& n);
	float distance(int x1, int y1, int x2, int y2);
	std::pair<int, int> bestNode(std::map <std::pair<int, int>, Node2> l);
	void addToClosedList(std::pair<int, int>& p);
	std::vector<std::pair<int, int>> recoverPath(Node2 start, Node2 objectif);
	bool nodeExistInList(std::pair<int, int> n, std::map<std::pair<int, int>, Node2>& l);
	int findDirection(std::vector < std::pair<int, int> >v);
	void moveToPos(std::vector < std::pair<int, int> >v);

public:

	Enemy(Position position, int pv,unsigned id, Game * gam);
	void uptadeSpritePosition();
	inline void setPath(std::vector<std::pair<int, int>> p);
	inline std::vector<std::pair<int, int>> getPath() const;
    void setHitTexture();
	bool getPlayerMoving();
	void setPlayerMoving(bool b);
	int getIndicePath() const;
	void incrementIndicePath();
	void resetIndicePath();
	void Enemy::setHitTextureDepart();
	void Enemy::setHitTextureHit();
	void startMovingEnemies();
	inline void reload();
	void functionMovingEnemies();
	inline std::thread * getthreads();
	inline const Position &getPositionFirst() const;
	inline unsigned getId()const;
	bool isDead = false;
	void spriteLevel();
	void nextLevel();
	void loadTextureStart();
	void loadTexture();
};

void Enemy::reload() {
	start = 0;
	//threadEnemies.detach();
	//threadEnemies.~thread();
	startMovingEnemies();
}


void Enemy::setPath(std::vector<std::pair<int, int>> p) {
	pathToPlayer = p;
}
std::vector <std::pair<int, int>> Enemy::getPath() const {
	return pathToPlayer;
}

std::thread* Enemy::getthreads() {
	return &threadEnemies;
}
const Position & Enemy::getPositionFirst() const {
	return positionFirst;
}

unsigned Enemy::getId()const {
	return id;
}


