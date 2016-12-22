#pragma once

#include "SFML/Graphics.hpp"
#include "Position.h"
#include <iostream>


class Character 
{
private:
	unsigned num_;
	unsigned pv_;
	Position position_;
	sf::RectangleShape hitbox_;
	sf::Texture perso_;

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
	inline sf::Texture getTextureChar() const;
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
	setSize(30,30);
	switch (num) {
	case 0:
		if (!perso_.loadFromFile("jake2.png")) {
			std::cout << "error loading image" << std::endl;
		}
		setFillColor(sf::Color::Transparent);
		setOutlineColor(sf::Color::Yellow);
		break;
	case 1:
		if (!perso_.loadFromFile("player2.png")) {
			std::cout << "error loading image" << std::endl;
		}
		setFillColor(sf::Color::Transparent);
		setOutlineColor(sf::Color::Green);
		break;
	}		
	setOutlineThickness(1);

	
	hitbox_.setTexture(&perso_);




}

sf::Texture  Character::getTextureChar() const {
	return perso_;
}