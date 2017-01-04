#include "Menu.h"
#include "SFML\Graphics.hpp"
#include <iostream>
Menu::Menu(float width, float height)

{

	nbMenu = 2;
	if (!font.loadFromFile("arial.ttf")) {
	
	}
	
	menu[0].setFont(font);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width -580, height -580));
	menu[0].setCharacterSize(40);
	menu[0].setRotation(10);
	menu[0].setOutlineThickness(20);
	
	
	
	
	menu[1].setFont(font);
	menu[1].setString("Quitter");
	menu[1].setPosition(sf::Vector2f(width - 580, height-420));
	menu[1].setCharacterSize(15);





	menu[2].setFont(font);
	menu[2].setString("1 Player");
	menu[2].setPosition(sf::Vector2f(width - 580, height - 500));
	menu[2].setCharacterSize(15);

	menu[3].setFont(font);
	menu[3].setString("2 Player");
	menu[3].setPosition(sf::Vector2f(width - 500, height - 500));
	menu[3].setCharacterSize(15);

	menu[4].setFont(font);
	menu[4].setString("Zurvival Arena");
	menu[4].setPosition(sf::Vector2f(width - 190, height - 600));
	menu[4].setCharacterSize(50);

	menu[0].setOutlineThickness(10);

	selectedItemIndex = 0;
}

void Menu::draws(sf::RenderWindow &window)

{
	
	
	texture.loadFromFile("a.jpg");
	sf::Sprite background(texture);
	window.draw(background);
	for (int i = 0; i <3; i++)
	{
		
		window.draw(menu[i]);
		
	}
}

void Menu::MoveUp()
{
	
	if (selectedItemIndex -1 >= 0) {
		menu[selectedItemIndex].setCharacterSize(15);
		menu[selectedItemIndex].setRotation(0);
		menu[selectedItemIndex].setOutlineThickness(0);
		selectedItemIndex--;
		menu[selectedItemIndex].setCharacterSize(40);
		menu[selectedItemIndex].setRotation(10);
		menu[selectedItemIndex].setOutlineThickness(20);
	}
}

void Menu::MoveDown()
{
	
	if (selectedItemIndex + 1 < nbMenu) {
		menu[selectedItemIndex].setCharacterSize(15);
		menu[selectedItemIndex].setRotation(0);
		menu[selectedItemIndex].setOutlineThickness(0);
		selectedItemIndex++;
		menu[selectedItemIndex].setCharacterSize(40);
		menu[selectedItemIndex].setRotation(10);
		menu[selectedItemIndex].setOutlineThickness(20);
	}
}