#include "Game.h"
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>
#include <map>
using namespace sf;

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

const RectangleShape & Game::getHitBoxChar(int i)const
{
	return players_.at(i).getHitbox();
}

void Game::addEnemy(float posX, float posY, int pv) {
	enemies_.push_back(Enemy(Position(posX, posY), pv));
}

std::vector<Enemy> & Game::getEnemies() {
	return enemies_;
}

void Game::playerMoving(bool moving) {
	playerMove = moving;
}

void Game::functionMovingEnemies() {

	using namespace std::chrono_literals;
	vector < pair<int, int> >v;
	enemies_.at(0).setAnimY(Down);
	enemies_.at(0).uptadeSpritePosition();
	enemies_.at(0).setState(Moving);

	vector< vector<pair<int, int>> > pathToEn;

	while (!gameFinish) {
		//for (int i = 0; i < enemies_.size(); i++) {

		int i = 0;
		Enemy& e = enemies_.at(i);
		if (!pathToEnemy.empty()) {
			v = pathToEnemy.at(i);
		}

		if (enemies_.at(i).getPlayerMoving() == true) {

			v.clear();
			Vector2f c = players_.at(i).getHitbox().getPosition();
			brain(i);
			v = pathToEnemy.at(i);
			/*cout << "first : " << v.at(0).first << "second : " << v.at(0).second << endl;
			cout << "yassine " << players_.at(0).getHitbox().getPosition().x / 30 << " " << players_.at(0).getHitbox().getPosition().y / 30 << endl;*/

			enemies_.at(i).setPlayerMoving(false);
			enemies_.at(i).resetIndicePath();
		}


		if (enemies_.at(i).getIndicePath() < v.size()) {
			players_.at(0).getSprite()->setRotation(0);
			if (textChange) {
				enemies_.at(i).setHitTextureDepart();
				textChange = false;
			}
			moveToPos(i, v);
			enemies_.at(i).incrementIndicePath();
		}
		else {
			if (players_.at(0).getPv() < 2) {


			}
			else {
				players_.at(0).removePv();
				if (!textChange) {
					enemies_.at(0).setHitTexture();
					textChange = true;
				}

			}
			//}
		}
		/*cout << enemies_.at(i).getHitbox().getPosition().x << "         " << enemies_.at(i).getHitbox().getPosition().y << endl;
		cout << players_.at(i).getHitbox().getPosition().x <<"       " <<  players_.at(i).getHitbox().getPosition().y << endl;*/
	}
	threadEnemies->detach();
}
void Game::brain(unsigned i)
{
	openList.clear();
	closedList.clear();
	Enemy & e = enemies_.at(i);
	for (unsigned i = 0; i < enemies_.size(); i++) { //build enemies path to player
		//A revérifier par Salmane 
		Position pos = Position(e.getHitbox().getPosition().x, e.getHitbox().getPosition().y);
		Node arrivee;

		arrivee.position.x = players_[0].getHitbox().getPosition().x / 30;
		arrivee.position.y = players_[0].getHitbox().getPosition().y / 30;

		//	cout << "JBrain -->  X : " << arrivee.position.x << " Y :" << arrivee.position.y<< endl;
			/*	arrivee.gValue = 1;*/
		Node depart;
		depart.parent.x = pos.getX() / 30;
		depart.parent.y = pos.getY() / 30;
		depart.position = Vector2f(pos.getX() / 30, pos.getY() / 30);

		depart.gValue = 1;

		pair<int, int> courant;
		courant.first = depart.position.x;
		courant.second = depart.position.y;
		//	cout << " pos ennemi" << endl;
		if (arrivee.position.x < depart.position.x) {
			inversion = true;

		}
		else {
			inversion = false;
		}

		openList[courant] = depart;
		addToClosedList(courant);
		addAdjectentCell(courant);
		//	cout << "JJJPX2  " << arrivee.position.x << " JJJPY2  " << arrivee.position.y << endl;
		while (!((courant.first <= arrivee.position.x && courant.first + 1 > arrivee.position.x) && (courant.second <= arrivee.position.y && courant.second + 1 > arrivee.position.y)) && (!openList.empty())) {
			//yassine !! dans le cas ou on déplace le joueur pendant que l ennemi bouge l'open list est vide 
			courant = bestNode(openList);	// si l open list est vide brain ne donne plus de path à l'ennemi et du coup n'adapte pas sa trajectoire pour suivre le joueur
			addToClosedList(courant);
			addAdjectentCell(courant);
		}
		int x = arrivee.position.x;
		int y = arrivee.position.y;
		if ((courant.first <= arrivee.position.x && courant.first + 1 > arrivee.position.x) &&
			(courant.second <= arrivee.position.y && courant.second + 1 > arrivee.position.y)) {
			pathToEnemy.at(i).clear();
			pathToEnemy.at(i) = recoverPath(depart, arrivee);
			//add the best possibloe movement
			cout << "OK" << endl;

		}
		else {
			cout << "PLEURE" << endl;
			//Pas de solution
		}


	}
	//Que faire après la constitution des movements des enemis vers les joueurs?
}

void Game::startMovingEnemies() {
	threadEnemies = std::unique_ptr < std::thread >(new std::thread(&Game::functionMovingEnemies, this));

}

bool Game::nodeExistInList(std::pair<int, int> n, std::map<std::pair<int, int>, Node>& l)
{
	std::map<std::pair<int, int>, Node>::iterator i = l.find(n);
	if (i == l.end())
		return false;
	else
		return true;
}

void Game::manageEnemi(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time) {

	for (unsigned i = 0; i < enemies_.size(); i++) {
		enemies_.at(i).manageSprite(fpsCount, fpsSpeed, switchFps, time);
		enemies_.at(i).setState(Moving);

	}

}

unsigned Game::spaceCase(Vector2f pos) {
	unsigned hValue;
	hValue = std::abs(players_.at(0).getHitbox().getPosition().x - pos.x);
	hValue += std::abs(players_.at(0).getHitbox().getPosition().y - pos.y);
	return hValue;
}

void Game::addAdjectentCell(pair<int, int>& n)
{
	Position posPlayer = Position(players_[0].getHitbox().getPosition().x, players_[0].getHitbox().getPosition().y);

	Node tmp;
	for (int i = n.first - 1; i <= n.first + 1; i++) {
		if ((i < 0) || (i >= (arena_.getHeight() / 30))) {
			/* en dehors de l'arène, on oublie */
			continue;
		}
		for (int j = n.second - 1; j <= n.second + 1; j++) {
			if ((j < 0) || (j >= (arena_.getWidth() / 30))) {
				/* en dehors de l'arène, on oublie */
				continue;
			}
			if ((i == n.first) && (j == n.second)) {
				/* case actuelle n, on oublie */
				continue;
			}
			if (arena_.getTiles()[i][j]) {
				/* obstace, terrain non franchissable, on oublie */
				continue;
			}


			pair<int, int> it(i, j);
			if (!nodeExistInList(it, closedList)) {
				/* le noeud n'est pas déjà présent dans la liste fermée */
				/* calcul du cout G du noeud en cours d'étude : cout du parent + distance jusqu'au parent */
				tmp.gValue = closedList[n].gValue + distance(i, j, n.first, n.second);
				/* calcul du cout H du noeud à la destination */

				tmp.hValue = distance(i, j, posPlayer.getX() / 30, posPlayer.getY() / 30);
				tmp.fValue = tmp.gValue + tmp.hValue;
				tmp.position = Vector2f(i, j);
				tmp.parent = Vector2f(n.first, n.second);

				if (nodeExistInList(it, openList)) {
					/* le noeud est déjà présent dans la liste ouverte, il faut comparer les couts */
					if (tmp.fValue < openList[it].fValue) {
						/* si le nouveau chemin est meilleur, on met à jour */
						openList[it] = tmp;
					}
					/* le noeud courant a un moins bon chemin, on ne change rien */
				}
				else {
					/* le noeud n'est pas présent dans la liste ouverte, on l'y ajoute */
					openList[pair<int, int>(i, j)] = tmp;
				}
			}
		}
	}
}
float Game::distance(int x1, int y1, int x2, int y2)
{
	//return std::abs(x1 - x2) + std::abs(y1-y2);
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}
pair<int, int> Game::bestNode(map <pair<int, int>, Node> l) {
	float m_coutf = l.begin()->second.fValue;
	pair<int, int> m_noeud = l.begin()->first;
	if (inversion) {
		for (map <pair<int, int>, Node>::reverse_iterator i = l.rbegin(); i != l.rend(); i++)
			if (i->second.fValue < m_coutf) {
				m_coutf = i->second.fValue;
				m_noeud = i->first;
			}
	}
	else {
		for (map <pair<int, int>, Node>::iterator i = l.begin(); i != l.end(); i++)
			if (i->second.fValue < m_coutf) {
				m_coutf = i->second.fValue;
				m_noeud = i->first;
			}
	}


	return m_noeud;
}

void Game::addToClosedList(pair<int, int>& p) {

	Node& n = openList[p];
	closedList[p] = n;

	/* il faut le supprimer de la liste ouverte, ce n'est plus une solution explorable */
	if (openList.erase(p) == 0)
		cerr << "Erreur, le noeud n'apparait pas dans la liste ouverte, impossible à supprimer" << endl;
	return;
}

vector<pair<int, int>> Game::recoverPath(Node start, Node objectif)
{
	vector <pair<int, int>>chemin;
	/*Position posPlayer = players_[0].getPosition();*/
	Node tmp;
	/* l'arrivée est le dernier élément de la liste fermée */
	map <pair<int, int>, Node>::iterator it;
	if (inversion) {
		map <pair<int, int>, Node>::iterator it = closedList.begin();
		//Node& tmp = closedList[pair<int, int>(objectif.position.x, objectif.position.y)];
		tmp = it->second;
	}
	else {
		map <pair<int, int>, Node>::reverse_iterator it = closedList.rbegin();
		//Node& tmp = closedList[pair<int, int>(objectif.position.x, objectif.position.y)];
		tmp = it->second;
	}

	pair<int, int>n;
	pair<int, int> prec;
	n.first = tmp.position.x;
	n.second = tmp.position.y;
	// parent est 0 ?? mais doit contenir la position joueur ??
	prec.first = tmp.parent.x;
	prec.second = tmp.parent.y;
	chemin.insert(chemin.begin(), n);


	while (prec != pair<int, int>(start.parent.x, start.parent.y)) {

		n.first = prec.first;
		n.second = prec.second;
		chemin.insert(chemin.begin(), n);
		tmp = closedList[pair<int, int>(tmp.parent.x, tmp.parent.y)];
		prec.first = tmp.position.x;
		prec.second = tmp.position.y;
	}
	return chemin;
}


//sf::Vector2f Game::getNextPos(unsigned idEnemy, bool eraseFirst) {
//
//	sf::Vector2f vectorNextPos((float)pathToEnemy.at(idEnemy).at(0).first * 30, (float)pathToEnemy.at(idEnemy).at(0).second * 30);
//	std::vector<std::pair<int, int>> path = pathToEnemy.at(idEnemy);
//	std::vector<std::pair<int, int>>::iterator position = std::find(path.begin(), path.end(), path.front());
//	if (position != path.end()) {
//		path.erase(position);   // supprime à chaque fois la position dans la liste qui est atteinte par l'ennemi qui poursuit le joueur
//	}
//	if (eraseFirst) {
//		pathToEnemy.at(idEnemy) = path;
//	}
//	return vectorNextPos;
//}


int Game::findDirection(unsigned idEnemy, vector < pair<int, int> >v) { // en fonction de sa position et de la prochaine l'enemi saura dans quelle direction avancer logiquement
	Enemy& e = enemies_.at(idEnemy);
	float x = enemies_.at(idEnemy).getPosition().getX();
	float nextX = v.at(e.getIndicePath()).first * 30;
	float y = enemies_.at(idEnemy).getPosition().getY();
	float nextY = v.at(e.getIndicePath()).second * 30;
	if (x == nextX && y > nextY) {
		return 0; //haut
	}
	else if (x == nextX && y < nextY) {
		return 1; //bas
	}
	else if (x < nextX && y == nextY) {
		return 2; //droite
	}
	else if (x > nextX && y == nextY) {
		return 3; //gauche
	}
	else if (x < nextX && y < nextY) {
		return 4; //basDroit
	}
	else if (x > nextX && y > nextY) {
		return 5; //hautGauche
	}
	else if (x > nextX && y < nextY) {
		return 6; // basGauche
	}
	else if (x < nextX && y > nextY) {
		return 7; // hautDroit
	}

}

void Game::moveToPos(unsigned idEnemy, vector < pair<int, int> >v) {
	Enemy& e = enemies_.at(idEnemy);
	int i = 0;
	while (i < 50000 && !gameFinish) {
		switch (findDirection(idEnemy, v)) {
		case 0:
			enemies_.at(idEnemy).move(0, -0.0006);   //mouvement graphique
			enemies_.at(0).setAnimY(Up);
			break;
		case 1:
			enemies_.at(idEnemy).move(0, 0.0006);
			enemies_.at(0).setAnimY(Down);
			break;
		case 2:
			enemies_.at(idEnemy).move(0.0006, 0);
			enemies_.at(0).setAnimY(Right);
			break;
		case 3:
			enemies_.at(idEnemy).move(-0.0006, 0);
			enemies_.at(0).setAnimY(Left);
			break;
		case 4:
			enemies_.at(idEnemy).move(0.0006, 0.0006);
			enemies_.at(0).setAnimY(Down);
			break;
		case 5:
			enemies_.at(idEnemy).move(-0.0006, -0.0006);
			enemies_.at(0).setAnimY(Up);
			break;
		case 6:
			enemies_.at(idEnemy).move(-0.0006, 0.0006);
			enemies_.at(0).setAnimY(Down);
			break;
		case 7:
			enemies_.at(idEnemy).move(0.0006, -0.0006);
			enemies_.at(0).setAnimY(Up);
			break;

		}
		enemies_.at(idEnemy).uptadeSpritePosition();
		i++;
	}
	//}
	switch (findDirection(idEnemy, v)) {
	case 0:
		//de la position de l ennemi et non sa hitbox aparemment)
		enemies_.at(idEnemy).setPositionHitbox(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		enemies_.at(idEnemy).setPosition(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		break;
	case 1:
		enemies_.at(idEnemy).setPositionHitbox(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		enemies_.at(idEnemy).setPosition(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		break;
	case 2:
		enemies_.at(idEnemy).setPositionHitbox(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		enemies_.at(idEnemy).setPosition(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		break;
	case 3:
		enemies_.at(idEnemy).setPositionHitbox(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		enemies_.at(idEnemy).setPosition(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		break;
	case 4:
		enemies_.at(idEnemy).setPositionHitbox(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		enemies_.at(idEnemy).setPosition(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		break;
	case 5:
		enemies_.at(idEnemy).setPositionHitbox(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		enemies_.at(idEnemy).setPosition(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		break;
	case 6:
		enemies_.at(idEnemy).setPositionHitbox(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		enemies_.at(idEnemy).setPosition(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		break;
	case 7:
		enemies_.at(idEnemy).setPositionHitbox(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		enemies_.at(idEnemy).setPosition(v.at(e.getIndicePath()).first * 30, v.at(e.getIndicePath()).second * 30);
		break;

	}
	enemies_.at(idEnemy).uptadeSpritePosition();
}

void Game::shoot(int idPlayer) {
	sf::Vector2f playerpos = players_.at(idPlayer).getHitbox().getPosition();
	switch (players_.at(idPlayer).getAnim().y) {
	case Up:
		for (int i = 0; i < enemies_.size(); i++) {
			if ((unsigned)enemies_.at(i).getHitbox().getPosition().x / 30 == (unsigned)playerpos.x / 30 && (unsigned)enemies_.at(i).getHitbox().getPosition().y / 30 < (unsigned)playerpos.y / 30) {
				//cout << "touché d'en bas" << endl;
				enemies_.at(i).removePv();
				cout << enemies_.at(i).getPv() << endl;
				enemies_.at(i).setHitTextureHit();
			}
			
		}
		break;
	case Down:
		for (int i = 0; i < enemies_.size(); i++) {
			unsigned enX = (unsigned)enemies_.at(i).getHitbox().getPosition().x / 30;
			unsigned enY = (unsigned)enemies_.at(i).getHitbox().getPosition().y / 30;
			unsigned playX = (unsigned)playerpos.x / 30;
			unsigned playY = (unsigned)playerpos.y / 30;

			if ((unsigned)enemies_.at(i).getHitbox().getPosition().x / 30 == (unsigned)playerpos.x / 30 && (unsigned)enemies_.at(i).getHitbox().getPosition().y / 30 > (unsigned)playerpos.y / 30) {
				//cout << "touché d'en haut" << endl;
				enemies_.at(i).removePv();
				cout << enemies_.at(i).getPv() << endl;
				enemies_.at(i).setHitTextureHit();
			}
		
		}
		break;
	case Right:
		for (int i = 0; i < enemies_.size(); i++) {
			if ((unsigned)enemies_.at(i).getHitbox().getPosition().x / 30 > (unsigned)playerpos.x / 30 && (unsigned)enemies_.at(i).getHitbox().getPosition().y / 30 == (unsigned)playerpos.y / 30) {
				//cout << "touché depuis la gauche" << endl;
				enemies_.at(i).removePv();
				cout << enemies_.at(i).getPv() << endl;
				enemies_.at(i).setHitTextureHit();
			}
		
		}
		break;
	case Left:
		for (int i = 0; i < enemies_.size(); i++) {
			if ((unsigned)enemies_.at(i).getHitbox().getPosition().x / 30 < (unsigned)playerpos.x / 30 && (unsigned)enemies_.at(i).getHitbox().getPosition().y / 30 == (unsigned)playerpos.y / 30) {
				//cout << "touché depuis la droite" << endl;
				enemies_.at(i).removePv();
				cout << enemies_.at(i).getPv() << endl;
				enemies_.at(i).setHitTextureHit();
			}
		
		}
		break;

	}


}
