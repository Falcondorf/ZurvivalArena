#include <SFML\Graphics.hpp>
#include "game.h"
#include <iostream>
#include <algorithm>
#include "Menu.h"
using namespace sf;
using namespace std;
int main()
{
	bool startgame = false;
	pair<int, int> lastPosition;
	const int width = 660;
	const int height = 660;
	bool afficher = false;
	int nombreJoueur =0;
	try {
		Game game = Game(width, height);
		/*game.addPlayer(330, 30);
		game.addPlayer(400, 330);*/
		game.addEnemy(210, 240, 1);
		game.addEnemy(300, 410, 2);
		game.addEnemy(180, 120, 3);


		lastPosition = make_pair(11, 2);
		/*game.addEnemy(180, 120);*/
		//	game.getArena().printTiles();
		//game.brain(game.getEnemies()[0]);
		VideoMode videoMode(width, height);
		RenderWindow window(videoMode, "Zurvival Arena");
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
							/*window.setVisible(true);
							game.startMovingEnemies();
							window3.close();*/
							afficher = true;
							menu2.changernbMenu(4);

							break;
						case 1:

							window3.close();
							window.close();
							break;
						case 2:
							nombreJoueur = 1;
							window.setVisible(true);

							window3.close();
							cout << "1joueur" << endl;

							break;
						case 3:
							nombreJoueur = 2;
							window.setVisible(true);

							window3.close();
							cout << "2joueur" << endl;

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
			for (int i = 0; i < 5; i++)
			{
				if ((i != 2 && i != 3) || afficher) {

					window3.draw(menu2.getMenu(i));
				}

			}
			window3.display();
		}

		sf::Texture texture2;
		texture2.loadFromFile("z.png");
		sf::Sprite background3(texture2);

		if (nombreJoueur == 1) {
			game.addPlayer(330, 30);
			game.startMovingEnemies();
		}
		else {
			game.addPlayer(330, 30);
			game.addPlayer(400, 330);
			game.startMovingEnemies();

		}
		unsigned nbEnemyDead = 0;
		
		
		sf::RenderWindow window4(sf::VideoMode(800, 450), "Zurvival Arena");
		window4.setVisible(false);
		
		
		while (window.isOpen())
		{

			if (nombreJoueur == 1) {
				
				if (game.getPlayers().at(0).getPv() < 1 ) {


					game.finishGame();
					window4.setVisible(true);
					sf::Texture texture;
					texture.loadFromFile("fin.jpg");
					sf::Sprite background(texture);
					window4.draw(background);

					window4.display();

				}
			}


			//window.display();
			window.clear();

			window.draw(background3);
			if (game.allEnemiesIsDead()) {
				game.nextLevel();
				//game.startMovingEnemies();
			}
			//gestion wave
			//if (game.getEnemies().size() == 0 && game.getRemainingEnemies() == 0) { //En fin de vague plus d'enemis
			//	game.nextWave();
			//	if (game.getRemainingEnemies() > 4) {
			//		for (int i = 0; i < 4; i++) {
			//			game.addEnemy(210, 240, game.getWave()); //faire un switching de position par variable
			//		}
			//	}
			//	else {
			//		int remainingEnemies = game.getRemainingEnemies();
			//		for (int i = 0; i < remainingEnemies; i++) {
			//			game.addEnemy(210+30*(i+1)  , 240 , game.getWave()); //faire un switching de position par variable
			//		}
			//	}
			//	game.startMovingEnemies();
			//}
			//cout << "Taille liste = " << game.getEnemies().size() << endl;


			for (unsigned i = 0; i < game.getEnemies().size(); i++) {

				if (game.getEnemies().at(i).getPv() > 0) {
					window.draw(*(game.getEnemies().at(i).getSprite()));
				}


			}

			// window.draw((game.getPlayers().at(0).getHitbox()));
			//window.draw((game.getlifebarre()));

			game.stateInitializerCharacters();
			for (int i = 0; i < nombreJoueur; i++) {
				window.draw(*(game.getPlayers().at(i).getSprite()));

			}

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
					yMov -= 0.4;
					game.setAnimYCharacter(0, Up);

				}
				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					game.setStateCharacter(0);
					yMov += 0.4;
					game.setAnimYCharacter(0, Down);
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					game.setStateCharacter(0);
					xMov -= 0.4;
					game.setAnimYCharacter(0, Left);
				}
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					game.setStateCharacter(0);
					xMov += 0.4;
					game.setAnimYCharacter(0, Right);

				}
				if (Keyboard::isKeyPressed(Keyboard::RControl)) {
					game.shoot(0);
					std::vector<pair<float, float>> vec;
					vec = game.trajectoireBalle(0);
					CircleShape rs(5, 20);
					rs.setPosition(sf::Vector2f((vec.at(0).first) * 30, (vec.at(0).second) * 30));
					rs.setFillColor(sf::Color::Magenta);
					for (int i = 0; i < vec.size(); i++) {
						rs.setPosition(vec.at(i).first * 30, vec.at(i).second * 30);
						window.draw(rs);
						window.display();
					}

					game.setEnemyHitTextureDepart(0);
				}

				if (Keyboard::isKeyPressed(Keyboard::RAlt)) {
					game.slice(0);
				}
				if (nombreJoueur == 2) {


					if (Keyboard::isKeyPressed(Keyboard::F1)) {
						game.setStateCharacter(1);
						yMov2 -= 0.1;
						game.setAnimYCharacter(1, Up);
					}
					if (Keyboard::isKeyPressed(Keyboard::F2)) {
						game.setStateCharacter(1);
						yMov2 += 0.1;
						game.setAnimYCharacter(1, Down);
					}
					if (Keyboard::isKeyPressed(Keyboard::F3)) {
						game.setStateCharacter(1);
						xMov2 -= 0.1;
						game.setAnimYCharacter(1, Left);
					}
					if (Keyboard::isKeyPressed(Keyboard::F4)) {
						game.setStateCharacter(1);
						xMov2 += 0.1;
						game.setAnimYCharacter(1, Right);
					}
					if (Keyboard::isKeyPressed(Keyboard::F5)) {

						game.shoot(1);
						std::vector<pair<float, float>> vec;
						vec = game.trajectoireBalle(1);
						CircleShape rs(5, 20);
						rs.setPosition(sf::Vector2f((vec.at(0).first) * 30, (vec.at(0).second) * 30));
						rs.setFillColor(sf::Color::Magenta);
						for (int i = 0; i < vec.size(); i++) {
							rs.setPosition(vec.at(i).first * 30, vec.at(i).second * 30);
							window.draw(rs);
							window.display();
						}

						game.setEnemyHitTextureDepart(0);

					}

					if (Keyboard::isKeyPressed(Keyboard::F6)) {
						game.slice(1);
					}
				}

				if (!game.hasCollision(0, xMov, yMov)) {
					game.move(0, xMov, yMov);
					game.setPositionCharacter(0);

					for (int i = 0; i < game.getEnemies().size(); i++) {
						game.setEnemyPlayerMoving(i, true);
					}
					game.manageGame(0, fpsCount, fpsSpeed, switchFps, time);
				}
				if (nombreJoueur > 1 && !game.hasCollision(1, xMov2, yMov2)) {
					game.move(1, xMov2, yMov2);
					game.setPositionCharacter(1);
					//game.getEnemies().at(1).setPlayerMoving(true);
					for (int i = 0; i < game.getEnemies().size(); i++) {
						game.setEnemyPlayerMoving(i, true);
					}
					game.manageGame(1, fpsCount, fpsSpeed, switchFps, time);
				}
			}
			game.manageEnemi(fpsCount, fpsSpeed, switchFps, time);

			//game.removeDeadEnemies();
			/*while (game.getEnemies().size() < 4 && game.getRemainingEnemies() > 0) {
			game.addEnemy(210, 240, game.getWave());
			}*/
		}
	}
	catch (std::exception const & e) {
		std::cout << e.what();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}