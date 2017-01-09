#pragma once
/*!
* \brief Classe représentant la position d'un charactere
*\file position.h
*\author Aynaou Dupont Fakir Bauwens
*/
class Position
{
private:
	/*!
	*\brief L abscisse de la position. 
	*/
	unsigned x_;
	/*!
	*\brief L ordonnée de la position
	*/
	unsigned y_;
public:
	/*!
	* \brief Constructeur de la classe position.
	*/
	inline Position();
	/*!
	* \brief Constructeur de la classe position avec parametre.
	* \param y abscisse de la position du joueur.
	* \param x ordonnée de la position du joueur.
	*/
	inline Position(unsigned x, unsigned y);

	/*!
	* \brief Geteur de l abscisse de la position du joueur.
	* \return Renvoie l abcisse de la position du joueur.
	*/
	inline unsigned getX() const;
	/*!
	* \brief Geteur ordonnée de la position du joueur.
	* \return Renvoie ordonnée de la position du joueur.
	*/
	inline unsigned getY() const;
	/*!
	* \brief Seter de l abscisse de la position du joueur.
	* \param x le nouvelle abscisse de la position du joueur
	*/
	inline void setX(unsigned x);
	/*!
	* \brief Seter ordonnée de la position du joueur.
	* \param y le nouvelle ordonnée de la position du joueur
	*/
	inline void setY(unsigned y);
};

Position::Position() :x_(0), y_(0) {}

Position::Position(unsigned x, unsigned y) : x_(x), y_(y) {}

unsigned Position::getX() const {
	return this->x_;
}

unsigned Position::getY() const {
	return this->y_;
}

void Position::setX(unsigned x) {
	this->x_ = x;
}
void Position::setY(unsigned y) {
	this->y_ = y;
}
