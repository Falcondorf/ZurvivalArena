#pragma once

#include "Arena.h"
#include <vector>
#include "Heroes.h"
#include "Enemy.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <map>
#include <utility>
#include <SFML\Graphics.hpp>
#include <iostream>

/*!
*\brief Class qui g�re le d�roulement de la partie, les interactions entre joueurs et ennemis.
*\file Game.h
*\author Aynaou Dupont Fakir Bauwens
*/
class Game {
private:
	/*!
	*\brief Contient le nombre de point de vie pour les ennemis d'un niveau sp�cifique.
	*/
	std::vector<unsigned> pvForLevel;
	/*!
	*\brief l'identifiant du niveau.
	*/
	unsigned idLevel = 0;
	/*!
	*\brief verrou servant � empecher que plusieurs ennemi fassent leur brain en meme temps.
	*/
	bool brainLock = false;
	/*!
	*\brief le nombre d'ennemi pour le niveau courant.
	*/
	unsigned nbEnemies = 0; // � suppr
							/*!
							*\brief La carte dans laquelle se d�roule la partie. Elle contient des obstacles.
							*/
	Arena arena_;
	/*!
	*\brief La liste des ou du player.
	*/
	std::vector<Character> players_;
	/*!
	*\brief La liste des ennemis.
	*/
	std::vector<Enemy> enemies_;
	/*!
	*\brief bool�en indiquant si le jeu est fini.
	*/
	bool gameFinish = false;
public:

	/*!
	* \brief Permet de savoir si le jeu est termin�.
	* \return vrai si le jeu est termin�.
	*/
	bool isFinishGame() const;


	/*!
	* \brief constructeur du jeu prenant les dimension du jeu en parametre.
	* \param width la largeur de la carte.
	* \param height la hauteur de la carte.
	*/
	Game(unsigned width, unsigned height);

	/*!
	* \brief Permet de savoir si un joueur est en collision avec un obstacle ou un ennemi (des pv seront retir� si il se trouve sur une case ennemi).
	* \param idPlayer l'identifiant du joueur � v�rifier
	* \param movex la position x vers laquelle le joueur veux se d�placer (qui est � v�rifier)
	* \param movey la position y vers laquelle le joueur veux se d�placer (qui est � v�rifier)
	* \return vrai si il y a une collision avec un obstacle ou un ennemi.
	*/
	bool hasCollision(int idPlayer, float movex, float movey);

	/*!
	* \brief Permet de savoir si il y a une intersection entre deux rectangleShapes
	* \param rect1 le premier rectangle
	* \param rect2 le deuxieme rectangle
	* \return vrai si il y a une intersection entre les deux rectangles
	*/
	static bool intersects(const sf::RectangleShape & rect1, const sf::RectangleShape & rect2);

	/*!
	* \brief bouge le joueur vers une position.
	* \param idplayer l'identifiant du joueur � d�placer.
	* \param xMove le x de la position vers laquelle d�placer l'ennemi.
	* \param yMove le y de la position vers laquelle d�placer l'ennemi.
	*/
	void move(int idplayer, float xMove, float yMove);

	/*!
	* \brief indique le nombre de player dans la partie.
	* \return le nombre de player dans la partie.
	*/
	unsigned getNbPlayers()const;

	/*!
	* \brief ajoute un enemi dans le jeu
	* \param posX l'abcisse de la position de l'ennemi
	* \param posY l'ordonn�e de la position de l'ennemi
	* \param pv le nombre de pv de l'ennemi au d�part.
	*/
	void addEnemy(float posX, float posY, int pv = 1);

	/*!
	* \brief la liste d'ennemis pr�sent dans le niveau
	* \return  la liste d'ennemis
	*/
	const std::vector<Enemy> & getEnemies() const;

	/*!
	* \brief  met � jour le sprite de l'ennemi et gere l'animation accelere ou ralenti les fps
	* \param fpsCount fps � incr�menter
	* \param fpsSpeed la vitesse des fps
	* \param switchFps valeur deintervenat dans la condition pour le changement d'image
	* \param time timer en secondee.
	*/
	void manageEnemi(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);

	/*!
	* \brief lance le thread pour chaque ennemi du jeu
	*/
	void startMovingEnemies();


	/*!
	* \brief  permet au joueur de tirer en ligne droite dans la direction vers laquelle il se tourne
	* le tir ne traverse pas les obstacles
	* \param idPlayer l'identifiant du joueur qui tire.
	*/
	void shoot(int idPlayer);

	/*!
	* \brief  permet au joueur de taper une case devant lui
	* \param idPlayer l'identifiant du joueur qui tape.
	*/
	void slice(int idPlayer);

	/*!
	* \brief �tabli une liste de position qu'auront les balles qui sont tir�es 
	* (� savoir, une par case dans la direction dans laquelle on regarde)
	* \param idPlayer l'identifiant du joueur qui tire.
	* \return  la liste de position des balles qui constitue la trajectoire du tir.
	*/
	std::vector<std::pair<float, float>> trajectoireBalle(int idPlayer) const;

	/*!
	* \brief g�re l'enchainement du niveau prochain, recharger les ennemis auguementer leurs pv, etc...
	*/
	void nextLevel();

	/*!
	* \brief v�rifie si tout les ennemis du niveau sont morts
	* \return vrai si tout les ennemis sont morts
	*/
	bool allEnemiesIsDead() const;

	/*!
	* \brief  enl�ve des pv au joueur
	* \param i l'identifiant du joueur qui perd des pv.
	*/
	void removePvOfPlayer(unsigned i);

	/*!
	* \brief  met � jour la barre de vie graphique du joueur (pour une eventuelle impl�mentation future)
	* \param i l'identifiant du joueur qui a sa barre de vie mise � jour.
	* \param rce le rectangle shape repr�sentant la barre de vie du joueur.
	*/
	void setLifeBarOfPlayer(unsigned i, sf::RectangleShape rce);


	/*!
	* \brief donne le nombre obstacles pr�sent dans le niveau
	* \return  le nombre obstacles pr�sent dans le niveau
	*/
	inline unsigned getNbObstacles() const;

	/*!
	* \brief donne l'obstacles correspondant � l'identifiant donn�
	* \param i l'identifiant de l'obstacle que l'on veut retourner
	* \return  l'obstacles identifi� par i
	*/
	inline sf::RectangleShape getObstacle(unsigned i) const;

	/*!
	* \brief met � jour la position du sprite du player
	* \param i l'identifiant du joueur dont on veut mettre le sprite � jour
	*/
	inline void setPositionCharacter(unsigned i);

	/*!
	* \brief met � jour la position du sprite du player
	* \param i l'identifiant du joueur dont on veut mettre le sprite � jour suivant sa direction
	* \param direction la direction vers laquelle le joueur regarde.
	*/
	inline void setAnimYCharacter(unsigned i, Direction direction);

	/*!
	* \brief met l'�tat du joueur en mouvement
	* \param i l'identifiant du joueur qui se met en mouvement
	*/
	inline void setStateCharacter(unsigned i);

	/*!
	* \brief indique � l'ennemi i que l'�tat du joueur est en mouvement ou pas
	* \param i l'identifiant de l'ennemi � avertir
	* \param isMoving l'�tat du joueur
	*/
	inline void setEnemyPlayerMoving(int i, bool isMoving);

	/*!
	* \brief met � jour la texture de l'ennemi en la mettant � sa texture initiale
	* \param i l'identifiant de l'ennemi dont il faut mettre la texture � jour
	*/
	inline void setEnemyHitTextureDepart(int i);

	/*!
	* \brief met tout les joueurs dans l'�tat "static"
	*/
	inline void stateInitializerCharacters();

	/*!
	* \brief termine le jeu.
	*/
	inline void finishGame();

	/*!
	* \brief  met � jour le sprite du joueur et gere l'animation accelere ou ralenti les fps
	* \param fpsCount fps � incr�menter
	* \param fpsSpeed la vitesse des fps
	* \param switchFps valeur deintervenat dans la condition pour le changement d'image
	* \param time timer en seconde.
	*/
	inline void managePlayer(unsigned i, float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);

	/*!
	* \brief retourne la map de jeu
	* \return  la map dans laquelle se d�roule le jeu
	*/
	inline Arena getArena() const;

	/*!
	* \brief retourne la barre de vie du joueur
	* \return  la barre de vie du joueur
	*/
	inline const  sf::RectangleShape & getlifebarre() const;

	/*!
	* \brief indique si un ennemi peut ex�cuter son brain ou pas (si un autre ennemi est d�ja occup� � le faire)
	* \return  vrai si l'ennemi peut ex�cuter son brain
	*/
	inline bool isBrainLocked()const;

	/*!
	* \brief autorise un ennemi � ex�cuter son brain ou pas selon la valeur de lock
	* \param lock est � vrai si l'ennemi peut ex�cuter son brain.
	*/
	inline void setBrainLock(bool lock);

	/*!
	* \brief ajoute un joueur dans le jeu
	* \param posX l'abcisse de la position du joueur
	* \param posY l'ordonn�e de la position du joueur
	* \param pv le nombre de pv du joueur au d�part.
	*/
	inline void addPlayer(float posX, float posY, int pv = 3);
	/*!
	* \brief guetter retournant la liste des joueurs.
	* \return la liste des joueurs.
	*/
	inline const std::vector<Character> &  getPlayers() const;


};

const std::vector<Character> &  Game::getPlayers() const {
	return players_;
}

void Game::addPlayer(float posX, float posY, int pv)
{
	players_.push_back(Heroes(Position(posX, posY), pv, players_.size()));
}

unsigned Game::getNbObstacles() const
{
	return arena_.getNbObstacles();
}

sf::RectangleShape Game::getObstacle(unsigned i) const
{
	return arena_.getObstacle(i);
}

void Game::setPositionCharacter(unsigned i) {
	players_.at(i).setPositionSprite((players_.at(i).getHitbox().getPosition()));
}


void Game::setAnimYCharacter(unsigned i, Direction direction) {
	players_.at(i).setAnimY(direction);
}

void Game::setStateCharacter(unsigned i) {
	players_.at(i).setState(Moving);
}
void Game::stateInitializerCharacters() {
	for (unsigned i = 0; i < players_.size(); i++) {
		players_.at(i).setState(Idle);
	}
}

void Game::managePlayer(unsigned i, float fpsCount, float fpsSpeed, float switchFps, sf::Clock time) {
	players_.at(i).manageSprite(fpsCount, fpsSpeed, switchFps, time);
}

void Game::finishGame() {
	gameFinish = true;
}
Arena Game::getArena() const {
	return arena_;
}

const sf::RectangleShape & Game::getlifebarre() const {
	return	players_.at(0).getlifebar();
}

bool Game::isBrainLocked()const {
	return brainLock;
}
void Game::setBrainLock(bool lock) {
	brainLock = lock;
}


void Game::setEnemyPlayerMoving(int i, bool isMoving) {
	enemies_.at(i).setPlayerMoving(isMoving);
}

void Game::setEnemyHitTextureDepart(int i)
{
	if (!enemies_.empty()) {
		enemies_.at(i).setHitTextureDepart();
	}

}

