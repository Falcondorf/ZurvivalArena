#include <SFML\Graphics.hpp>
#include "Game.h"
#include <iostream>

using namespace sf;
int main()
{
	pair<int, int> lastPosition;
	const int width = 660;
	const int height = 660;
	try {
		Game game = Game(width, height);
		game.addPlayer(330, 30);
		game.addPlayer(250, 250);
		game.addEnemy(210, 240);
		game.addEnemy(420, 300);
		lastPosition = make_pair(11, 2);
		/*game.addEnemy(180, 120);*/
		game.getArena().printTiles();
		//game.brain(game.getEnemies()[0]);
		VideoMode videoMode(width, height);
		RenderWindow window(videoMode, "Rectangle Collision");
		sf::Clock time;
		float fpsCount = 0, switchFps = 0, fpsSpeed = 500;
		//std::vector<Vector2f> p;
		////p=game.brain(1);
		//for (Vector2f b : p) {
		//	std::cout << " X : " << b.x << " Y : " << b.y << std::endl;
		//}
		
		game.startMovingEnemies();

		while (window.isOpen())
		{
			window.clear(Color::White);
			window.draw(game.getEnemies().at(0).getHitbox());
			window.draw(*(game.getEnemies().at(0).getSprite()));
			window.draw(game.getEnemies().at(1).getHitbox());
			window.draw(*(game.getEnemies().at(1).getSprite()));
			//window.draw(*(game.getEnemies().at(2).getSprite()));
			game.stateInitializerCharacters();
			window.draw((game.getPlayers().at(0).getHitbox()));
			window.draw(*(game.getPlayers().at(0).getSprite()));
			/*for (unsigned i = 0; i < game.getNbPlayers(); i++) {
			}*/
			for (unsigned i = 0; i < game.getNbObstacles(); i++) {
				window.draw(game.getObstacle(i));
			}
			window.display();
			Event event;
			while (window.pollEvent(event))
			{
		
				if ((event.type == Event::Closed) ||
					((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))) {
					game.finishGame();
					window.close();
				}
			}

			if (event.type == Event::KeyPressed) {
				float xMov = 0, yMov = 0, xMov2 = 0, yMov2 = 0;
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					game.setStateCharacter(0);
					yMov -= 0.1;
					game.setAnimYCharacter(0, Up);

				}
				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					game.setStateCharacter(0);
					yMov += 0.1;
					game.setAnimYCharacter(0, Down);
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					game.setStateCharacter(0);
					xMov -= 0.1;
					game.setAnimYCharacter(0, Left);
				}
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					game.setStateCharacter(0);
					xMov += 0.1;
					game.setAnimYCharacter(0, Right);

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
					game.setPositionCharacter(0);
				}
				if (!game.hasCollision(1, xMov2, yMov2)) {
					game.move(1, xMov2, yMov2);
				}
				
				game.getEnemies().at(0).setPlayerMoving(true);
			}
			if (game.getPlayers().at(0).getState() == State::Moving) {
				game.manageGame(0, fpsCount, fpsSpeed, switchFps, time);
			}
			game.manageEnemi(fpsCount, fpsSpeed, switchFps, time);
		}
	}catch (std::exception const & e) {
		std::cout << e.what();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}