#include <SFML\Graphics.hpp>
#include "Game.h"
#include <iostream>

using namespace sf;




int main()
{
	const int width = 640;
	const int height = 480;

	Game game = Game(width, height);

	game.addPlayer(10, 10);
	game.addPlayer(250, 250);

	VideoMode videoMode(width, height);
	RenderWindow window(videoMode, "Rectangle Collision");	

	sf::Texture perso;
	if (!perso.loadFromFile("player.png")) {
		std::cout << "error loading image" << std::endl;
	}
	
	sf::Texture tex = game.getPlayers().at(0).getTextureChar();
	sf::Sprite sprit;
	sprit.setScale(sf::Vector2f(0.6, 0.6));
	sprit.setTexture(tex);

	sf::Texture tex2 = game.getPlayers().at(1).getTextureChar();
	sf::Sprite sprit2;
	sprit2.setScale(sf::Vector2f(0.6, 0.6));
	sprit2.setTexture(tex2);


	while (window.isOpen())
	{
		window.clear(Color::White);
		//window.draw(rtexture);

		
		window.draw(sprit);
		window.draw(sprit2);
		/*RectangleShape texture2 = game.getHitBoxChar(1);
		texture2.setTexture(&perso);
		sf::Texture tex2 = game.getPlayers().at(1).getTextureChar();
		sf::Sprite sprit2;
		sprit.setTexture(tex2);
		window.draw(sprit2);		*/
		for (unsigned i = 0; i < game.getNbPlayers(); i++) {
			//RectangleShape texture1 = game.getHitBoxChar(i);
			////texture1.setSize(sf::Vector2f(40, 40));
			//texture1.setTexture(&perso);
			//window.draw(texture1);
			
		}
		
		for (unsigned i = 0; i < game.getNbObstacles(); i++) {
			window.draw(game.getObstacle(i));
		}

		window.display();

		Event event;
		
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) ||
				((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
				window.close();

		}	
		
		if (event.type == Event::KeyPressed){
			float xMov = 0, yMov = 0, xMov2 = 0, yMov2 = 0;
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				yMov -= 0.1;
				
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				yMov += 0.1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				xMov -= 0.1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				xMov += 0.1;
			}
			if (Keyboard::isKeyPressed(Keyboard::F1)) {
				yMov2 -= 0.1;
			}
			if (Keyboard::isKeyPressed(Keyboard::F2)) {
				yMov2 += 0.1;
			}
			if (Keyboard::isKeyPressed(Keyboard::F3)) {
				xMov2 -= 0.1;
			}
			if (Keyboard::isKeyPressed(Keyboard::F4)) {
				xMov2 += 0.1;
			}

			if (!game.hasCollision(0, xMov, yMov)) {
				game.move(0, xMov, yMov);
				sprit.setPosition(game.getHitBoxChar(0).getPosition());
			}
			if (!game.hasCollision(1, xMov2, yMov2)) {
				game.move(1, xMov2, yMov2);
				sprit2.setPosition(game.getHitBoxChar(1).getPosition());
			}

			
		}

		

	

	}
	return EXIT_SUCCESS;
}