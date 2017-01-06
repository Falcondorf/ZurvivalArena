#pragma once

#include "character.h"
#include <string>
#include "ZurvivalException.h"

class Heroes : public Character
{
	unsigned num_;
public:
	inline Heroes(Position pos, int pv, unsigned num);
	inline Heroes(std::string name);
	//inline std::vector<int,int> trajectoireBalle();
	inline std::string getName() const;
private:

	std::string name_;

};

Heroes::Heroes(Position pos, int pv, unsigned num) :Character(pos, pv), num_(num){
	setPv(10000);
	perso_ = new sf::Texture();
	switch (num) {
	case 0:

		if (!perso_->loadFromFile("pics/jake2.png")) {
			throw ZurvivalException("error loading image");
		}
		break;
	case 1:
		if (!perso_->loadFromFile("pics/jake2.png")) {
			throw ZurvivalException("error loading image");
		}
		break;
	}
	spritePerso_ = new sf::Sprite();
	spritePerso_->setTexture(*perso_);
	spritePerso_->setTextureRect(sf::IntRect(anim.x * 56, anim.y * 85, 56, 85));
	spritePerso_->setScale(sf::Vector2f(0.9, 0.5));
	setPositionSprite(getHitbox().getPosition());
}

inline Heroes::Heroes(std::string name)
{

}

std::string Heroes::getName() const {

	return name_;
}
