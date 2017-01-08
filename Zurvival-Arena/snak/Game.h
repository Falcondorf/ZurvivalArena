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

struct Node {
	sf::Vector2f parent;
	sf::Vector2f position;
	unsigned gValue;
	unsigned hValue;
	unsigned fValue;
};

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
	* \brief  met à jour le sprite et gere l'animation
	* \param fpsCount
	* \param fpsSpeed l'ordonnée de la position a vendre
	* \param switchFps l'ordonnée de la position a vendre
	* \param time l'ordonnée de la position a vendre
	* \return vrai si la case est accessible.
	*/
	void manageEnemi(float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);
	void startMovingEnemies();
	void shoot(int idPlayer);
	void slice(int idPlayer);
	std::vector<std::pair<float, float>> trajectoireBalle(int idPlayer) const;
	void moveBall(std::vector<std::pair<float, float>> vec);
	void nextLevel();
	bool allEnemiesIsDead() const;
	void removePvOfPlayer(unsigned i);
	void setLifeBarOfPlayer(unsigned i, sf::RectangleShape rce);


	/*!
	* \brief la liste d'ennemis présent dans le niveau
	* \return  la liste d'ennemis
	*/
	inline unsigned getNbObstacles() const;
	inline sf::RectangleShape getObstacle(unsigned i) const;
	inline void setPositionCharacter(unsigned i);
	inline void setAnimXCharacter(unsigned i, Direction direction);
	inline void setAnimYCharacter(unsigned i, Direction direction);
	inline void setStateCharacter(unsigned i);
	inline void setEnemyPlayerMoving(int i, bool isMoving);
	inline void setEnemyHitTextureDepart(int i);
	inline void stateInitializerCharacters();
	inline void finishGame();
	inline void manageGame(unsigned i, float fpsCount, float fpsSpeed, float switchFps, sf::Clock time);
	inline Arena getArena() const;
	inline const  sf::RectangleShape & getlifebarre() const;
	inline bool isBrainLocked()const;
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

void Game::setAnimXCharacter(unsigned i, Direction direction) {
	players_.at(i).setAnimX(direction);
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

void Game::manageGame(unsigned i, float fpsCount, float fpsSpeed, float switchFps, sf::Clock time) {
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

