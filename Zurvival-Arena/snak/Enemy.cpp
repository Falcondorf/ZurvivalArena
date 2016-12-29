#include "Enemy.h"


Enemy::Enemy(Position position, int pv): Character (position, pv)
{
	perso_ = new sf::Texture();
		if (!perso_->loadFromFile("pics/jake3.png")) {
			std::cout << "error loading image" << std::endl;
		}
		playerMove = true;
		indicePath = 0;
	spritePerso_ = new sf::Sprite();
	spritePerso_->setTexture(*perso_);
	spritePerso_->setPosition(getHitbox().getPosition());
	spritePerso_->setTextureRect(sf::IntRect(anim.x * 56, anim.y * 85, 56, 85));
	spritePerso_->setScale(sf::Vector2f(0.9, 0.5));
}

void Enemy::uptadeSpritePosition() {
	spritePerso_->setPosition(getHitbox().getPosition());
}

bool Enemy::getPlayerMoving() {
	return playerMove;
}
void Enemy::setPlayerMoving(bool b) {
	playerMove = b;
}


int Enemy::getIndicePath()const {
	return indicePath;
}

void Enemy::incrementIndicePath() {
	indicePath++;
}
void Enemy::resetIndicePath() {
	indicePath = 0;
}
void Enemy::setHitTexture() {
	sf::Texture* perso = new sf::Texture();
	if (!perso->loadFromFile("pics/jake33.png")) {
		std::cout << "error loading image" << std::endl;
	}
	spritePerso_->setTexture(*perso);
}

void Enemy::setHitTextureDepart() {
	sf::Texture* perso = new sf::Texture();
	if (!perso->loadFromFile("pics/jake3.png")) {
		std::cout << "error loading image" << std::endl;
	}
	spritePerso_->setTexture(*perso);
}