#pragma once

#include "SFML/Graphics.hpp"
#include "Position.h"

using namespace sf;

class Character : RectangleShape
{
private:
	unsigned pv_;
	Position position_;

public:

	inline   Character();
	~Character();
	inline unsigned getPv() const;
	inline const Position &getPosition() const;
};

unsigned Character::getPv() const {
	return pv_;
}

const Position & Character::getPosition() const {
	return position_;
}

Character::Character() {

}