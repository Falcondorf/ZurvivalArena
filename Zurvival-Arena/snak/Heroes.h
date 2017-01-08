#pragma once

#include "character.h"
#include <string>
#include "ZurvivalException.h"

/*!
*\brief Class qui represente le joueur.
*\file Heroes.h
*\author Aynaou Dupont Fakir Bauwens
*/
class Heroes : public Character
{
	/*!
	* \brief identifiant du joueur
	*/
	unsigned num_;
public:

	/*!
	* \brief Constructeur de Heroes avec parametres.
	* \param pos la position de départ du joueur
	* \param pv le nombre de point de vie
	* \param num l identifiant du joueur
	*/
	inline Heroes(Position pos, int pv, unsigned num);

};

Heroes::Heroes(Position pos, int pv, unsigned num) :Character(pos, pv), num_(num) {
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
