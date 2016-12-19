#pragma once

#include "SFML/Graphics.hpp"
#include <vector>


class Arena
{
private:
	unsigned width_;
	unsigned height_;
	std::vector<sf::RectangleShape> obstacles;

public:
	Arena()=default;
	Arena(unsigned width,unsigned height);
	inline const std::vector<sf::RectangleShape> & getObstacles() const;

	//taille de l'arène
	//liste des items Rect
	//liste d'enemis
	//liste de joueur
};


const std::vector<sf::RectangleShape> & Arena::getObstacles() const {
	return obstacles;
}