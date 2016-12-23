#pragma once
#include "Character.h"

class Enemy : public Character {

public:
	Enemy(Position position, int pv);
	void uptadeSpritePosition();

};