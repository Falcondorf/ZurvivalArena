#pragma once

#include <SFML\Graphics.hpp>


/*!
* \brief Classe représentant le menu de demarage du jeu.
*\file menu.h
*\author Aynaou Dupont Fakir Bauwens Temsamani
*/
class Menu {
public:
	/*!
	* \brief Constructeur du Menu du jeu.
	* \param width la longeur du menu.
	* \param height la largeur du menu.
	*/

	Menu(float width, float height);
	/*!
	* \brief Dessine dans la fentre du jeu.
	*\param window La fenêtre principal.
	*/
	void draws(sf::RenderWindow &window);
	/*!
	* \brief Permet de parcourir le menu vers le haut.
	*/
	void MoveUp();
	/*!
	* \brief Permet de parcourir le menu vers le bas.
	*/
	void MoveDown();
	/*!
	* \brief Permet de parcourir le menu vers le haut.
	* \return le numero d'index selectionné.
	*/
	int getPressedItem() { return selectedItemIndex; }
	/*!
	* \brief Permet de changer le nom d'element à parcourir dans le menu.
	* \param nbmenu le nombre d'element dans le menu.
	*/
	inline void changernbMenu(int nbmenu);

	sf::RenderWindow window;
	/*!
	* \brief Geteur d'un element du menu.
	* \param id le nombre d'element dans le menu.
	*/
	inline sf::Text getMenu(int id) const;
private:
	int selectedItemIndex;/*!< L'index selectionner dans le menu */
	sf::Font font;/*!< la police utilisée pour les ecritures du menu */
	sf::Text menu[5];/*!< le tableau de titre du menu */
	sf::Texture texture;/*!< La texture sur lequel on va appliquer l'image du fond d'ecran. */
	sf::Sprite background;/*!<l'image du fond d'ecran. */
	int nbMenu;/*!< le nombre d'element dans le menu */
};

sf::Text Menu::getMenu(int id) const {

	return menu[id];
}
inline void Menu::changernbMenu(int nbmenu) {
	nbMenu = nbmenu;
}