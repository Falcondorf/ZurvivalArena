#include "Character.h"
#include <iostream>


using namespace sf;

void Character::move(float f1, float f2) {
	hitbox_.move(f1, f2);
}

void Character::setPositionHitbox(float f1, float f2) {
	hitbox_.setPosition(f1, f2);
}

void Character::setPosition(unsigned x, unsigned y) {
	position_.setX(x);
	position_.setY(y);
}
void Character::setFillColor(Color c) {
	hitbox_.setFillColor(c);
	lifebar_.setFillColor(c);
}
void Character::setOutlineColor(Color c) {
	hitbox_.setOutlineColor(c);
}
void Character::setOutlineThickness(int i) {
	hitbox_.setOutlineThickness(i);
}

void Character::setSize(float f1, float f2) {
	hitbox_.setSize(Vector2f(f1, f2));
}

void Character::removePv(int damage) {
	if (pv_ > 0) {
		std::cout <<"pv : " << pv_ << std::endl;
		pv_ -= damage;
	}

}

void Character::manageSprite(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time) {
	if (updateFps_) { 
		fpsCount += fpsSpeed *time.restart().asSeconds();
	}
	else {
		fpsCount = 0;
	}
	if (fpsCount >= switchFps) {
		anim.x++;
		if (anim.x * 76 >= perso_->getSize().x) {
			anim.x = 0;
		}
	}
	spritePerso_->setTextureRect(sf::IntRect(anim.x * 76, anim.y * 95, 76, 95));

}