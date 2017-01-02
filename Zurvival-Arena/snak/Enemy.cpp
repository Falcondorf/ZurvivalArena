#include "Enemy.h"
#include <iostream>

Enemy::Enemy(Position position, int pv, unsigned idEnemy, Game * gam) : Character(position, pv)
{
	game = gam;
	id = idEnemy;
	std::cout << "id ennemy " << id << std::endl;
	positionFirst = position;
	perso_ = new sf::Texture();
		if (!perso_->loadFromFile("pics/jake3.png")) {
			std::cout << "error loading image" << std::endl;
		}
		playerMove = true;
		indicePath = 0;
	spritePerso_ = new sf::Sprite();
	spritePerso_->setTexture(*perso_);
	spritePerso_->setPosition(getHitbox().getPosition());
	spritePerso_->setTextureRect(sf::IntRect(anim.x * 56, anim.y * 85, 56, 85));
	spritePerso_->setScale(sf::Vector2f(0.9, 0.5));
}

void Enemy::uptadeSpritePosition() {
	spritePerso_->setPosition(sf::Vector2f(getHitbox().getPosition().x - 20, getHitbox().getPosition().y - 5));
	
}

bool Enemy::getPlayerMoving() {
	return playerMove;
}
void Enemy::setPlayerMoving(bool b) {
	playerMove = b;
}


int Enemy::getIndicePath()const {
	return indicePath;
}

void Enemy::incrementIndicePath() {
	indicePath++;
}
void Enemy::resetIndicePath() {
	indicePath = 0;
}
void Enemy::setHitTexture() {
	sf::Texture* perso = new sf::Texture();
	if (!perso->loadFromFile("pics/jake33.png")) {
		std::cout << "error loading image" << std::endl;
	}
	spritePerso_->setTexture(*perso);
}

void Enemy::setHitTextureDepart() {
	sf::Texture* perso = new sf::Texture();
	if (!perso->loadFromFile("pics/jake3.png")) {
		std::cout << "error loading image" << std::endl;
	}
	spritePerso_->setTexture(*perso);
}

void Enemy::setHitTextureHit() {
	sf::Texture* perso = new sf::Texture();
	if (!perso->loadFromFile("pics/jake3Hit.png")) {
		std::cout << "error loading image" << std::endl;
	}
	spritePerso_->setTexture(*perso);
}

///////////////////////////////// START //////////////////////////////////////////////


void Enemy::functionMovingEnemies() {

	using namespace std::chrono_literals;
	vector < pair<int, int> >v;
	setAnimY(Down);
	uptadeSpritePosition();
	setState(Moving);

	vector< vector<pair<int, int>> > pathToEn;

	while ( !game->isFinishGame()  && pv_ > 0) {

		/*for (int i = 0; i < enemies_.size(); i++) {*/

		if (!pathToPlayer.empty()) {
			/*v = pathToPlayer.at(i);*/
		}

		if (getPlayerMoving() == true && (start==0 || !game->isBrainLocked() ) ) {
			cout << "Brain" << endl;
			start++;
			pathToPlayer.clear();
			Vector2f c = game->getPlayers().at(0).getHitbox().getPosition();
			game->setBrainLock(true);
			brain();
			game->setBrainLock(false);
			v = pathToPlayer;
			/*cout << "first : " << v.at(0).first << "second : " << v.at(0).second << endl;
			cout << "yassine " << players_.at(0).getHitbox().getPosition().x / 30 << " " << players_.at(0).getHitbox().getPosition().y / 30 << endl;*/
			setPlayerMoving(false);
			resetIndicePath();
			
		}

		if (indicePath < pathToPlayer.size()) {
			game->getPlayers().at(0).getSprite()->setRotation(0);
			if (textChange) {
				setHitTextureDepart();
				textChange = false;
			}

			moveToPos(v); 
			incrementIndicePath();
		}
		else {
			if (game->getPlayers().at(0).getPv() < 2) {


			}
			else {
				game->removePvOfPlayer(1);

				if (!textChange) {
					setHitTexture();
					textChange = true;
				}

			}
			//}
		}
		/*cout << getHitbox().getPosition().x << "         " << getHitbox().getPosition().y << endl;
		cout << players_.at(i).getHitbox().getPosition().x <<"       " <<  players_.at(i).getHitbox().getPosition().y << endl;*/
		/*}*/
			for (int l = 0; l < game->getPlayers().size(); l++) {
				if (game->intersects(getHitbox(), game->getPlayers().at(l).getHitbox())) {
					
					//TODO .....
					game->removePvOfPlayer(1);
					cout << "player pv : " << game->getPlayers().at(l).getPv() << endl;
					sf::RectangleShape rce = game->getPlayers().at(l).getlifebar();
					if (rce.getSize().x > 0) {
						rce.setSize(sf::Vector2f(rce.getSize().x - 0.005, rce.getSize().y));
						game->setLifeBarOfPlayer(l,rce);
					}
				}
			}

	}
	threadEnemies.detach();
}

void Enemy::startMovingEnemies() {
	threadEnemies =  std::thread(&Enemy::functionMovingEnemies, this);
	
}


void Enemy::brain()
{
	openList.clear();
	closedList.clear();


		Position pos = Position(getHitbox().getPosition().x, getHitbox().getPosition().y);
		Node2 arrivee;
		if (id % 2 == 0) {
			arrivee.position.x = game->getPlayers().at(0).getHitbox().getPosition().x / 30;

			arrivee.position.y = game->getPlayers().at(0).getHitbox().getPosition().y / 30;
			cout << "1" << endl;
		}
		else {
			arrivee.position.x = game->getPlayers().at(1).getHitbox().getPosition().x / 30;

			arrivee.position.y = game->getPlayers().at(1).getHitbox().getPosition().y / 30;
			cout << "2" << endl;
		}
		

			/*cout << "JBrain -->  X : " << arrivee.position.x << " Y :" << arrivee.position.y<< endl;*/
		/*	arrivegValue = 1;*/
		Node2 depart;
		
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
		while (!((courant.first <= arrivee.position.x && courant.first + 1 >arrivee.position.x) 
			&& (courant.second <= arrivee.position.y && courant.second + 1 > arrivee.position.y))
			&& (!openList.empty())&& !game->isFinishGame()) {

			//yassine !! dans le cas ou on déplace le joueur pendant que l ennemi bouge l'open list est vide 
			courant = bestNode(openList);	// si l open list est vide brain ne donne plus de path à l'ennemi et du coup n'adapte pas sa trajectoire pour suivre le joueur
			addToClosedList(courant);
			addAdjectentCell(courant);
		}
		int x = arrivee.position.x;
		int y = arrivee.position.y;
		if ((courant.first <= arrivee.position.x && courant.first + 1 > arrivee.position.x) &&
			(courant.second <= arrivee.position.y && courant.second + 1 > arrivee.position.y)) {
			pathToPlayer.clear();
			pathToPlayer = recoverPath(depart, arrivee);
			//add the best possibloe movement
			/*cout << "OK" << endl;*/

		}
		else {
			/*	cout << "PLEURE" << endl;*/
			//Pas de solution
		}


	//Que faire après la constitution des movements des enemis vers les joueurs?
}


void Enemy::addAdjectentCell(pair<int, int>& n)
{
	Position posPlayer;
	if (id % 2 == 0) {
		 posPlayer= Position(game->getPlayers().at(0).getHitbox().getPosition().x, game->getPlayers().at(0).getHitbox().getPosition().y);
	}
	else {
		posPlayer = Position(game->getPlayers().at(1).getHitbox().getPosition().x, game->getPlayers().at(1).getHitbox().getPosition().y);
	}
	Node2 tmp;
	for (int i = n.first - 1; i <= n.first + 1 && !game->isFinishGame(); i++) {
		if ((i < 0) || (i >= (game->getArena().getHeight() / 30))) {
			/* en dehors de l'arène, on oublie */
			continue;
		}
		for (int j = n.second - 1; j <= n.second + 1 && !game->isFinishGame(); j++) {
			if ((j < 0) || (j >= (game->getArena().getWidth() / 30))) {
				/* en dehors de l'arène, on oublie */
				continue;
			}
			if ((i == n.first) && (j == n.second)) {
				/* case actuelle n, on oublie */
				continue;
			}
			if (game->getArena().getTiles()[i][j]) {
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

float Enemy::distance(int x1, int y1, int x2, int y2)
{
	//return std::abs(x1 - x2) + std::abs(y1-y2);
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

pair<int, int> Enemy::bestNode(map <pair<int, int>, Node2> l) {
	float m_coutf = l.begin()->second.fValue;
	pair<int, int> m_noeud = l.begin()->first;
	if (inversion) {
		for (map <pair<int, int>, Node2>::reverse_iterator i = l.rbegin(); i != l.rend() && !game->isFinishGame(); i++)
			if (i->second.fValue < m_coutf) {
				m_coutf = i->second.fValue;
				m_noeud = i->first;
			}
	}
	else {
		for (map <pair<int, int>, Node2>::iterator i = l.begin(); i != l.end() && !game->isFinishGame(); i++)
			if (i->second.fValue < m_coutf) {
				m_coutf = i->second.fValue;
				m_noeud = i->first;
			}
	}


	return m_noeud;
}

void Enemy::addToClosedList(pair<int, int>& p) {

	Node2& n = openList[p];
	closedList[p] = n;

	/* il faut le supprimer de la liste ouverte, ce n'est plus une solution explorable */
	if (openList.erase(p) == 0)
		cerr << "Erreur, le noeud n'apparait pas dans la liste ouverte, impossible à supprimer" << endl;
	return;
}

vector<pair<int, int>> Enemy::recoverPath(Node2 start, Node2 objectif)
{
	vector <pair<int, int>>chemin;
	/*Position posPlayer = game->getPlayers().at(0).getPosition();*/
	Node2 tmp;
	/* l'arrivée est le dernier élément de la liste fermée */
	map <pair<int, int>, Node2>::iterator it;
	if (inversion) {
		map <pair<int, int>, Node2>::iterator it = closedList.begin();
		//Node2& tmp = closedList[pair<int, int>(objectif.position.x, objectif.position.y)];
		tmp = it->second;
	}
	else {
		map <pair<int, int>, Node2>::reverse_iterator it = closedList.rbegin();
		//Node2& tmp = closedList[pair<int, int>(objectif.position.x, objectif.position.y)];
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


	while (prec != pair<int, int>(start.parent.x, start.parent.y) && !game->isFinishGame()) {

		n.first = prec.first;
		n.second = prec.second;
		chemin.insert(chemin.begin(), n);
		tmp = closedList[pair<int, int>(tmp.parent.x, tmp.parent.y)];
		prec.first = tmp.position.x;
		prec.second = tmp.position.y;
	}
	return chemin;
}

bool Enemy::nodeExistInList(std::pair<int, int> n, std::map<std::pair<int, int>, Node2>& l)
{
	std::map<std::pair<int, int>, Node2>::iterator i = l.find(n);
	if (i == l.end())
		return false;
	else
		return true;
}

int Enemy::findDirection(vector < pair<int, int> >v) { // en fonction de sa position et de la prochaine l'enemi saura dans quelle direction avancer logiquement

	float x = getPosition().getX();
	float nextX = v.at(indicePath).first * 30;
	float y = getPosition().getY();
	float nextY = v.at(indicePath).second * 30;
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

void Enemy::moveToPos( vector < pair<int, int> >v) {
	int i = 0;
	while (i < 50000 && !game->isFinishGame()) {
		switch (findDirection(v)) {
		case 0:
			move(0, -0.0006);   //mouvement graphique
			setAnimY(Up);
			break;
		case 1:
			move(0, 0.0006);
			setAnimY(Down);
			break;
		case 2:
			move(0.0006, 0);
			setAnimY(Right);
			break;
		case 3:
			move(-0.0006, 0);
			setAnimY(Left);
			break;
		case 4:
			move(0.0006, 0.0006);
			setAnimY(Down);
			break;
		case 5:
			move(-0.0006, -0.0006);
			setAnimY(Up);
			break;
		case 6:
			move(-0.0006, 0.0006);
			setAnimY(Down);
			break;
		case 7:
			move(0.0006, -0.0006);
			setAnimY(Up);
			break;

		}
		uptadeSpritePosition();
		i++;
	}
	//}
	switch (findDirection(v)) {
	case 0:
		//de la position de l ennemi et non sa hitbox aparemment)
		setPositionHitbox(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		setPosition(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		break;
	case 1:
		setPositionHitbox(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		setPosition(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		break;
	case 2:
		setPositionHitbox(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		setPosition(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		break;
	case 3:
		setPositionHitbox(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		setPosition(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		break;
	case 4:
		setPositionHitbox(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		setPosition(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		break;
	case 5:
		setPositionHitbox(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		setPosition(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		break;
	case 6:
		setPositionHitbox(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		setPosition(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		break;
	case 7:
		setPositionHitbox(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		setPosition(v.at(getIndicePath()).first * 30, v.at(getIndicePath()).second * 30);
		break;

	}


	uptadeSpritePosition();
}
