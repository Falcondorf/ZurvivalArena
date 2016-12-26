#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

class Arena
{
private:
	unsigned width_;
	unsigned height_;
	std::vector<sf::RectangleShape> obstacles;
	std::vector<std::vector<bool>> tiles_;

public:
	Arena()=default;
	Arena(unsigned width,unsigned height);
	inline unsigned getWidth()const;
	inline unsigned getHeight() const;
	void setTiles();
	inline unsigned getNbObstacles();
	inline sf::RectangleShape getObstacle(unsigned index);
	inline std::vector<std::vector<bool>> getTiles();
	bool isFree(float x, float y);
	void printTiles();
};


unsigned Arena::getNbObstacles()
{
	return obstacles.size();
}

sf::RectangleShape Arena::getObstacle(unsigned index)
{
	return obstacles[index];
}

unsigned Arena::getWidth() const {
	return width_;
}

unsigned Arena::getHeight() const {
	return height_;
}
std::vector<std::vector<bool>> Arena::getTiles() {
	return tiles_;
}
