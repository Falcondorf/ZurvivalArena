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
	*\brief represente la position pr�cedente avant le noeud.
	*/
	sf::Vector2f parent;
	/*!
	*\brief represente la position du noeud courant.
	*/
	sf::Vector2f position;
	/*!
	*\brief represente le cout pour aller du point de d�part au noeud consid�r�
	*/
	unsigned gValue;
	/*!
	*\brief represente le cout pour aller du noeud consid�r� au point de destination
	*/
	unsigned hValue;
	/*!
	*\brief represente la somme des pr�c�dents mais m�moris� pour ne pas le recalculer � chaque fois
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
	* \brief Attribut priv� permettant � l'ennemi de calculer le chemin lors de son initialisation.
	*/
	unsigned start = 0;
	/*!
	* \brief Attribut priv� permmettant de d�finir la difficult� qu'un ennemi doit avoir.
	*/
	unsigned idLevel=1;
	/*!
	* \brief Attribut priv� repr�sentant l'�tat du jeu courant.
	*/
	Game * game=nullptr;
	/*!
	* \brief Attribut priv� repr�sentant la liste des positions � suivrent pour arriver aux joueurs.
	*/
	std::vector<std::pair<int, int>> pathToPlayer;
	/*!
	* \brief Attribut priv� permettant de savoir � quel position l'ennemi est arriv� dans la liste de position � suivre vers les joueurs.
	*/
	int indicePath;
	/*!
	* \brief Attribut priv� permettant de savoir si la texture de l'ennemi a chang�e.
	*/
	bool textChange = false;
	/*!
	* \brief Attribut priv� repr�sentant l'identifiant de l'ennemi.
	*/
	unsigned id;
	/*!
	* \brief Attribut priv� permettant de lancer un thread pour le d�placement de l'ennemi.
	*/
	std::thread threadEnemies;
	/*!
	* \brief Attribut priv� repr�sentant la position de d�part de l'ennemi.
	*/
	Position positionFirst;
	/*!
	* \brief Attribut priv� permettant de repr�sent� la liste des noeuds � trait� dans l'algorithme a* de l'ennemi
	*/
	std::map <std::pair<int, int>, Node2> openList;
	/*!
	* \brief Attribut priv� permettant de repr�sent� la liste des noeuds qui ont d�j� �t� trait� par l'algorithme a* de l'ennemi.
	*/
	std::map <std::pair<int, int>, Node2> closedList;
	/*!
	* \brief Attribut priv� permettant de savoir si un des jouers � effectu� un mouvement.
	*/
	bool playerMove;
	/*!
	* \brief Attribut priv� permettant de savoir si il faudra lire invers�mement le chemin donn� par l'algorithme a* de l'ennemi.
	*/
	bool inversion = false;
	/*!
	* \brief M�thod� priv� permettant d'�tablir un chemin vers les joueurs gr�ce � l'algorithme a*.
	*/
	void brain();
	/*!
	* \brief M�thode priv� consiste � rep�rer les noeuds adjacents et � les ajouter ou non � la liste ouverte.
	* \param n d�termine la position du noeud courant. 
	*/
	void addAdjectentCell(std::pair<int, int>& n);
	/*!
	* \brief M�thode priv� consiste donn� la distance entre deux points.
	* \param x1 la position en absisse du premier point.
	* \param y1 la position en ordonn� du premier point.
	* \param x2 la position en absisse du deuxi�me point.
	* \param y2 la position en ordonn� du deuxi�me point.
	* \return la distance entre les deux points.
	*/
	float distance(int x1, int y1, int x2, int y2);
	/*!
	* \brief M�thode priv� consiste � rep�rer le meilleur noeud dans la liste ouverte.
	* \param n d�termine la position du noeud courant.
	*/
	std::pair<int, int> bestNode(std::map <std::pair<int, int>, Node2> l);
	/*!
	* \brief M�thode priv� consiste � ajouter un noeud dans la liste ferm�e
	* \param p L'identifiant du noeud qui sera rajout� dans la liste.
	*/
	void addToClosedList(std::pair<int, int>& p);
	/*!
	* \brief M�thode priv� consiste � �tablir un chemin gr�ce � la m�thode brain.
	* \param start Le noeud de d�part.
	* \param objectif Le noeud objectif que l'on veut atteindre
	* \return le chemin qui va du d�part jusqu'� l'objectif.
	*/
	std::vector<std::pair<int, int>> recoverPath(Node2 start, Node2 objectif);
	/*!
	* \brief M�thode priv� consiste � v�rifi� si un noeud est pr�sent ou non dans la liste ferm�e et dans la liste ouverte.
	* \param n L'identifiant du noeud � v�rifi�
	* \param l La liste que l'on va test�. 
	*/
	bool nodeExistInList(std::pair<int, int> n, std::map<std::pair<int, int>, Node2>& l);
	/*!
	* \brief M�thode priv� permet � l'ennemi de savoir dans quel direction il doit aller.
	* \param v la liste des positions que l'ennemi doit suivre.
	* \return un entier qui repr�sente la direction que l'ennemi doit suivre.
	*/
	int findDirection(std::vector < std::pair<int, int> >v);
	/*!
	* \brief M�thode priv� consiste � faire d�placer l'ennemi gr�ce � sa liste de position � suivre et la m�thode findDirection().
	* \param v La liste de position � suivre.
	*/
	void moveToPos(std::vector < std::pair<int, int> >v);
	/*!
	* \brief M�thode priv� permettant � l'ennemi de savoir si un joueur est � cot� de lui.
	* \ return vrai si c'est le cas, faux sinon. 
	*/
	bool isAdjacent();
	/*!
	* \brief M�thode priv� consiste � charg� la texture de d�part de l'ennemi.
	*/
	void loadTextureStart();
	/*!
	* \brief M�thode priv� consiste � charg� la texture de l'ennemi.
	*/
	void loadTexture();
	/*!
	* \brief M�thode priv� consiste � mettre � jour la position du sprite de l'ennemi
	*/
	void uptadeSpritePosition();
	/*!
	* \brief M�thode priv� consiste � faire bouger automatiquement les ennemis vers les joueurs.
	*/
	void functionMovingEnemies();
public:
	/*!
	* \brief Constructeur de la classe Enemy
	* \param position La position de l'ennemi
	* \param pv Les points de vie de l'ennemi
	* \param id L'identifiant de l'ennemi
	* \param gam L'�tat courant du jeux.
	*/
	Enemy(Position position, int pv,unsigned id, Game * gam);
	/*!
	* \brief M�thode public consiste � mettre � jour l'attribut qui d�termine si un joueur a bouger.
	* \param b La nouvelle valeur � donner � l'attribut
	*/
	void setPlayerMoving(bool b);
	/*!
	* \brief M�thode public faisant appel � la m�thode priv� loadTexture()
	*/
	void setHitTextureDepart();
	/*!
	* \brief M�thode public permettant de lancer le thread.
	*/
	void startMovingEnemies();
	/*!
	* \brief M�thode public faisant appel � la m�thode loadTexture()
	*/
	void spriteLevel();
	/*!
	* \brief M�thode public consiste � pass� au niveau suivant.
	*/
	void nextLevel();
	/*!
	* \brief M�thode public consiste � recharg� l'�tat de base de l'ennemi.
	*/
	inline void reload();
	/*!
	* \brief M�thode public consiste � donn� la position de d�part de l'ennemi.
	* \return la position de d�part de l'ennemi.
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



