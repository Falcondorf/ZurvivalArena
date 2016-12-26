#include "Game.h"
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
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
		for (unsigned i = 0;i < enemies_.size();i++) {

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

void Game::manageEnemi(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time) {

	for (unsigned i = 0;i < enemies_.size();i++) {
		enemies_.at(i).manageSprite(fpsCount, fpsSpeed, switchFps, time);
		enemies_.at(i).setState(Idle);
	}

}

std::vector<sf::Vector2f> Game::brain(unsigned idEnemy) {
	bool end = false;
	std::vector<Node> openList;     // openList est la liste des n�uds adjacents au n�ud courantpas encore �valu�
	std::vector<Node> closedList; //la liste des n�uds qui ont �t� �valu�s en temps que n�ud courant.
	Enemy en = enemies_.at(idEnemy);
	int i = en.getHitbox().getPosition().x;
	int j = en.getHitbox().getPosition().y;
	//Node noeud{ getPlayer(numJoueur).getPos(),std::pair<unsigned, unsigned>(i,j), 0, board_.getFrameHV(i,j,numJoueur - 1), 0 };   //on cr�e le noeud ou se trouve le joueur �valu� 
	//openList.push_back(noeud);    // on place le noeud sur lequel est le joueur dans l openlist
	Node node;
	node.position = en.getHitbox().getPosition();
	node.parent = en.getHitbox().getPosition();
	node.fValue = 0;
	node.gValue = 0;
	node.hValue = spaceCase(en.getHitbox().getPosition());
	openList.push_back(node);

	while (!openList.empty() && !end) {
		//  tant que la liste n'est pas vide si il n'y a pas de chemin et pas end (quand hvalue = 0 c�d  qu on est de l autre cot�)
		int fVal = 1000;
		Node q;
		int cpt = 0;
		int itQ = 0;
		std::cout << openList.size() << std::endl;
		for (Node n : openList) {  //on parcourt tous les noeuds � traiter
			cpt++;
			if (n.fValue < fVal) {  //trouve la fValue la plus petite
				fVal = n.fValue;
				q.parent = n.parent;
				q.position = n.position;
				q.fValue = n.fValue;
				q.gValue = n.gValue;
				q.hValue = n.hValue;
				itQ = cpt; // it�rateur de node servant � vid� de l'openList le noeud avec la fvalue la plus petite
			}
		}
		openList.erase(openList.begin() + itQ - 1);
		// enl�ve de l'openList le noeud avec la fvalue la plus petite

		std::vector<Node> successors;
		generateSuccessors(q.position, &successors, q);
		//cr�ation des successeurs du noeuds �valu�.
		for (Node n : successors) {
			if (n.hValue == 0) {
				//Goal atteint, arret de la recherche
				end = true;
				std::cout << "FIN" << std::endl;
				break;
			}
			n.gValue = q.gValue + 1;
			//Attribution de la valeur gVal (score de parcours)
			n.fValue = n.gValue + n.hValue;
			//Attribution de la valeur fVal (score de noeud) - somme de la gVal et fVal

			if (!parcourOpen(openList, n.position, n.fValue) && !parcourClosed(closedList, n.position, n.fValue)) {
				//Si on a pas trouv� une node avec une fVal 
				//plus int�rressante dans les listes, elle peut �tre 
				//prise dans l'openList car elle poss�de un score
				//plus proche de la solution de chemin.
				openList.push_back(n);
				
			}
		}


		closedList.push_back(q);
	}
	//On met le noeud qui �tait �valu� dans la closedList (liste des noeuds trait�)
	Node current = closedList.back();
	//On r�cup�re le dernier noeuds du chemin
	std::vector<sf::Vector2f> reversePath;
	//Vecteur qui contiendra les positions des noeuds d�crivant le chemin de retour 
	reversePath.push_back(sf::Vector2f(current.position.x, current.position.y));
	//On prend d�j� le noeud courant (dernier de 
	//la closed list
	while (current.position.x != current.parent.x || current.position.y != current.parent.y) {
		//Le noeud parent � comme position
		//de noeud parent sa propre position
		for (Node n : closedList) {
			//On parcourt la closedList 
			if (n.position.x == current.parent.x && n.position.y == current.position.y) {
				// On cherche le parent du noeud
				current = n;
				break;
			}
		}
		reversePath.push_back((sf::Vector2f(current.position.x, current.position.y)));
		//On ajout le noeud courant 
		//(anciennement le parent)

	}
	return reversePath;
}

unsigned Game::spaceCase(Vector2f pos) {
	unsigned hValue;
	hValue = std::abs(players_.at(0).getHitbox().getPosition().x - pos.x);
	hValue += std::abs(players_.at(0).getHitbox().getPosition().y - pos.y);

	return hValue;
}

void Game::generateSuccessors(Vector2f pos, std::vector<Node> *successors, Node parent) {
	// manque les diagonale
	if (pos.x >= 30 && arena_.isFree(pos.x - 30, pos.y)) {
		if (pos.x - 60 != parent.position.x || pos.y != parent.position.y) {
			Node node{ parent.position, sf::Vector2f(pos.x - 60, pos.y), 0, spaceCase(sf::Vector2f(pos.x - 60, pos.y)),0 };
			successors->push_back(node);
		}

	}
	if (pos.x < arena_.getWidth() /* * 2 - 3*/ && arena_.isFree(pos.x + 30, pos.y)) {
		if (pos.x + 60 != parent.position.x || pos.y != parent.position.y) {
			Node node{ parent.position, sf::Vector2f(pos.x + 60, pos.y), 0, spaceCase(sf::Vector2f(pos.x + 60, pos.y)),0 };
			successors->push_back(node);
		}

	}
	if (pos.y >= 30 && arena_.isFree(pos.x, pos.y - 30)) {
		if (pos.x != parent.position.x || pos.y - 60 != parent.position.y) {
			Node node{ parent.position, sf::Vector2f(pos.x, pos.y - 60), 0, spaceCase(sf::Vector2f(pos.x, pos.y - 60)),0 };
			successors->push_back(node);

		}
	}
	if (pos.y < arena_.getWidth() /* * 2 - 3*/ && arena_.isFree(pos.x, pos.y + 30)) {
		if (pos.x != parent.position.x || pos.y + 60 != parent.position.y) {
			Node node{ parent.position, sf::Vector2f(pos.x, pos.y + 60), 0, spaceCase(sf::Vector2f(pos.x, pos.y + 60)),0 };
			successors->push_back(node);
		}

	}
}

bool Game::parcourOpen(std::vector<Node> openList, sf::Vector2f position, int fValue) {
	// Evalue qu'un noeud �valu� � une 
	//m�me position ait une fValue moins int�ressante
	bool ok = false;

	for (Node node : openList) {
		if (node.position.x == position.x &&
			node.position.y == position.y &&
			node.fValue < fValue) {
			ok = true;
			break;
		}

	}
	return ok;
}

bool Game::parcourClosed(std::vector<Node> closedList, sf::Vector2f position, int fValue) {
	// Evalue qu'un noeud �valu� � une 
	//m�me position ait une fValue moins int�ressante
	bool ok = false;
	for (Node node : closedList) {
		if (node.position.x == position.x &&
			node.position.y == position.y &&
			node.fValue < fValue) {
			ok = true;
			break;
		}

	}
	return ok;
}