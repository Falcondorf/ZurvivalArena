#pragma once

#include "SFML/Graphics.hpp"
#include "Position.h"

using namespace sf;

class Character 
{
private:
	unsigned pv_;
	Position position_;
	RectangleShape hitbox_;

public:


	void move(float f1, float f2);
	void setPosition(float f1, float f2);
	void setFillColor(Color c);
	void setOutlineColor(Color c);
	void setOutlineThickness(int i);
	void setSize(float f1, float f2);
	inline Character();
	inline unsigned getPv() const;
	inline const RectangleShape &getHitbox() const;
	inline const Position &getPosition() const;
};

unsigned Character::getPv() const {
	return pv_;
}

const RectangleShape & Character::getHitbox() const {
	return hitbox_;
}


const Position & Character::getPosition() const {
	return position_;
}

Character::Character() {

}