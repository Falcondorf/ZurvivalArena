#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
#include <mutex>

class Arena
{
private:

	unsigned width_;
	unsigned height_;
	std::vector<sf::RectangleShape> obstacles_;
	std::vector<std::vector<bool>> tiles_;

public:
	Arena()=default;
	Arena(unsigned width,unsigned height);
	bool isFree(float x, float y);
	void setTiles();
	inline unsigned getWidth()const;
	inline unsigned getHeight() const;
	inline unsigned getNbObstacles() const;
	inline const  sf::RectangleShape & getObstacle(unsigned index) const;
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
