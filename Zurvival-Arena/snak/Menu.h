#pragma once

#include <SFML\Graphics.hpp>


class Menu {
public:
	Menu(float width, float height);

	void draws(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int getPressedItem() { return selectedItemIndex; }
	inline void changernbMenu(int nbmenu);
	//sf::Sprite background;
	sf::RenderWindow window;
	inline sf::Text getMenu(int id) const;
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[5];
	sf::Texture texture;
	sf::Sprite background;
	int nbMenu;
};

sf::Text Menu::getMenu(int id) const {

	return menu[id];
}
inline void Menu::changernbMenu(int nbmenu) {
	nbMenu = nbmenu;
}