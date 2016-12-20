#pragma once

#include "SFML/Graphics.hpp"
#include "Position.h"


class Character 
{
private:
	unsigned num_;
	unsigned pv_;
	Position position_;
	sf::RectangleShape hitbox_;

	void setPosition(float f1, float f2);
	void setFillColor(sf::Color c);
	void setOutlineColor(sf::Color c);
	void setOutlineThickness(int i);
	void setSize(float f1, float f2);

public:
	void move(float f1, float f2);	
	inline Character();
	inline Character(Position position,int pv, unsigned num);
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

Character::Character() {}

Character::Character(Position position, int pv, unsigned num):position_(position),pv_(pv), num_(num){
	setPosition(position.getX(), position.getY());
	setSize(20,20);
	switch (num) {
	case 0:
		setFillColor(sf::Color::Red);
		setOutlineColor(sf::Color::Yellow);
		break;
	case 1:
		setFillColor(sf::Color::Blue);
		setOutlineColor(sf::Color::Green);
		break;
	}		
	setOutlineThickness(1);

}