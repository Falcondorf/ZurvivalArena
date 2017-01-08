
#include "Game.h"

#include <vector>
#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>
#include <map>
using namespace sf;
using namespace std;
Game::Game(unsigned width, unsigned height) {
	arena_ = Arena(width, height);
	for (unsigned i = 0; i < 7; i++) {
		pvForLevel.push_back(100 * pow(10, i));
	}
}

bool Game::hasCollision(int idPlayer, float movex, float movey) {
	if (idPlayer < 0 || idPlayer>1) {
		//throw invalid_argument();
	}
	RectangleShape futurePosition = players_.at(idPlayer).getHitbox();
	futurePosition.move(movex, movey);
	for (int i = 0; i < getNbObstacles(); i++) {
		if (intersects(getObstacle(i), futurePosition)) {
			return true;
		}
	}
	for (int j = 0; j < getEnemies().size(); j++) {
		if (intersects(getEnemies().at(j).getHitbox(), futurePosition)) {
			if (getEnemies().at(j).getPv() != 0) {
				players_.at(idPlayer).removePv(1);
				sf::RectangleShape rce = players_.at(idPlayer).getlifebar();
				if (rce.getSize().x > 0) {
					rce.setSize(sf::Vector2f(rce.getSize().x - 0.005, rce.getSize().y));
				}
				players_.at(idPlayer).setlifebar(rce);
			}

			//players_.at(idPlayer).getlifebar().setSize(sf::Vector2f(players_.at(idPlayer).getlifebar().getSize().x-1, players_.at(idPlayer).getlifebar().getSize().y));


		}
	}
	return false;
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

unsigned Game::getNbPlayers() const
{
	return players_.size();
}

//const RectangleShape & Game::getHitBoxChar(int i)const
//{
//	return players_.at(i).getHitbox();
//}

void Game::addEnemy(float posX, float posY, int pv) {
	//nbEnemies++;
	enemies_.push_back(Enemy(Position(posX, posY), nbEnemies, pv, this));
}



const std::vector<Enemy> & Game::getEnemies() const {
	return enemies_;
}


void Game::startMovingEnemies() {
	for (unsigned i = 0; i < enemies_.size(); i++) {
		enemies_.at(i).startMovingEnemies();
	}

}


void Game::manageEnemi(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time) {

	for (unsigned i = 0; i < enemies_.size(); i++) {
		enemies_.at(i).manageSprite(fpsCount, fpsSpeed, switchFps, time);
		enemies_.at(i).setState(Moving);

	}

}


void Game::shoot(int idPlayer) {

	std::vector<pair<float, float>> vec;
	sf::Vector2f playerpos = players_.at(idPlayer).getHitbox().getPosition();
	RectangleShape rs(sf::Vector2f(playerpos.x, playerpos.y));
	bool isObstacle = false;
	switch (players_.at(idPlayer).getAnim().y) {
	case Up:

		for (int i = 0; i < enemies_.size(); i++) {
			if ((unsigned)enemies_.at(i).getHitbox().getPosition().x / 30 == (unsigned)playerpos.x / 30 && (unsigned)enemies_.at(i).getHitbox().getPosition().y / 30 < (unsigned)playerpos.y / 30) {
				for (unsigned k = (playerpos.y / 30); (k > enemies_.at(i).getHitbox().getPosition().y / 30 && !isObstacle); k--) {
					if (arena_.getTiles()[playerpos.x / 30][k]) {
						isObstacle = true;
					}
				}
				if (!isObstacle) {
					enemies_.at(i).removePv(10);
					cout << enemies_.at(i).getPv() << endl;
				}
			}

		}
		break;
	case Down:
		for (int i = 0; i < enemies_.size(); i++) {
			unsigned enX = (unsigned)enemies_.at(i).getHitbox().getPosition().x / 30;
			unsigned enY = (unsigned)enemies_.at(i).getHitbox().getPosition().y / 30;
			unsigned playX = (unsigned)playerpos.x / 30;
			unsigned playY = (unsigned)playerpos.y / 30;

			if ((unsigned)enemies_.at(i).getHitbox().getPosition().x / 30 == (unsigned)playerpos.x / 30 && (unsigned)enemies_.at(i).getHitbox().getPosition().y / 30 >(unsigned)playerpos.y / 30) {
				for (unsigned k = (playerpos.y / 30); (k < enemies_.at(i).getHitbox().getPosition().y / 30 && !isObstacle); k++) {
					if (arena_.getTiles()[playerpos.x / 30][k]) {
						isObstacle = true;
					}
				}
				if (!isObstacle) {
					enemies_.at(i).removePv(10);
					cout << enemies_.at(i).getPv() << endl;
				}
			}

		}
		break;
	case Right:
		for (int i = 0; i < enemies_.size(); i++) {
			if ((unsigned)enemies_.at(i).getHitbox().getPosition().x / 30 >(unsigned)playerpos.x / 30 && (unsigned)enemies_.at(i).getHitbox().getPosition().y / 30 == (unsigned)playerpos.y / 30) {
				for (unsigned k = (playerpos.x / 30); (k < enemies_.at(i).getHitbox().getPosition().x / 30 && !isObstacle); k++) {
					if (arena_.getTiles()[k][playerpos.x / 30]) {
						isObstacle = true;
					}
				}
				if (!isObstacle) {
					enemies_.at(i).removePv(10);
					cout << enemies_.at(i).getPv() << endl;
				}
			}

		}
		break;
	case Left:
		for (int i = 0; i < enemies_.size(); i++) {
			if ((unsigned)enemies_.at(i).getHitbox().getPosition().x / 30 < (unsigned)playerpos.x / 30 && (unsigned)enemies_.at(i).getHitbox().getPosition().y / 30 == (unsigned)playerpos.y / 30) {
				for (unsigned k = (playerpos.x / 30); (k > enemies_.at(i).getHitbox().getPosition().x / 30 && !isObstacle); k--) {
					if (arena_.getTiles()[k][playerpos.x / 30]) {
						isObstacle = true;
					}
				}
				if (!isObstacle) {
					enemies_.at(i).removePv(10);
					cout << enemies_.at(i).getPv() << endl;
				}
			}

		}
		break;

	}


}

std::vector<pair<float, float>> Game::trajectoireBalle(int idPlayer) const {
	sf::Vector2f playerpos = players_.at(idPlayer).getHitbox().getPosition();
	int min = 0;
	int max = 660;
	std::vector<pair<float, float>> vectorpos;
	vectorpos.clear();
	switch (players_.at(idPlayer).getAnim().y) { // selon la direction dans laquelle le joueur se tourne
	case Down:
		for (float i = playerpos.y + 30; i <= max; i += 30) {
			vectorpos.push_back(std::make_pair(playerpos.x / 30, i / 30)); // la liste de position de balle est établie
		}
		break;

	case Left:
		for (float i = playerpos.x - 30; i >= min; i -= 30) {
			vectorpos.push_back(std::make_pair(i / 30, playerpos.y / 30));
		}
		break;

	case Up:
		for (float i = playerpos.y - 30; i >= min; i -= 30) {
			vectorpos.push_back(std::make_pair(playerpos.x / 30, i / 30));
		}
		break;
	case Right:
		for (float i = playerpos.x + 30; i <= max; i += 30) {
			vectorpos.push_back(std::make_pair(i / 30, playerpos.y / 30));
		}
		break;
	}
	return vectorpos;
}

void Game::slice(int idPlayer)
{
	RectangleShape hitZone;
	hitZone.setSize(Vector2f(30, 30));

	switch (players_.at(idPlayer).getAnim().y) {
	case Up:
		hitZone.setPosition(players_.at(idPlayer).getHitbox().getPosition().x, players_.at(idPlayer).getHitbox().getPosition().y - 30);
		break;
	case Down:
		hitZone.setPosition(players_.at(idPlayer).getHitbox().getPosition().x, players_.at(idPlayer).getHitbox().getPosition().y + 30);
		break;
	case Left:
		hitZone.setPosition(players_.at(idPlayer).getHitbox().getPosition().x - 30, players_.at(idPlayer).getHitbox().getPosition().y);
		break;
	case Right:
		hitZone.setPosition(players_.at(idPlayer).getHitbox().getPosition().x + 30, players_.at(idPlayer).getHitbox().getPosition().y);
		break;
	}

	for (unsigned i = 0; i < enemies_.size(); i++) {
		if (Game::intersects(hitZone, enemies_.at(i).getHitbox())) {
			enemies_.at(i).removePv(1);
		}
	}
}

void Game::removePvOfPlayer(unsigned i) {
	players_.at(0).removePv(i);
}
void Game::setLifeBarOfPlayer(unsigned i, sf::RectangleShape rce) {
	players_.at(i).setlifebar(rce);
}

bool Game::isFinishGame() const {
	return gameFinish;
}

void Game::nextLevel() {
	if (idLevel < 5) {
		idLevel++;
		for (unsigned i = 0; i < enemies_.size(); i++) {
			enemies_.at(i).nextLevel();
			enemies_.at(i).setPv(pvForLevel.at(idLevel));
			enemies_.at(i).spriteLevel();
			enemies_.at(i).reload();
		}
	}
	else {
		gameFinish = true;
	}

}

bool Game::allEnemiesIsDead() const {
	for (auto & e : enemies_) {
		if (e.getPv() > 0) {
			return false;
		}
	}
	return true;
}

