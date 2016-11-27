#pragma once


#include "HitBox.h"
class Character
{
protected:
	unsigned pv_;
	HitBox hbChar_;
	Direction::dir direction_;

public:

	inline   Character();
	inline Character(unsigned pv, HitBox hbChar);
	
	inline unsigned getPv() const;
	
	inline void move(Direction::dir direction);
	inline unsigned getXDL() const;
	inline unsigned getXHR() const;
	inline unsigned getYDL() const;
	inline unsigned getYHR() const;

};

Character::Character(unsigned pv, HitBox hbChar) :pv_(pv), hbChar_(hbChar),direction_(Direction::dir::up) {

}

unsigned Character::getXDL() const {
	return hbChar_.getDL().getX();
}

unsigned Character::getXHR() const {
	return hbChar_.getHR().getX();
}

unsigned Character::getYDL() const {
	return hbChar_.getDL().getY();
}
unsigned Character::getYHR() const {
	return hbChar_.getHR().getY();
}


unsigned Character::getPv() const {
	return pv_;
}





Character::Character() {

}
void Character::move(Direction::dir direction) {
	direction_ = direction;
	hbChar_.move(direction);
	

}