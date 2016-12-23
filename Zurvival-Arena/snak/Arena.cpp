#include "Arena.h"
#include "ZurvivalException.h"

Arena::Arena(unsigned width, unsigned height) : width_(width), height_(height) {
	if (width % 30 != 0 && height % 30 != 0) {
		throw ZurvivalException("No respect of size");
	}
	else {
		sf::RectangleShape top, left, right, bottom, obstacle;

		obstacle.setPosition(50, 50);
		obstacle.setSize(sf::Vector2f(200, 100));
		obstacle.setFillColor(sf::Color::Blue);

		top.setPosition(3, 0);
		top.setSize(sf::Vector2f(width - 2 * 3, 3));

		left.setPosition(0, 0);
		left.setSize(sf::Vector2f(3, height));

		right.setPosition(width - 3, 0);
		right.setSize(sf::Vector2f(3, height));

		bottom.setPosition(3, height - 3);
		bottom.setSize(sf::Vector2f(width - 2 * 3, -3));

		top.setFillColor(sf::Color(100, 100, 100));
		top.setOutlineColor(sf::Color::Blue);
		top.setOutlineThickness(3);

		left.setFillColor(sf::Color(100, 100, 100));
		left.setOutlineColor(sf::Color::Blue);
		left.setOutlineThickness(3);

		right.setFillColor(sf::Color(100, 100, 100));
		right.setOutlineColor(sf::Color::Blue);
		right.setOutlineThickness(3);

		bottom.setFillColor(sf::Color(100, 100, 100));
		bottom.setOutlineColor(sf::Color::Blue);
		bottom.setOutlineThickness(3);

		obstacles.push_back(top);
		obstacles.push_back(bottom);
		obstacles.push_back(left);
		obstacles.push_back(right);
		obstacles.push_back(obstacle);
	}


}

void Arena::setTiles()
{
	//faire la recherche des dalles + trouver une bonne tailles
	sf::RectangleShape tile;
	tile.setSize(sf::Vector2f(30, 30));

	while (tile.getPosition().y < height_) {
		while (tile.getPosition().y < width_) {

		}

	}
}
