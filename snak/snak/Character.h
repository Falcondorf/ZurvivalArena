#pragma once

#include "SFML/Graphics.hpp"
#include "Position.h"


class Character 
{
private:
	unsigned pv_;
	Position position_;
	sf::RectangleShape hitbox_;

public:


	void move(float f1, float f2);
	void setPosition(float f1, float f2);
	void setFillColor(sf::Color c);
	void setOutlineColor(sf::Color c);
	void setOutlineThickness(int i);
	void setSize(float f1, float f2);
	inline Character();
	inline unsigned getPv() const;
	inline const sf::RectangleShape &getHitbox() const;
	inline const Position &getPosition() const;
};

unsigned Character::getPv() const {
	return pv_;
}

const sf::RectangleShape & Character::getHitbox() const {
	return hitbox_;
}


const Position & Character::getPosition() const {
	return position_;
}

Character::Character() {

}