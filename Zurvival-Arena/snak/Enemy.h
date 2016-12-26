#pragma once
#include "Character.h"

class Enemy : public Character {
private:

public:
	Enemy(Position position, int pv);
	void uptadeSpritePosition();


};