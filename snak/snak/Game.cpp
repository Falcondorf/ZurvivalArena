#include "Game.h"
#include <SFML\Graphics.hpp>

using namespace sf;

bool Game::hasCollision() {
	
}

bool Game::intersects(const RectangleShape & rect1, const RectangleShape & rect2)
{
	FloatRect r1 = rect1.getGlobalBounds();
	FloatRect r2 = rect2.getGlobalBounds();
	return r1.intersects(r2);
}
