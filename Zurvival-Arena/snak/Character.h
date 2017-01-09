#pragma once

#include "SFML/Graphics.hpp"
#include "Position.h"
#pragma region variables
enum State { Idle, Moving };
enum Direction { Down, Left, Right, Up };
#pragma endregion variables



/*!
*\brief Class qui un personnage qui bouge dans le jeu.
*\file character.h
*\author Aynaou Dupont Fakir Bauwens Temsamani
*/

class Character
{
protected:
	/*!
	*\brief represente l'orientation du personnage.
	*/
	sf::Vector2i anim{ 1, Up };
	/*!
	*\brief represente la texture d'un personnage.
	*/
	sf::Texture* perso_;
	/*!
	*\brief represente le sprite d'un personnage.
	*/
	sf::Sprite* spritePerso_;
	/*!
	*\brief represente les pv d'un personnage.
	*/
	int pv_;
	/*!
	* \brief Seteur de la position de la hitbox du personnage.
	* \param f1 l'absicce de la position
	*\param f2 l'ordonnée de la position
	*/
	void setPositionHitbox(float f1, float f2);
	/*!
	* \brief Seteur de la position  du personnage.
	* \param x l'absicce de la position
	*\param y l'ordonnée de la position
	*/
	void setPosition(unsigned x, unsigned y);


private:
	/*!
	*\brief represente le numero du personnage.
	*/
	unsigned num_;
	/*!
	*\brief represente l'etat du personnage.
	*/
	State state_;
	/*!
	*\brief represente la position du personnage.
	*/
	Position position_;
	/*!
	*\brief represente la hitbox du personnage.
	*/
	sf::RectangleShape hitbox_;
	/*!
	*\brief represente la barre de vie du personnage.
	*/
	sf::RectangleShape lifebar_;
	/*!
	*\brief represente l'etat de l'update des images du personnage.
	*/
	bool updateFps_ = true;

	/*!
	* \brief Seteur de la couleur  du personnage.
	* \param c la couleur du personnage.
	*/

	void setFillColor(sf::Color c);
	/*!
	* \brief Seteur de la couleur du perimetre du personnage.
	* \param c la couleur du personnage.
	*/
	void setOutlineColor(sf::Color c);
	/*!
	* \brief Seteur de la couleur des ombres des personnages.
	* \param i l'intensité des ombres
	*/
	void setOutlineThickness(int i);
	/*!
	* \brief Seteur de la taille des personnages.
	* \param f1 la longeur de la taille de la hitbox.
	*\param f2 la largeur de la taille de la hitbox.
	*/
	void setSize(float f1, float f2);
public:
	/*!
	*\brief Méthode public permettant de retirer de la vie au joueur.
	* \param damage Le nombre de point de vie à retirer.
	*/
	void removePv(int damage);
	/*!
	*\brief Méthode public permettant de déplacer le joueur.
	*/
	void move(float f1, float f2);
	/*!
	*\brief Méthode public permettant de gèrer l'animation du sprite du joueur.
	*/
	void manageSprite(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);
	/*!
	*\brief Constructeur par défaut de la classe Character
	*/
	inline Character();
	/*!
	*\brief Constructeur de la class Character
	*\param position La position du character
	*\param pv Le nombre de point de vie du Character
	*/
	inline Character(Position position, int pv);
	/*!
	*\brief Accesseur de l'attribut privé pv
	*\return Le nombre de point de vit du character
	*/
	inline int getPv() const;
	/*!
	*\brief Accesseur de l'attribut privé hitbox_
	*\return Un rectangle correspondant à la hitbox du character.
	*/
	inline const sf::RectangleShape &getHitbox() const;
	/*!
	*\brief Accesseur de l'attribut privé position_
	*\return La position du character.
	*/
	inline const Position &getPosition() const;
	/*!
	*\brief Accesseur de l'attribut privé sprite_
	*\return Le sprite du character.
	*/
	inline  sf::Sprite* getSprite() const;
	/*!
	*\brief Setteur de l'attribut privé sprite_
	*\param p La nouvelle position du character.
	*/
	inline void setPositionSprite(sf::Vector2f p);
	/*!
	*\brief Setter permettant de mettre à jour l'attribut anim_
	*\param direction La nouvelle direction pour l'animation du character.
	*/
	inline void setAnimX(Direction direction);
	/*!
	*\brief Setter permettant de mettre à jour l'attribut anim_
	*\param direction La nouvelle direction pour l'animation du character.
	*/
	inline void setAnimY(Direction direction);
	/*!
	*\brief Accesseur de l'attribut privé state_
	*\return L'état du character.
	*/
	inline const State& getState() const;
	/*!
	*\brief Setter permettant de mettre à jour l'attribut state_
	*\param s Le nouvel état du character.
	*/
	inline void setState(State s);
	/*!
	*\brief Accesseur de l'attribut privé anim_
	*\return la valeur de l'attribut anim_
	*/
	inline const sf::Vector2i & getAnim() const;
	/*!
	*\brief Setter permettant de mettre à jour l'attribut pv
	*\param pv Le nouveau nombre de point de vie du character.
	*/
	inline void setPv(int pv);
	/*!
	*\brief Accesseur de l'attribut privé num_
	*\return L'identifiant du character.
	*/
	inline unsigned getNum() const;
	/*!
	*\brief Accesseur de l'attribut lifebar_
	*\return un rectangle correspondant à la barre de vie du character.
	*/
	inline const sf::RectangleShape &getlifebar() const;
	/*!
	*\brief Setter permettant de mettre à jour l'attribut lifebar_
	*\param rce La nouvelle barre de vie du Character.
	*/
	inline void setlifebar(sf::RectangleShape rce);
	inline void destructPointer();
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
	pv_ = 100; 

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

void Character::setPv(int pv) {
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
inline void Character::destructPointer() {
	delete spritePerso_;
	spritePerso_ = nullptr;
	delete perso_;
	perso_ = nullptr;
}