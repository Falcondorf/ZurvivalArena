#pragma once
#include "Character.h"
#include "string"
using namespace std;
class Enemy : public Character {
private:
	vector<pair<int, int>> pathToPlayer;
	int indicePath;
	bool playerMove;
public:
	Enemy(Position position, int pv);
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

};

void Enemy::setPath(vector<pair<int, int>> p) {
	pathToPlayer = p;
}
vector <pair<int, int>> Enemy::getPath() const {
	return pathToPlayer;
}