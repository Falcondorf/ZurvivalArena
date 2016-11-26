#pragma once

#include "Position.h"

class Character
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