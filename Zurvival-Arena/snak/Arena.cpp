#include "Arena.h"
#include "ZurvivalException.h"
#include "Game.h"

Arena::Arena(unsigned width, unsigned height) : width_(width), height_(height) {
	if (width % 30 != 0 || height % 30 != 0) {
		throw ZurvivalException("No respect of size");
	}
	else {
		std::vector<std::vector<bool>> tiles(width/30, std::vector<bool>(height/30 , false));
		tiles_ = tiles;

		sf::RectangleShape top, left, right, bottom, forest , bush, barn,barrier,puit,maisonette;

		forest.setPosition(0,0);
		forest.setSize(sf::Vector2f(150, 400));
		forest.setFillColor(sf::Color::Transparent);

		bush.setPosition(150, 0);
		bush.setSize(sf::Vector2f(60, 160));
		bush.setFillColor(sf::Color::Transparent);

		barn.setPosition(490, 25);
		barn.setSize(sf::Vector2f(100, 140));
		barn.setFillColor(sf::Color::Transparent);
		
		barrier.setPosition(0, 610);
		barrier.setSize(sf::Vector2f(650, 60));
		barrier.setFillColor(sf::Color::Transparent);

		puit.setPosition(455, 300);
		puit.setSize(sf::Vector2f(30, 30));
		puit.setFillColor(sf::Color::Transparent);

		maisonette.setPosition(210, 300);
		maisonette.setSize(sf::Vector2f(80, 120));
		maisonette.setFillColor(sf::Color::Transparent);

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
		obstacles.push_back(forest);
		obstacles.push_back(bush);
		obstacles.push_back(barn);
		obstacles.push_back(barrier);
		obstacles.push_back(puit);
		obstacles.push_back(maisonette);
		setTiles();
	}


}

void Arena::setTiles()
{
	sf::RectangleShape searchTile;
	unsigned line = 0, column = 0;
	searchTile.setSize(sf::Vector2f(30, 30));
	searchTile.setPosition(0,0);

	while (searchTile.getPosition().y < height_) {
		while (searchTile.getPosition().x < width_) {
			for (sf::RectangleShape rs : obstacles){
				if (Game::intersects(rs,searchTile)){
					tiles_[column][line] = true;
				}
				
			}
			column++;
			searchTile.setPosition(searchTile.getPosition().x + 30, searchTile.getPosition().y);
		}
		column = 0;
		line++;
		searchTile.setPosition(0, searchTile.getPosition().y + 30);
	}
	
}

bool Arena::isFree(float x, float y) {
	Position p = Position(x / 30, y / 30);
	return tiles_[p.getX()][p.getY()] == false;
}

//void Arena::printTiles()
//{
//	for (int i = 0; i < height_ / 30; i++) {
//		for (int j = 0; j < width_ / 30; j++) {
//			std::cout << tiles_[j][i];
//		}
//		std::cout << std::endl;
//	}
//}
