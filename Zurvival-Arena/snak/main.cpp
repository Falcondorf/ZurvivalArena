#include <SFML\Graphics.hpp>
#include "Game.h"
#include <iostream>

using namespace sf;
int main()
{
	const int width = 960;
	const int height = 960;
	try {
		Game game = Game(width, height);

		game.addPlayer(10, 10);
		game.addPlayer(250, 250);
		game.addEnemy(300, 10);
		game.addEnemy(420, 300);

		VideoMode videoMode(width, height);
		RenderWindow window(videoMode, "Rectangle Collision");

		sf::Texture perso;
		if (!perso.loadFromFile("player.png")) {
			std::cout << "error loading image" << std::endl;
		}

		//sf::Texture tex = game.getPlayers().at(0).getTextureChar();
		//sf::Sprite sprit;
		//	sprit.setScale(sf::Vector2f(0.6, 0.6));
		/*sprit.setTexture(tex);*/

		/*sf::Texture tex2 = game.getPlayers().at(1).getTextureChar();
		sf::Sprite sprit2;*/
		//	sprit2.setScale(sf::Vector2f(0.6, 0.6));
		//	sprit2.setTexture(tex2);

		sf::Clock time;

		float fpsCount = 0, switchFps = 0, fpsSpeed = 500;

		/*State state;*/

		game.startMovingEnemies();
		while (window.isOpen())
		{
			window.clear(Color::White);

			/*state = State::Idle;*/
			window.draw(*(game.getEnemies().at(0).getSprite()));
			window.draw(*(game.getEnemies().at(1).getSprite()));
			game.stateInitializerCharacters();
			//sprit.setTextureRect(sf::IntRect(anim.x * 56, anim.y * 85, 56, 85));
			window.draw(*(game.getPlayers().at(0).getSprite()));
			//window.draw(*(game.getPlayers().at(1).getSprite()));
			for (unsigned i = 0; i < game.getNbPlayers(); i++) {


			}

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
					/*state = State::Moving;*/
					game.setStateCharacter(0);
					yMov -= 0.1;
					/*anim.y = Up;*/
					game.setAnimYCharacter(0, Up);

				}
				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					/*state = State::Moving;*/
					game.setStateCharacter(0);
					yMov += 0.1;
					/*anim.y = Down;*/
					game.setAnimYCharacter(0, Down);
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					/*state = State::Moving;*/
					game.setStateCharacter(0);
					xMov -= 0.1;
					/*anim.y = Left;*/
					game.setAnimYCharacter(0, Left);
				}
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					/*state = State::Moving;*/
					game.setStateCharacter(0);
					xMov += 0.1;
					/*anim.y = Right;*/
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
					//sprit.setPosition(game.getHitBoxChar(0).getPosition());
					game.setPositionCharacter(0);
				}
				if (!game.hasCollision(1, xMov2, yMov2)) {
					game.move(1, xMov2, yMov2);
					/*sprit2.setPosition(game.getHitBoxChar(1).getPosition());*/
				}


			}
			if (game.getPlayers().at(0).getState() == State::Moving) {
				game.manageGame(0, fpsCount, fpsSpeed, switchFps, time);
			}
			game.manageEnemi(fpsCount, fpsSpeed, switchFps, time);
			/*if (updateFps) {
			fpsCount += fpsSpeed *time.restart().asSeconds();
			}
			else {
			fpsCount = 0;
			}
			if (fpsCount >= switchFps) {
			anim.x++;
			if (anim.x * 56 >= tex.getSize().x) {
			anim.x = 0;
			}
			}
			sprit.setTextureRect(sf::IntRect(anim.x * 56, anim.y * 85, 56, 85));*/





		}
	}catch (std::exception const & e) {
		std::cout << e.what();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}