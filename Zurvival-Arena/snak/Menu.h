#pragma once

#include <SFML\Graphics.hpp>


class Menu {
public:
	Menu(float width, float height);

	void draws(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int getPressedItem() { return selectedItemIndex; }
	
	//sf::Sprite background;
	sf::RenderWindow window;
	inline sf::Text getMenu(int id) const;
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[4];
	sf::Texture texture;
	sf::Sprite background;



};

sf::Text Menu::getMenu(int id) const {

	return menu[id];
}