#include <SFML\Graphics.hpp>
#include "Game.h"
#include <iostream>
#include "Menu.h"
using namespace sf;
int main()
{
	bool startgame = false;
	pair<int, int> lastPosition;
	const int width = 660;
	const int height = 660;
	try {
		Game game = Game(width, height);
		game.addPlayer(330, 30);
		game.addPlayer(250, 250);
		game.addEnemy(210, 240);
		//game.addEnemy(420, 300);
		lastPosition = make_pair(11, 2);
		/*game.addEnemy(180, 120);*/
	//	game.getArena().printTiles();
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

		sf::RenderWindow window3(sf::VideoMode(800, 450), "Zurvival Arena");
		Menu menu2(600, 600);

		window.setVisible(false);



		while (window3.isOpen())
		{
			sf::Event event;


			while (window3.pollEvent(event)) {
				switch (event.type)
				{

				case ::Event::KeyReleased:

					switch (event.key.code) {
					case sf::Keyboard::Up:
						menu2.MoveUp();
						break;
					case sf::Keyboard::Down:
						menu2.MoveDown();
						break;
					case sf::Keyboard::Return:
						switch (menu2.getPressedItem())
						{
						case 0:
							window.setVisible(true);
							game.startMovingEnemies();
							window3.close();
							break;
						case 1:
							break;
						case 2:
							window3.close();
							window.close();

							break;
						default:
							break;
						}
					}
					break;
				case sf::Event::Closed:
					window3.close();
					window.close();

					break;


				}

			}


			sf::Texture texture;

			texture.loadFromFile("a.jpg");
			sf::Sprite background(texture);
			window3.draw(background);
			for (int i = 0; i < 4; i++)
			{
				window3.draw(menu2.getMenu(i));

			}
			window3.display();
		}


		sf::Texture texture2;
		texture2.loadFromFile("z.png");
		sf::Sprite background3(texture2);
		while (window.isOpen())
		{

			//window.display();
			window.clear();


			window.draw(background3);


			//window.draw(game.getEnemies().at(0).getHitbox());
			window.draw(*(game.getEnemies().at(0).getSprite()));
			//window.draw(game.getEnemies().at(1).getHitbox());
			//window.draw(*(game.getEnemies().at(1).getSprite()));
			//window.draw(*(game.getEnemies().at(2).getSprite()));
			game.stateInitializerCharacters();
			// window.draw((game.getPlayers().at(0).getHitbox()));
			window.draw((game.getlifebarre()));
			window.draw(*(game.getPlayers().at(0).getSprite()));
			/*for (unsigned i = 0; i < game.getNbPlayers(); i++) {
			}*/
			for (unsigned i = 0; i < game.getNbObstacles(); i++) {
				window.draw(game.getObstacle(i));
			}
			window.display();
			Event event;
			//cout << "pv joueur : " << game.getPlayers().at(0).getPv() << endl;




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
				if (Keyboard::isKeyPressed(Keyboard::F5)) {
					game.shoot(0);
					std::vector<std::pair<float, float>> vec;
					vec = game.trajectoireBalle(0);

					CircleShape rs(5, 20);


					rs.setPosition(sf::Vector2f((vec.at(0).first) * 30, (vec.at(0).second) * 30));
					rs.setFillColor(sf::Color::Magenta);
					//rs.setSize(sf::Vector2f(5, 5));


					for (int i = 0; i < vec.size(); i++) {
						rs.setPosition(vec.at(i).first * 30, vec.at(i).second * 30);
						window.draw(rs);
						window.display();
					}




					game.getEnemies().at(0).setHitTextureDepart();
				}

				if (Keyboard::isKeyPressed(Keyboard::F6)) {
					game.slice(0);
					cout << game.getEnemies().at(0).getPv() << endl;
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
	}
	catch (std::exception const & e) {
		std::cout << e.what();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}