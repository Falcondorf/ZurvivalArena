#pragma once

#include "SFML/Graphics.hpp"
#include "Position.h"
#pragma region variables
enum State { Idle, Moving };
enum Direction { Down, Left, Right, Up };
#pragma endregion variables

class Character
{
protected:
	sf::Vector2i anim{ 1, Up };
	sf::Texture* perso_;
	sf::Sprite* spritePerso_;
	int pv_;
	void setPositionHitbox(float f1, float f2);
	void setPosition(unsigned x, unsigned y);
	

private:
	int num_;
	State state_;
	Position position_;
	sf::RectangleShape hitbox_;
	sf::RectangleShape lifebar_;
	bool updateFps_ = true;
	void setFillColor(sf::Color c);
	void setOutlineColor(sf::Color c);
	void setOutlineThickness(int i);
	void setSize(float f1, float f2);


public:

	void removePv(unsigned damage);
	void move(float f1, float f2);	
	void manageSprite(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);

	inline Character();
	inline Character(Position position, int pv);
	inline int getPv() const;
	inline const sf::RectangleShape &getHitbox() const;
	inline const Position &getPosition() const;
	inline  sf::Sprite* getSprite() const;
	inline void setPositionSprite(sf::Vector2f p);
	inline void setAnimX(Direction direction);
	inline void setAnimY(Direction direction);
	inline const State& getState() const;
	inline void setState(State s);
	inline const sf::Vector2i & getAnim() const;
	inline void setPv(unsigned pv);
	inline unsigned getNum() const;
	inline const sf::RectangleShape &getlifebar() const;
	inline void setlifebar(sf::RectangleShape rce);
};

int Character::getPv() const {
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

	setPositionHitbox(0, 0);
	setSize(30, 30);
	setOutlineThickness(1);
	pv_ = 100;
}

Character::Character(Position position, int pv) :position_(position), pv_(pv) {

	setPositionHitbox(position.getX(), position.getY());
	lifebar_.setSize(sf::Vector2f(50, 2));
	setSize(30, 30);
	setFillColor(sf::Color::Red);

	//hitbox_.setTexture(&perso_);

	pv_ = 100; // Changer ça !!!

}

sf::Sprite * Character::getSprite() const {

	return spritePerso_;
}
void Character::setPositionSprite(sf::Vector2f p) {

	spritePerso_->setPosition(sf::Vector2f(p.x - 20, p.y - 5));
	lifebar_.setPosition(sf::Vector2f(p.x, p.y - 35));

}

void Character::setAnimX(Direction direction) {
	anim.x = direction;
}

void Character::setAnimY(Direction direction) {
	anim.y = direction;
}

const State& Character::getState() const {
	return state_;
}

void Character::setState(State s) {
	state_ = s;
}

const sf::Vector2i & Character::getAnim() const {
	return anim;
}

void Character::setPv(unsigned pv) {
	pv_ = pv;
}

const sf::RectangleShape& Character::getlifebar() const {
	return lifebar_;
}

void Character::setlifebar(sf::RectangleShape rce) {
	lifebar_ = rce;

}

unsigned Character::getNum() const {
	return num_;
}