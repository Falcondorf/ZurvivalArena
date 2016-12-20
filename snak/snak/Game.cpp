#include "Game.h"
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
using namespace sf;

bool Game::hasCollision(int idPlayer,float movex, float movey) {
	if (idPlayer < 0 || idPlayer>1) {
		//throw invalid_argument();
	}
	bool ok = false;
	for (int i = 0; i< arena_.getObstacles().size(); i++) {
		if (intersects( arena_.getObstacles()[i], players_.at(idPlayer).getHitbox())) {
			std::cout << "collision" << std::endl;
			
			players_.at(idPlayer).setPosition(players_.at(idPlayer).getHitbox().getPosition().x - movex * 10, players_.at(idPlayer).getHitbox().getPosition().y - movey * 10);
			ok = true;
		}
	}
	return ok;
}

bool Game::intersects(const RectangleShape & rect1, const RectangleShape & rect2)
{
	FloatRect r1 = rect1.getGlobalBounds();
	FloatRect r2 = rect2.getGlobalBounds();
	return r1.intersects(r2);
}

void Game::move(int idplayer, float xMove, float yMove) {

	players_.at(idplayer).move(xMove, yMove);
}