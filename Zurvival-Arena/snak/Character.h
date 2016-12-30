#pragma once

#include "SFML/Graphics.hpp"
#include "Position.h"
#include <iostream>
#pragma region variables
enum State { Idle, Moving };
enum Direction { Up, Left, Right, Down };

#pragma endregion variables

class Character 
{
protected:
	sf::Vector2i anim{ 1,Up };
	sf::Texture* perso_;
	sf::Sprite* spritePerso_;

private:
	unsigned num_;
	State state_;
	unsigned pv_;
	Position position_;	
	sf::RectangleShape hitbox_;
	bool updateFps = true;
	
public:
	void setFillColor(sf::Color c);
	void setOutlineColor(sf::Color c);
	void setOutlineThickness(int i);
	void setSize(float f1, float f2);
	void slice(); //futur méthode pour trancher dans le lard mes gaillards

public:
	
	void setPositionHitbox(float f1, float f2);
	void setPosition(unsigned x, unsigned y);
	void move(float f1, float f2);	
	inline Character();
	inline Character(Position position,int pv);
	inline unsigned getPv() const;
	inline const sf::RectangleShape &getHitbox() const;
	inline const Position &getPosition() const;
	inline  sf::Sprite* getSprite() const;
	inline void setPositionSprite(sf::Vector2f p);
	inline void setAnimX(Direction direction);
	inline void setAnimY(Direction direction);
	inline const State& getState() const;
	inline void setState(State s);
	void removePv(); // mettre en privé et redef dans game
	void manageSprite(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);
	inline sf::Vector2i getAnim();
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
	setFillColor(sf::Color::Black);
	setPositionHitbox(10, 10);
	setSize(30, 30);
	setOutlineThickness(1);
	pv_ = 100;
}

Character::Character(Position position, int pv):position_(position),pv_(pv){

	setPositionHitbox(position.getX(), position.getY());
	setSize(30,30);
	setFillColor(sf::Color::Red);
	//hitbox_.setTexture(&perso_);
	pv_ = 100;

}

 sf::Sprite * Character::getSprite() const {

	return spritePerso_;
}
void Character::setPositionSprite(sf::Vector2f p) {
	spritePerso_->setPosition(p);
}

void Character::setAnimX(Direction direction) {
	anim.x = direction;
}

void Character::setAnimY(Direction direction) {
	anim.y = direction;
}

const State& Character::getState() const{
	return state_;
}

void Character::setState(State s) {
	state_ = s;
}

sf::Vector2i Character::getAnim() {
	return anim;
}