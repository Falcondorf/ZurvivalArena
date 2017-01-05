
#include "Game.h"

#include <vector>
#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>
#include <map>
using namespace sf;
using namespace std;
Game::Game(unsigned width, unsigned height, int fiboNbEnemies) : nbEnemies(fiboNbEnemies){
	arena_ = Arena(width, height);
	for (unsigned i = 0;i<7; i++) {
		Level lvl;
		lvl.nbPv = 100;// *pow(10, i);
		levels.push_back(lvl);
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
			players_.at(idPlayer).removePv(1);
			sf::RectangleShape rce = players_.at(idPlayer).getlifebar();
			if (rce.getSize().x > 0) {
				rce.setSize(sf::Vector2f(rce.getSize().x - 0.005, rce.getSize().y));
			}
			players_.at(idPlayer).setlifebar(rce);
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

const RectangleShape & Game::getHitBoxChar(int i)const
{
	return players_.at(i).getHitbox();
}

void Game::addEnemy(float posX, float posY, int pv) {
	
	enemies_.push_back(Enemy(Position(posX, posY),nbEnemies, pv, this));
	nbEnemies--;
	//setNbEnemies(nbEnemies + 1);
}



const std::vector<Enemy> & Game::getEnemies() const{
	return enemies_;
}

void Game::playerMoving(bool moving) {
	playerMove = moving;
}


void Game::startMovingEnemies() {
	/*threadEnemies = std::unique_ptr < std::thread >(new std::thread(&Game::functionMovingEnemies, this));*/
	for (unsigned i = 0;i<enemies_.size();i++) {
		enemies_.at(i).startMovingEnemies();
	}

}


void Game::manageEnemi(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time) {

	for (unsigned i = 0; i < enemies_.size(); i++) {
		enemies_.at(i).manageSprite(fpsCount, fpsSpeed, switchFps, time);
		enemies_.at(i).setState(Moving);

	}

}

void Game::moveBall(std::vector<pair<float, float>> vec) {

	RectangleShape rs(sf::Vector2f(vec.at(0).first, vec.at(0).second));
	rs.setFillColor(sf::Color::Red);
	rs.setSize(sf::Vector2f(10, 10));

	for (int i = 0; i < vec.size(); i++) {
		rs.move(vec.at(i).first, vec.at(i).second);


	}

}

void Game::shoot(int idPlayer) {


	std::vector<pair<float, float>> vec;
	/*vec = trajectoireBalle(idPlayer);
	moveBall(vec);*/
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
					//enemies_.at(i).setHitTextureHit();
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

			if ((unsigned)enemies_.at(i).getHitbox().getPosition().x / 30 == (unsigned)playerpos.x / 30 && (unsigned)enemies_.at(i).getHitbox().getPosition().y / 30 > (unsigned)playerpos.y / 30) {
				//cout << "touché d'en haut" << endl;
				for (unsigned k = (playerpos.y / 30); (k < enemies_.at(i).getHitbox().getPosition().y / 30 && !isObstacle); k++) {
					if (arena_.getTiles()[playerpos.x / 30][k]) {
						isObstacle = true;
					}
				}
				if (!isObstacle) {
					enemies_.at(i).removePv(10);
					cout << enemies_.at(i).getPv() << endl;
					//enemies_.at(i).setHitTextureHit();
				}
			}

		}
		break;
	case Right:
		for (int i = 0; i < enemies_.size(); i++) {
			if ((unsigned)enemies_.at(i).getHitbox().getPosition().x / 30 > (unsigned)playerpos.x / 30 && (unsigned)enemies_.at(i).getHitbox().getPosition().y / 30 == (unsigned)playerpos.y / 30) {
				//cout << "touché depuis la gauche" << endl;
				for (unsigned k = (playerpos.x / 30); (k < enemies_.at(i).getHitbox().getPosition().x / 30 && !isObstacle); k++) {
					if (arena_.getTiles()[k][playerpos.x / 30]) {
						isObstacle = true;
					}
				}
				if (!isObstacle) {
					enemies_.at(i).removePv(10);
					cout << enemies_.at(i).getPv() << endl;
				//	enemies_.at(i).setHitTextureHit();
				}
			}

		}
		break;
	case Left:
		for (int i = 0; i < enemies_.size(); i++) {
			if ((unsigned)enemies_.at(i).getHitbox().getPosition().x / 30 < (unsigned)playerpos.x / 30 && (unsigned)enemies_.at(i).getHitbox().getPosition().y / 30 == (unsigned)playerpos.y / 30) {
				//cout << "touché depuis la droite" << endl;
				for (unsigned k = (playerpos.x / 30); (k > enemies_.at(i).getHitbox().getPosition().x / 30 && !isObstacle); k--) {
					if (arena_.getTiles()[k][playerpos.x / 30]) {
						isObstacle = true;
					}
				}
				if (!isObstacle) {
					enemies_.at(i).removePv(10);
					cout << enemies_.at(i).getPv() << endl;
				//	enemies_.at(i).setHitTextureHit();
				}
			}

		}
		break;

	}


}

std::vector<pair<float, float>> Game::trajectoireBalle(int idPlayer) {
	sf::Vector2f playerpos = players_.at(idPlayer).getHitbox().getPosition();

	int min = 0;
	int max = 660;
	std::vector<pair<float, float>> vectorpos;
	vectorpos.clear();
	switch (players_.at(idPlayer).getAnim().y) {

	case Down:

		for (float i = playerpos.y + 30; i <= max; i += 30) {
			vectorpos.push_back(std::make_pair(playerpos.x / 30, i / 30));

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
			//cout << "pv " <<enemies_.at(i).getPv() << endl;
		}
	}
}

void Game::removePvOfPlayer(unsigned i) {
	players_.at(0).removePv(i);
}
void Game::setLifeBarOfPlayer(unsigned i, sf::RectangleShape rce) {
	players_.at(i).setlifebar(rce);
}

bool Game::isFinishGame() {
	return gameFinish;
}

void Game::nextLevel() {
	idLevel++;
	for (unsigned i=0;i < enemies_.size();i++) {
		enemies_.at(i).nextLevel();
		enemies_.at(i).setPv(levels.at(idLevel).nbPv);
		enemies_.at(i).spriteLevel();
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
// NE PAS TOUCHER CI_DESSOUS

//
//void Game::addAdjectentCell(pair<int, int>& n)
//{
//	Position posPlayer = Position(players_[0].getHitbox().getPosition().x, players_[0].getHitbox().getPosition().y);
//
//	Node tmp;
//	for (int i = n.first - 1; i <= n.first + 1; i++) {
//		if ((i < 0) || (i >= (arena_.getHeight() / 30))) {
//			/* en dehors de l'arène, on oublie */
//			continue;
//		}
//		for (int j = n.second - 1; j <= n.second + 1; j++) {
//			if ((j < 0) || (j >= (arena_.getWidth() / 30))) {
//				/* en dehors de l'arène, on oublie */
//				continue;
//			}
//			if ((i == n.first) && (j == n.second)) {
//				/* case actuelle n, on oublie */
//				continue;
//			}
//			if (arena_.getTiles()[i][j]) {
//				/* obstace, terrain non franchissable, on oublie */
//				continue;
//			}
//
//
//			pair<int, int> it(i, j);
//			if (!nodeExistInList(it, closedList)) {
//				/* le noeud n'est pas déjà présent dans la liste fermée */
//				/* calcul du cout G du noeud en cours d'étude : cout du parent + distance jusqu'au parent */
//				tmp.gValue = closedList[n].gValue + distance(i, j, n.first, n.second);
//				/* calcul du cout H du noeud à la destination */
//
//				tmp.hValue = distance(i, j, posPlayer.getX() / 30, posPlayer.getY() / 30);
//				tmp.fValue = tmp.gValue + tmp.hValue;
//				tmp.position = Vector2f(i, j);
//				tmp.parent = Vector2f(n.first, n.second);
//
//				if (nodeExistInList(it, openList)) {
//					/* le noeud est déjà présent dans la liste ouverte, il faut comparer les couts */
//					if (tmp.fValue < openList[it].fValue) {
//						/* si le nouveau chemin est meilleur, on met à jour */
//						openList[it] = tmp;
//					}
//					/* le noeud courant a un moins bon chemin, on ne change rien */
//				}
//				else {
//					/* le noeud n'est pas présent dans la liste ouverte, on l'y ajoute */
//					openList[pair<int, int>(i, j)] = tmp;
//				}
//			}
//		}
//	}
//}
//float Game::distance(int x1, int y1, int x2, int y2)
//{
//	return std::abs(x1 - x2) + std::abs(y1-y2);
//	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
//}
//pair<int, int> Game::bestNode(map <pair<int, int>, Node> l) {
//	float m_coutf = l.begin()->second.fValue;
//	pair<int, int> m_noeud = l.begin()->first;
//	if (inversion) {
//		for (map <pair<int, int>, Node>::reverse_iterator i = l.rbegin(); i != l.rend(); i++)
//			if (i->second.fValue < m_coutf) {
//				m_coutf = i->second.fValue;
//				m_noeud = i->first;
//			}
//	}
//	else {
//		for (map <pair<int, int>, Node>::iterator i = l.begin(); i != l.end(); i++)
//			if (i->second.fValue < m_coutf) {
//				m_coutf = i->second.fValue;
//				m_noeud = i->first;
//			}
//	}
//
//
//	return m_noeud;
//}
//
//void Game::addToClosedList(pair<int, int>& p) {
//
//	Node& n = openList[p];
//	closedList[p] = n;
//
//	/* il faut le supprimer de la liste ouverte, ce n'est plus une solution explorable */
//	if (openList.erase(p) == 0)
//		cerr << "Erreur, le noeud n'apparait pas dans la liste ouverte, impossible à supprimer" << endl;
//	return;
//}
//
//vector<pair<int, int>> Game::recoverPath(Node start, Node objectif)
//{
//	vector <pair<int, int>>chemin;
//	/*Position posPlayer = players_[0].getPosition();*/
//	Node tmp;
//	/* l'arrivée est le dernier élément de la liste fermée */
//	map <pair<int, int>, Node>::iterator it;
//	if (inversion) {
//		map <pair<int, int>, Node>::iterator it = closedList.begin();
//		Node& tmp = closedList[pair<int, int>(objectif.position.x, objectif.position.y)];
//		tmp = it->second;
//	}
//	else {
//		map <pair<int, int>, Node>::reverse_iterator it = closedList.rbegin();
//		Node& tmp = closedList[pair<int, int>(objectif.position.x, objectif.position.y)];
//		tmp = it->second;
//	}
//
//	pair<int, int>n;
//	pair<int, int> prec;
//	n.first = tmp.position.x;
//	n.second = tmp.position.y;
//	 parent est 0 ?? mais doit contenir la position joueur ??
//	prec.first = tmp.parent.x;
//	prec.second = tmp.parent.y;
//	chemin.insert(chemin.begin(), n);
//
//
//	while (prec != pair<int, int>(start.parent.x, start.parent.y)) {
//
//		n.first = prec.first;
//		n.second = prec.second;
//		chemin.insert(chemin.begin(), n);
//		tmp = closedList[pair<int, int>(tmp.parent.x, tmp.parent.y)];
//		prec.first = tmp.position.x;
//		prec.second = tmp.position.y;
//	}
//	return chemin;
//}

//bool Game::nodeExistInList(pair<int, int> n, std::map<pair<int, int>, Node>& l)
//{
//	std::map<pair<int, int>, Node>::iterator i = l.find(n);
//	if (i == l.end())
//		return false;
//	else
//		return true;
//}

//void Game::functionMovingEnemies() {
//
//	using namespace std::chrono_literals;
//	vector < pair<int, int> >v;
//	enemies_.at(0).setAnimY(Down);
//	enemies_.at(0).uptadeSpritePosition();
//	enemies_.at(0).setState(Moving);
//
//	vector< vector<pair<int, int>> > pathToEn;
//
//	while (!gameFinish) {
//		/*for (int i = 0; i < enemies_.size(); i++) {*/
//		int i = 0;
//		Enemy& e = enemies_.at(i);
//		if (!pathToEnemy.empty()) {
//			v = pathToEnemy.at(i);
//		}
//
//		if (enemies_.at(i).getPlayerMoving() == true) {
//
//			v.clear();
//			Vector2f c = players_.at(i).getHitbox().getPosition();
//			brain(i);
//			v = pathToEnemy.at(i);
//			/*cout << "first : " << v.at(0).first << "second : " << v.at(0).second << endl;
//			cout << "yassine " << players_.at(0).getHitbox().getPosition().x / 30 << " " << players_.at(0).getHitbox().getPosition().y / 30 << endl;*/
//			enemies_.at(i).setPlayerMoving(false);
//			enemies_.at(i).resetIndicePath();
//		}
//
//		v = pathToEnemy.at(i);
//		if (enemies_.at(i).getIndicePath() < v.size()) {
//			players_.at(0).getSprite()->setRotation(0);
//			if (textChange) {
//				enemies_.at(i).setHitTextureDepart();
//				textChange = false;
//			}
//
//			moveToPos(i, v);
//			enemies_.at(i).incrementIndicePath();
//		}
//		else {
//			if (players_.at(0).getPv() < 2) {
//
//
//			}
//			else {
//				players_.at(0).removePv(1);
//				if (!textChange) {
//					enemies_.at(0).setHitTexture();
//					textChange = true;
//				}
//
//			}
//			//}
//		}
//		/*cout << enemies_.at(i).getHitbox().getPosition().x << "         " << enemies_.at(i).getHitbox().getPosition().y << endl;
//		cout << players_.at(i).getHitbox().getPosition().x <<"       " <<  players_.at(i).getHitbox().getPosition().y << endl;*/
//		/*}*/
//		for (int k = 0; k < enemies_.size(); k++) {
//			for (int l = 0; l < players_.size(); l++) {
//				if (intersects(getEnemies().at(k).getHitbox(), players_.at(l).getHitbox())) {
//					players_.at(l).removePv(1);
//					cout << "player pv : " << players_.at(l).getPv() << endl;
//					sf::RectangleShape rce = players_.at(l).getlifebar();
//					if (rce.getSize().x > 0) {
//						rce.setSize(sf::Vector2f(rce.getSize().x - 0.005, rce.getSize().y));
//						players_.at(l).setlifebar(rce);
//					}
//				}
//			}
//
//		}
//	}
//	threadEnemies->detach();
//}

////void Game::brain(unsigned i)
////{
////	/*mutexx.lock();*/
////	openList.clear();
////	closedList.clear();
////	Enemy & e = enemies_.at(i);
////	for (unsigned i = 0; i < enemies_.size(); i++) { //build enemies path to player
////		//A revérifier par Salmane 
////		Position pos = Position(e.getHitbox().getPosition().x, e.getHitbox().getPosition().y);
////		Node arrivee;
////
////		arrivee.position.x = players_[0].getHitbox().getPosition().x / 30;
////		arrivee.position.y = players_[0].getHitbox().getPosition().y / 30;
////
////		//	cout << "JBrain -->  X : " << arrivee.position.x << " Y :" << arrivee.position.y<< endl;
////			/*	arrivee.gValue = 1;*/
////		Node depart;
////		depart.parent.x = pos.getX() / 30;
////		depart.parent.y = pos.getY() / 30;
////		depart.position = Vector2f(pos.getX() / 30, pos.getY() / 30);
////
////		depart.gValue = 1;
////
////		pair<int, int> courant;
////		courant.first = depart.position.x;
////		courant.second = depart.position.y;
////		//	cout << " pos ennemi" << endl;
////		if (arrivee.position.x < depart.position.x) {
////			inversion = true;
////
////		}
////		else {
////			inversion = false;
////		}
////
////		openList[courant] = depart;
////		addToClosedList(courant);
////		addAdjectentCell(courant);
////		//	cout << "JJJPX2  " << arrivee.position.x << " JJJPY2  " << arrivee.position.y << endl;
////		while (!((courant.first <= arrivee.position.x && courant.first + 1 > arrivee.position.x) && (courant.second <= arrivee.position.y && courant.second + 1 > arrivee.position.y)) && (!openList.empty())) {
////			//yassine !! dans le cas ou on déplace le joueur pendant que l ennemi bouge l'open list est vide 
////			courant = bestNode(openList);	// si l open list est vide brain ne donne plus de path à l'ennemi et du coup n'adapte pas sa trajectoire pour suivre le joueur
////			addToClosedList(courant);
////			addAdjectentCell(courant);
////		}
////		int x = arrivee.position.x;
////		int y = arrivee.position.y;
////		if ((courant.first <= arrivee.position.x && courant.first + 1 > arrivee.position.x) &&
////			(courant.second <= arrivee.position.y && courant.second + 1 > arrivee.position.y)) {
////			pathToEnemy.at(i).clear();
////			pathToEnemy.at(i) = recoverPath(depart, arrivee);
////			//add the best possibloe movement
////			/*cout << "OK" << endl;*/
////
////		}
////		else {
////			/*	cout << "PLEURE" << endl;*/
////				//Pas de solution
////		}
////
////
////	}
////	//Que faire après la constitution des movements des enemis vers les joueurs?
////	/*mutexx.unlock();*/
////}