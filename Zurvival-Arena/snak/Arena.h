#pragma once

#include "SFML/Graphics.hpp"
#include <vector>


class Arena
{
private:
	unsigned width_;
	unsigned height_;
	std::vector<sf::RectangleShape> obstacles;
	inline const std::vector<sf::RectangleShape> & getObstacles() const;

public:
	Arena()=default;
	Arena(unsigned width,unsigned height);	
	inline unsigned getNbObstacles();
	inline sf::RectangleShape getObstacle(unsigned index);

};


const std::vector<sf::RectangleShape> & Arena::getObstacles() const {
	return obstacles;
}

unsigned Arena::getNbObstacles()
{
	return obstacles.size();
}

sf::RectangleShape Arena::getObstacle(unsigned index)
{
	return obstacles[index];
}
