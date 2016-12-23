#pragma once

#include "character.h"
#include <string>
class Heroes : public Character
{
	unsigned num_;
public:
	inline Heroes(Position pos, int pv, unsigned num);
	inline Heroes(std::string name);

	inline std::string getName() const;
private:

	std::string name_;

};

Heroes::Heroes(Position pos, int pv, unsigned num) :Character(pos, pv), num_(num){
	perso_ = new sf::Texture();
	switch (num) {
	case 0:

		if (!perso_->loadFromFile("jake2.png")) {

			std::cout << "error loading image" << std::endl;
		}
		break;
	case 1:
		if (!perso_->loadFromFile("player2.png")) {
			std::cout << "error loading image" << std::endl;
		}
		break;
	}
	spritePerso_ = new sf::Sprite();
	spritePerso_->setTexture(*perso_);
	spritePerso_->setTextureRect(sf::IntRect(anim.x * 56, anim.y * 85, 56, 85));
	spritePerso_->setScale(sf::Vector2f(0.9, 0.5));
}

inline Heroes::Heroes(std::string name)
{

}



std::string Heroes::getName() const {

	return name_;
}