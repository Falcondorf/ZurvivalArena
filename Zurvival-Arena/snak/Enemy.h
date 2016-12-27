#pragma once
#include "Character.h"
#include "string"
using namespace std;
class Enemy : public Character {
private:
	vector<pair<int, int>> pathToPlayer;
public:
	Enemy(Position position, int pv);
	void uptadeSpritePosition();
	inline void setPath(vector<pair<int, int>> p);
	inline vector<pair<int, int>> getPath();


};

void Enemy::setPath(vector<pair<int, int>> p) {
	pathToPlayer = p;
}
vector <pair<int, int>> Enemy::getPath() {
	return pathToPlayer;
}