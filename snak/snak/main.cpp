#include <SFML\Graphics.hpp>

#include "Character.h"
#include "Arena.h"
#include "Game.h"
using namespace sf;

int main()
{
	const int width = 640;
	const int height = 480;
	
	Character player2(Position(250, 250), 3);
	Character player(Position(10,10), 3);
	std::vector<Character> players;
	players.push_back(player);
	players.push_back(player2);

	Game game = Game(width, height,players);

	const int borderSize = 30;

	VideoMode videoMode(width, height);
	RenderWindow window(videoMode, "Rectangle Collision");

	RectangleShape top;
	RectangleShape left;
	RectangleShape right;
	RectangleShape bottom;
	
	
	
	RectangleShape obstacle;
	obstacle.setPosition(width / 3, height / 2);
	obstacle.setSize(Vector2f(200, 20));
	obstacle.setFillColor(Color::Red);
	obstacle.setOutlineColor(Color::Yellow);
	obstacle.setOutlineThickness(1);




	Arena myArena(640, 480);

	

	while (window.isOpen())
	{
		window.clear(Color::White);
		
		for (int i = 0; i < game.getPlayers().size(); i++) {
			window.draw(game.getPlayers().at(i).getHitbox());
		}
		
		for (int i = 0; i < myArena.getObstacles().size(); i++) {
			window.draw(myArena.getObstacles()[i]);
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