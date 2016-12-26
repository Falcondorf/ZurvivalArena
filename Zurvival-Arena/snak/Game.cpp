#include "Game.h"
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <utility>
#include <iterator>
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
			return true;
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

const std::vector<Enemy> & Game::getEnemies() const {
	return enemies_;
}
void Game::functionMovingEnemies() {
	using namespace std::chrono_literals;
	Vector2f p;
	while (!gameFinish) {
		for (unsigned i = 0; i < enemies_.size(); i++) {

			enemies_.at(i).move(0, 0.00006);
			enemies_.at(i).setAnimY(Down);
			enemies_.at(i).uptadeSpritePosition();
			enemies_.at(i).setState(Moving);
			//enemies_.at(i).manageSprite(fpsCount, fpsSpeed, switchFps, time);
			//arena_.updateMatrice(enemies_.at(i).getHitbox().getPosition(), float x,float y );
		}

	}
	threadEnemies->detach();
}

void Game::startMovingEnemies() {
	threadEnemies = std::unique_ptr < std::thread >(new std::thread(&Game::functionMovingEnemies, this));

}

bool Game::nodeExistInList(pair<int, int> n, map<pair<int, int>, Node>& l)
{
	map<pair<int, int>, Node>::iterator i = l.find(n);
	if (i == l.end())
		return false;
	else
		return true;
}

void Game::manageEnemi(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time) {

	for (unsigned i = 0; i < enemies_.size(); i++) {
		enemies_.at(i).manageSprite(fpsCount, fpsSpeed, switchFps, time);
		enemies_.at(i).setState(Idle);
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
	Position posPlayer = players_[0].getPosition();
	Node tmp;
	for (int i = n.first - 1; i <= n.first + 1; i++) {
		if ((i < 0) || (i >= arena_.getHeight()))  /* en dehors de l'arène, on oublie */
			continue;
		for (int j = n.second - 1; j <= n.second + 1; j++) {
			if ((j < 0) || (j >= arena_.getWidth()))   /* en dehors de l'arène, on oublie */
				continue;
			if ((i == n.first) && (j == n.second))  /* case actuelle n, on oublie */
				continue;
			if (arena_.getTiles()[i][j])
				/* obstace, terrain non franchissable, on oublie */
				continue;
			pair<int, int> it(i, j);
			if (!nodeExistInList(it, closedList)) {
				/* le noeud n'est pas déjà présent dans la liste fermée */
				/* calcul du cout G du noeud en cours d'étude : cout du parent + distance jusqu'au parent */
				tmp.gValue = closedList[n].gValue + distance(i, j, n.first, n.second);
				/* calcul du cout H du noeud à la destination */
				tmp.hValue = distance(i, j, posPlayer.getX(), posPlayer.getY());
				tmp.fValue = tmp.gValue + tmp.hValue;
				tmp.position = Vector2f(n.first,n.second);

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
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}


//std::vector<sf::Vector2f> Game::brain(unsigned idEnemy) {
//	bool end = false;
//	std::vector<Node> openList;     // openList est la liste des nœuds adjacents au nœud courantpas encore évalué
//	std::vector<Node> closedList; //la liste des nœuds qui ont été évalués en temps que nœud courant.
//	Enemy en = enemies_.at(idEnemy);
//	int i = en.getHitbox().getPosition().x;
//	int j = en.getHitbox().getPosition().y;
//	//Node noeud{ getPlayer(numJoueur).getPos(),std::pair<unsigned, unsigned>(i,j), 0, board_.getFrameHV(i,j,numJoueur - 1), 0 };   //on crée le noeud ou se trouve le joueur évalué 
//	//openList.push_back(noeud);    // on place le noeud sur lequel est le joueur dans l openlist
//	Node node;
//	node.position = en.getHitbox().getPosition();
//	node.parent = en.getHitbox().getPosition();
//	node.fValue = 0;
//	node.gValue = 0;
//	node.hValue = spaceCase(en.getHitbox().getPosition());
//	openList.push_back(node);
//
//	while (!openList.empty() && !end) {
//		//  tant que la liste n'est pas vide si il n'y a pas de chemin et pas end (quand hvalue = 0 càd  qu on est de l autre coté)
//		int fVal = 1000;
//		Node q;
//		int cpt = 0;
//		int itQ = 0;
//		std::cout << openList.size() << std::endl;
//		for (Node n : openList) {  //on parcourt tous les noeuds à traiter
//			cpt++;
//			if (n.fValue < fVal) {  //trouve la fValue la plus petite
//				fVal = n.fValue;
//				q.parent = n.parent;
//				q.position = n.position;
//				q.fValue = n.fValue;
//				q.gValue = n.gValue;
//				q.hValue = n.hValue;
//				itQ = cpt; // itérateur de node servant à vidé de l'openList le noeud avec la fvalue la plus petite
//			}
//		}
//		openList.erase(openList.begin() + itQ - 1);
//		// enlève de l'openList le noeud avec la fvalue la plus petite
//		std::vector<Node> successors;
//		generateSuccessors(q.position, &successors, q);
//		//création des successeurs du noeuds évalué.
//		for (Node n : successors) {
//			if (n.hValue == 0) {
//				//Goal atteint, arret de la recherche
//				end = true;
//				std::cout << "FIN" << std::endl;
//				break;
//			}
//			n.gValue = q.gValue + 1;
//			//Attribution de la valeur gVal (score de parcours)
//			n.fValue = n.gValue + n.hValue;
//			//Attribution de la valeur fVal (score de noeud) - somme de la gVal et fVal
//
//			if (!parcourOpen(openList, n.position, n.fValue) && !parcourClosed(closedList, n.position, n.fValue)) {
//				//Si on a pas trouvé une node avec une fVal 
//				//plus intérressante dans les listes, elle peut être 
//				//prise dans l'openList car elle possède un score
//				//plus proche de la solution de chemin.
//				openList.push_back(n);
//				
//			}
//		}
//
//
//		closedList.push_back(q);
//	}
//	//On met le noeud qui était évalué dans la closedList (liste des noeuds traité)
//	Node current = closedList.back();
//	//On récupère le dernier noeuds du chemin
//	std::vector<sf::Vector2f> reversePath;
//	//Vecteur qui contiendra les positions des noeuds décrivant le chemin de retour 
//	reversePath.push_back(sf::Vector2f(current.position.x, current.position.y));
//	//On prend déjà le noeud courant (dernier de 
//	//la closed list
//	while (current.position.x != current.parent.x || current.position.y != current.parent.y) {
//		//Le noeud parent à comme position
//		//de noeud parent sa propre position
//		for (Node n : closedList) {
//			//On parcourt la closedList 
//			if (n.position.x == current.parent.x && n.position.y == current.position.y) {
//				// On cherche le parent du noeud
//				current = n;
//				break;
//			}
//		}
//		reversePath.push_back((sf::Vector2f(current.position.x, current.position.y)));
//		//On ajout le noeud courant 
//		//(anciennement le parent)
//
//	}
//	return reversePath;
//}
//
//
//void Game::generateSuccessors(Vector2f pos, std::vector<Node> *successors, Node parent) {
//	// manque les diagonale
//	if (pos.x >= 30 && arena_.isFree(pos.x - 30, pos.y)) {
//		if (pos.x - 60 != parent.position.x || pos.y != parent.position.y) {
//			Node node{ parent.position, sf::Vector2f(pos.x - 60, pos.y), 0, spaceCase(sf::Vector2f(pos.x - 60, pos.y)),0 };
//			successors->push_back(node);
//		}
//
//	}
//	if (pos.x < arena_.getWidth() /* * 2 - 3*/ && arena_.isFree(pos.x + 30, pos.y)) {
//		if (pos.x + 60 != parent.position.x || pos.y != parent.position.y) {
//			Node node{ parent.position, sf::Vector2f(pos.x + 60, pos.y), 0, spaceCase(sf::Vector2f(pos.x + 60, pos.y)),0 };
//			successors->push_back(node);
//		}
//
//	}
//	if (pos.y >= 30 && arena_.isFree(pos.x, pos.y - 30)) {
//		if (pos.x != parent.position.x || pos.y - 60 != parent.position.y) {
//			Node node{ parent.position, sf::Vector2f(pos.x, pos.y - 60), 0, spaceCase(sf::Vector2f(pos.x, pos.y - 60)),0 };
//			successors->push_back(node);
//
//		}
//	}
//	if (pos.y < arena_.getWidth() /* * 2 - 3*/ && arena_.isFree(pos.x, pos.y + 30)) {
//		if (pos.x != parent.position.x || pos.y + 60 != parent.position.y) {
//			Node node{ parent.position, sf::Vector2f(pos.x, pos.y + 60), 0, spaceCase(sf::Vector2f(pos.x, pos.y + 60)),0 };
//			successors->push_back(node);
//		}
//
//	}
//}
//
//bool Game::parcourOpen(std::vector<Node> openList, sf::Vector2f position, int fValue) {
//	// Evalue qu'un noeud évalué à une 
//	//même position ait une fValue moins intéressante
//	bool ok = false;
//
//	for (Node node : openList) {
//		if (node.position.x == position.x &&
//			node.position.y == position.y &&
//			node.fValue < fValue) {
//			ok = true;
//			break;
//		}
//
//	}
//	return ok;
//}
//
//bool Game::parcourClosed(std::vector<Node> closedList, sf::Vector2f position, int fValue) {
//	// Evalue qu'un noeud évalué à une 
//	//même position ait une fValue moins intéressante
//	bool ok = false;
//	for (Node node : closedList) {
//		if (node.position.x == position.x &&
//			node.position.y == position.y &&
//			node.fValue < fValue) {
//			ok = true;
//			break;
//		}
//
//	}
//	return ok;
//}