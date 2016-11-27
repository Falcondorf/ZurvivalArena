#pragma once


#include "Character.h"


class Enemy:public Character

{
private:

public:
	inline Enemy(unsigned pv, HitBox hb);

};

Enemy::Enemy(unsigned pv,HitBox hb):Character(pv,hb) {

}