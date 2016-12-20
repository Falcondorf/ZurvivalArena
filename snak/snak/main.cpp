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

	while (window.isOpen())
	{
		window.clear(Color::White);
		
		for (unsigned i = 0; i < game.getNbPlayers(); i++) {
			window.draw(game.getHitBoxChar(i));
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
			}
			if (!game.hasCollision(1, xMov2, yMov2)) {
				game.move(1, xMov2, yMov2);
			}

			
		}

		

	

	}
	return EXIT_SUCCESS;
}