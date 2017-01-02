#pragma once
#ifndef Game_H
#define Game_H


#include "Game.h"

#include "Character.h"
#include "string"
#include <thread>
using namespace std;


struct Node2 {
	sf::Vector2f parent;
	sf::Vector2f position;
	unsigned gValue;
	unsigned hValue;
	unsigned fValue;
};
extern class Game;
class Enemy : public Character {
private:
	unsigned start = 0;
	Game * game=nullptr;
	vector<pair<int, int>> pathToPlayer;
	int indicePath;
	bool textChange = false;
	unsigned id;
	thread threadEnemies;

	Position positionFirst;
	map <pair<int, int>, Node2> openList;
	map <pair<int, int>, Node2> closedList;
	bool playerMove;
	
	bool inversion = false;
	void brain();
	void addAdjectentCell(pair<int, int>& n);
	float distance(int x1, int y1, int x2, int y2);
	pair<int, int> bestNode(map <pair<int, int>, Node2> l);
	void addToClosedList(pair<int, int>& p);
	vector<pair<int, int>> recoverPath(Node2 start, Node2 objectif);
	bool nodeExistInList(std::pair<int, int> n, std::map<std::pair<int, int>, Node2>& l);
	int findDirection(vector < pair<int, int> >v);
	void moveToPos(vector < pair<int, int> >v);

public:
	Enemy(Position position, int pv,unsigned id, Game * gam);
	void uptadeSpritePosition();
	inline void setPath(vector<pair<int, int>> p);
	inline vector<pair<int, int>> getPath() const;
    void setHitTexture();
	bool getPlayerMoving();
	void setPlayerMoving(bool b);
	int getIndicePath() const;
	void incrementIndicePath();
	void resetIndicePath();
	void Enemy::setHitTextureDepart();
	void Enemy::setHitTextureHit();
	void startMovingEnemies();
	void functionMovingEnemies();
	inline thread* getThreads();
	inline const Position &getPositionFirst() const;
	inline unsigned getId()const;
};
#endif // !Game_H

void Enemy::setPath(vector<pair<int, int>> p) {
	pathToPlayer = p;
}
vector <pair<int, int>> Enemy::getPath() const {
	return pathToPlayer;
}

thread* Enemy::getThreads() {
	return &threadEnemies;
}
const Position & Enemy::getPositionFirst() const {
	return positionFirst;
}

unsigned Enemy::getId()const {
	return id;
}