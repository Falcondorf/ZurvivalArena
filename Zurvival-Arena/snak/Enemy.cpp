#include "Enemy.h"

Enemy::Enemy(Position position, int pv): Character (position, pv)
{
	perso_ = new sf::Texture();
		if (!perso_->loadFromFile("pics/jake3.png")) {
			std::cout << "error loading image" << std::endl;
		}
		setFillColor(sf::Color::Yellow);
	spritePerso_ = new sf::Sprite();
	spritePerso_->setTexture(*perso_);
	spritePerso_->setTextureRect(sf::IntRect(anim.x * 56, anim.y * 85, 56, 85));
	spritePerso_->setScale(sf::Vector2f(0.9, 0.5));
}