#pragma once

#include "Character.h"
#include <string>
#include <thread>
/*!
*\brief Structure qui represente un noeud pour l'algorithme a*.
*\author Aynaou Dupont Fakir Bauwens Temsamani
*/
struct Node2 {
	/*!
	*\brief represente la position précedente avant le noeud.
	*/
	sf::Vector2f parent;
	/*!
	*\brief represente la position du noeud courant.
	*/
	sf::Vector2f position;
	/*!
	*\brief represente le cout pour aller du point de départ au noeud considéré
	*/
	unsigned gValue;
	/*!
	*\brief represente le cout pour aller du noeud considéré au point de destination
	*/
	unsigned hValue;
	/*!
	*\brief represente la somme des précédents mais mémorisé pour ne pas le recalculer à chaque fois
	*/
	unsigned fValue;
};

class Game;
/*!
*\brief Class qui represente un ennemi dans le jeu.
*\file enemy.h
*\author Aynaou Dupont Fakir Bauwens Temsamani
*/
class Enemy : public Character {
private:
	/*!
	* \brief Attribut privé permettant à l'ennemi de calculer le chemin lors de son initialisation.
	*/
	unsigned start = 0;
	/*!
	* \brief Attribut privé permmettant de définir la difficulté qu'un ennemi doit avoir.
	*/
	unsigned idLevel=1;
	/*!
	* \brief Attribut privé représentant l'état du jeu courant.
	*/
	Game * game=nullptr;
	/*!
	* \brief Attribut privé représentant la liste des positions à suivrent pour arriver aux joueurs.
	*/
	std::vector<std::pair<int, int>> pathToPlayer;
	/*!
	* \brief Attribut privé permettant de savoir à quel position l'ennemi est arrivé dans la liste de position à suivre vers les joueurs.
	*/
	int indicePath;
	/*!
	* \brief Attribut privé permettant de savoir si la texture de l'ennemi a changée.
	*/
	bool textChange = false;
	/*!
	* \brief Attribut privé représentant l'identifiant de l'ennemi.
	*/
	unsigned id;
	/*!
	* \brief Attribut privé permettant de lancer un thread pour le déplacement de l'ennemi.
	*/
	std::thread threadEnemies;
	/*!
	* \brief Attribut privé représentant la position de départ de l'ennemi.
	*/
	Position positionFirst;
	/*!
	* \brief Attribut privé permettant de représenté la liste des noeuds à traité dans l'algorithme a* de l'ennemi
	*/
	std::map <std::pair<int, int>, Node2> openList;
	/*!
	* \brief Attribut privé permettant de représenté la liste des noeuds qui ont déjà été traité par l'algorithme a* de l'ennemi.
	*/
	std::map <std::pair<int, int>, Node2> closedList;
	/*!
	* \brief Attribut privé permettant de savoir si un des jouers à effectué un mouvement.
	*/
	bool playerMove;
	/*!
	* \brief Attribut privé permettant de savoir si il faudra lire inversémement le chemin donné par l'algorithme a* de l'ennemi.
	*/
	bool inversion = false;
	/*!
	* \brief Méthodé privé permettant d'établir un chemin vers les joueurs grâce à l'algorithme a*.
	*/
	void brain();
	/*!
	* \brief Méthode privé consiste à repérer les noeuds adjacents et à les ajouter ou non à la liste ouverte.
	* \param n détermine la position du noeud courant. 
	*/
	void addAdjectentCell(std::pair<int, int>& n);
	/*!
	* \brief Méthode privé consiste donné la distance entre deux points.
	* \param x1 la position en absisse du premier point.
	* \param y1 la position en ordonné du premier point.
	* \param x2 la position en absisse du deuxième point.
	* \param y2 la position en ordonné du deuxième point.
	* \return la distance entre les deux points.
	*/
	float distance(int x1, int y1, int x2, int y2);
	/*!
	* \brief Méthode privé consiste à repérer le meilleur noeud dans la liste ouverte.
	* \param n détermine la position du noeud courant.
	*/
	std::pair<int, int> bestNode(std::map <std::pair<int, int>, Node2> l);
	/*!
	* \brief Méthode privé consiste à ajouter un noeud dans la liste fermée
	* \param p L'identifiant du noeud qui sera rajouté dans la liste.
	*/
	void addToClosedList(std::pair<int, int>& p);
	/*!
	* \brief Méthode privé consiste à établir un chemin grâce à la méthode brain.
	* \param start Le noeud de départ.
	* \param objectif Le noeud objectif que l'on veut atteindre
	* \return le chemin qui va du départ jusqu'à l'objectif.
	*/
	std::vector<std::pair<int, int>> recoverPath(Node2 start, Node2 objectif);
	/*!
	* \brief Méthode privé consiste à vérifié si un noeud est présent ou non dans la liste fermée et dans la liste ouverte.
	* \param n L'identifiant du noeud à vérifié
	* \param l La liste que l'on va testé. 
	*/
	bool nodeExistInList(std::pair<int, int> n, std::map<std::pair<int, int>, Node2>& l);
	/*!
	* \brief Méthode privé permet à l'ennemi de savoir dans quel direction il doit aller.
	* \param v la liste des positions que l'ennemi doit suivre.
	* \return un entier qui représente la direction que l'ennemi doit suivre.
	*/
	int findDirection(std::vector < std::pair<int, int> >v);
	/*!
	* \brief Méthode privé consiste à faire déplacer l'ennemi grâce à sa liste de position à suivre et la méthode findDirection().
	* \param v La liste de position à suivre.
	*/
	void moveToPos(std::vector < std::pair<int, int> >v);
	/*!
	* \brief Méthode privé permettant à l'ennemi de savoir si un joueur est à coté de lui.
	* \ return vrai si c'est le cas, faux sinon. 
	*/
	bool isAdjacent();
	/*!
	* \brief Méthode privé consiste à chargé la texture de départ de l'ennemi.
	*/
	void loadTextureStart();
	/*!
	* \brief Méthode privé consiste à chargé la texture de l'ennemi.
	*/
	void loadTexture();
	/*!
	* \brief Méthode privé consiste à mettre à jour la position du sprite de l'ennemi
	*/
	void uptadeSpritePosition();
	/*!
	* \brief Méthode privé consiste à faire bouger automatiquement les ennemis vers les joueurs.
	*/
	void functionMovingEnemies();
public:
	/*!
	* \brief Constructeur de la classe Enemy
	* \param position La position de l'ennemi
	* \param pv Les points de vie de l'ennemi
	* \param id L'identifiant de l'ennemi
	* \param gam L'état courant du jeux.
	*/
	Enemy(Position position, int pv,unsigned id, Game * gam);
	/*!
	* \brief Méthode public consiste à mettre à jour l'attribut qui détermine si un joueur a bouger.
	* \param b La nouvelle valeur à donner à l'attribut
	*/
	void setPlayerMoving(bool b);
	/*!
	* \brief Méthode public faisant appel à la méthode privé loadTexture()
	*/
	void setHitTextureDepart();
	/*!
	* \brief Méthode public permettant de lancer le thread.
	*/
	void startMovingEnemies();
	/*!
	* \brief Méthode public faisant appel à la méthode loadTexture()
	*/
	void spriteLevel();
	/*!
	* \brief Méthode public consiste à passé au niveau suivant.
	*/
	void nextLevel();
	/*!
	* \brief Méthode public consiste à rechargé l'état de base de l'ennemi.
	*/
	inline void reload();
	/*!
	* \brief Méthode public consiste à donné la position de départ de l'ennemi.
	* \return la position de départ de l'ennemi.
	*/
	inline const Position &getPositionFirst() const;
};

void Enemy::reload() {
	start = 0;
	setPosition(positionFirst.getX(), positionFirst.getY());
	setPositionHitbox(positionFirst.getX(), positionFirst.getY());
	setPositionSprite(sf::Vector2f(positionFirst.getX(), positionFirst.getY()));
	startMovingEnemies();
}

const Position & Enemy::getPositionFirst() const {
	return positionFirst;
}



