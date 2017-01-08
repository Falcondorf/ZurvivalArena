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
*\brief Class qui gère le déroulement de la partie, les interactions entre joueurs et ennemis.
*\file Game.h
*\author Aynaou Dupont Fakir Bauwens
*/
class Game {
private:
	/*!
	*\brief Contient le nombre de point de vie pour les ennemis d'un niveau spécifique.
	*/
	std::vector<unsigned> pvForLevel;
	/*!
	*\brief l'identifiant du niveau.
	*/
	unsigned idLevel = 0;
	/*!
	*\brief verrou servant à empecher que plusieurs ennemi fassent leur brain en meme temps.
	*/
	bool brainLock = false;
	/*!
	*\brief le nombre d'ennemi pour le niveau courant.
	*/
	unsigned nbEnemies = 0; // à suppr
							/*!
							*\brief La carte dans laquelle se déroule la partie. Elle contient des obstacles.
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
	*\brief booléen indiquant si le jeu est fini.
	*/
	bool gameFinish = false;
public:

	/*!
	* \brief Permet de savoir si le jeu est terminé.
	* \return vrai si le jeu est terminé.
	*/
	bool isFinishGame() const;


	/*!
	* \brief constructeur du jeu prenant les dimension du jeu en parametre.
	* \param width la largeur de la carte.
	* \param height la hauteur de la carte.
	*/
	Game(unsigned width, unsigned height);

	/*!
	* \brief Permet de savoir si un joueur est en collision avec un obstacle ou un ennemi (des pv seront retiré si il se trouve sur une case ennemi).
	* \param idPlayer l'identifiant du joueur à vérifier
	* \param movex la position x vers laquelle le joueur veux se déplacer (qui est à vérifier)
	* \param movey la position y vers laquelle le joueur veux se déplacer (qui est à vérifier)
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
	* \param idplayer l'identifiant du joueur à déplacer.
	* \param xMove le x de la position vers laquelle déplacer l'ennemi.
	* \param yMove le y de la position vers laquelle déplacer l'ennemi.
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
	* \param posY l'ordonnée de la position de l'ennemi
	* \param pv le nombre de pv de l'ennemi au départ.
	*/
	void addEnemy(float posX, float posY, int pv = 1);

	/*!
	* \brief la liste d'ennemis présent dans le niveau
	* \return  la liste d'ennemis
	*/
	const std::vector<Enemy> & getEnemies() const;

	/*!
	* \brief  met à jour le sprite de l'ennemi et gere l'animation accelere ou ralenti les fps
	* \param fpsCount fps à incrémenter
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
	* \brief établi une liste de position qu'auront les balles qui sont tirées 
	* (à savoir, une par case dans la direction dans laquelle on regarde)
	* \param idPlayer l'identifiant du joueur qui tire.
	* \return  la liste de position des balles qui constitue la trajectoire du tir.
	*/
	std::vector<std::pair<float, float>> trajectoireBalle(int idPlayer) const;

	/*!
	* \brief gère l'enchainement du niveau prochain, recharger les ennemis auguementer leurs pv, etc...
	*/
	void nextLevel();

	/*!
	* \brief vérifie si tout les ennemis du niveau sont morts
	* \return vrai si tout les ennemis sont morts
	*/
	bool allEnemiesIsDead() const;

	/*!
	* \brief  enlève des pv au joueur
	* \param i l'identifiant du joueur qui perd des pv.
	*/
	void removePvOfPlayer(unsigned i);

	/*!
	* \brief  met à jour la barre de vie graphique du joueur (pour une eventuelle implémentation future)
	* \param i l'identifiant du joueur qui a sa barre de vie mise à jour.
	* \param rce le rectangle shape représentant la barre de vie du joueur.
	*/
	void setLifeBarOfPlayer(unsigned i, sf::RectangleShape rce);


	/*!
	* \brief donne le nombre obstacles présent dans le niveau
	* \return  le nombre obstacles présent dans le niveau
	*/
	inline unsigned getNbObstacles() const;

	/*!
	* \brief donne l'obstacles correspondant à l'identifiant donné
	* \param i l'identifiant de l'obstacle que l'on veut retourner
	* \return  l'obstacles identifié par i
	*/
	inline sf::RectangleShape getObstacle(unsigned i) const;

	/*!
	* \brief met à jour la position du sprite du player
	* \param i l'identifiant du joueur dont on veut mettre le sprite à jour
	*/
	inline void setPositionCharacter(unsigned i);

	/*!
	* \brief met à jour la position du sprite du player
	* \param i l'identifiant du joueur dont on veut mettre le sprite à jour suivant sa direction
	* \param direction la direction vers laquelle le joueur regarde.
	*/
	inline void setAnimYCharacter(unsigned i, Direction direction);

	/*!
	* \brief met l'état du joueur en mouvement
	* \param i l'identifiant du joueur qui se met en mouvement
	*/
	inline void setStateCharacter(unsigned i);

	/*!
	* \brief indique à l'ennemi i que l'état du joueur est en mouvement ou pas
	* \param i l'identifiant de l'ennemi à avertir
	* \param isMoving l'état du joueur
	*/
	inline void setEnemyPlayerMoving(int i, bool isMoving);

	/*!
	* \brief met à jour la texture de l'ennemi en la mettant à sa texture initiale
	* \param i l'identifiant de l'ennemi dont il faut mettre la texture à jour
	*/
	inline void setEnemyHitTextureDepart(int i);

	/*!
	* \brief met tout les joueurs dans l'état "static"
	*/
	inline void stateInitializerCharacters();

	/*!
	* \brief termine le jeu.
	*/
	inline void finishGame();

	/*!
	* \brief  met à jour le sprite du joueur et gere l'animation accelere ou ralenti les fps
	* \param fpsCount fps à incrémenter
	* \param fpsSpeed la vitesse des fps
	* \param switchFps valeur deintervenat dans la condition pour le changement d'image
	* \param time timer en seconde.
	*/
	inline void managePlayer(unsigned i, float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);

	/*!
	* \brief retourne la map de jeu
	* \return  la map dans laquelle se déroule le jeu
	*/
	inline Arena getArena() const;

	/*!
	* \brief retourne la barre de vie du joueur
	* \return  la barre de vie du joueur
	*/
	inline const  sf::RectangleShape & getlifebarre() const;

	/*!
	* \brief indique si un ennemi peut exécuter son brain ou pas (si un autre ennemi est déja occupé à le faire)
	* \return  vrai si l'ennemi peut exécuter son brain
	*/
	inline bool isBrainLocked()const;

	/*!
	* \brief autorise un ennemi à exécuter son brain ou pas selon la valeur de lock
	* \param lock est à vrai si l'ennemi peut exécuter son brain.
	*/
	inline void setBrainLock(bool lock);

	/*!
	* \brief ajoute un joueur dans le jeu
	* \param posX l'abcisse de la position du joueur
	* \param posY l'ordonnée de la position du joueur
	* \param pv le nombre de pv du joueur au départ.
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

