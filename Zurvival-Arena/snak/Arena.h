#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

/*!
*\brief Class qui represente l'arene du jeu.
*\file arena.h
*\author Aynaou Dupont Fakir Bauwens
*/

class Arena
{
private:
	/*!
	* \brief width La longueur de l'arene.  
	*/
	unsigned width_;
	/*!
	* \brief height La longueur de l'arene.
	*/
	unsigned height_;

	/*!
	* \brief obstacles_ Les obstacles presents dans l'arene tels que les maisons,puits... 
	*/
	std::vector<sf::RectangleShape> obstacles_;

	/*!
	 * \brief Matrice boolean qui represente les obstacles.
	 */
	std::vector<std::vector<bool>> tiles_;

public:
	/*!
	* \brief Constructeur de Arena par defaut
	*/
	Arena() = default;
	/*!
	* \brief Constructeur de Arena avec parametre.
	* \param width la longeur de l'arene
	* \param height la largeur de l'arene
	*/
	Arena(unsigned width, unsigned height);
	/*!
	* \brief Permet de savoir si une case est accessible.
	* \param x l'abcisse de la position a tester
	* \param `y l'ordonnée de la position a vendre
	* \return vrai si la case est accessible.
	*/
	bool isFree(float x, float y);
	/*!
	* \brief permet d'initialiser la matrice d'accessiblité.
	*/
	void setTiles();
	/*!
	* \brief Geteur de la longueur de l'arene.
	* \return la longueur de l'arene.
	*/
	inline unsigned getWidth()const;
	/*!
	* \brief Geteur de la hauteur de l'arene.
	* \return la honteur de l'arene.
	*/
	inline unsigned getHeight() const;
	/*!
	* \brief Geteur le nombre d'obstacle dans l'arene.
	* \return le nombre d'obstacle dans l'arene.
	*/
	inline unsigned getNbObstacles() const;
	/*!
	* \brief Geteur d'un obstacle dans l'arene.
	*\param index l'indicede l'obstacle qu'on veut.
	* \return Un obstacle de present dans l'arene. 
	*/
	inline const  sf::RectangleShape & getObstacle(unsigned index) const;
	/*!
	* \brief Geteur de la matrice d'accessibilité  de l'arene.
	* \return La matrice d'accessibilité de l'arene.
	*/
	inline const  std::vector<std::vector<bool>> & getTiles() const;
};


unsigned Arena::getNbObstacles()const
{
	return obstacles_.size();
}

const sf::RectangleShape  & Arena::getObstacle(unsigned index) const
{
	return obstacles_[index];
}

unsigned Arena::getWidth() const {
	return width_;
}

unsigned Arena::getHeight() const {
	return height_;
}
const std::vector<std::vector<bool>> & Arena::getTiles()const {
	return tiles_;
}
