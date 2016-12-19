#include <SFML\Graphics.hpp>

#include "Character.h"
#include "Arena.h"
#include "Game.h"
using namespace sf;

//bool intersects(const RectangleShape & rect1, const RectangleShape & rect2)
//{
//	FloatRect r1 = rect1.getGlobalBounds();
//	FloatRect r2 = rect2.getGlobalBounds();
//	return r1.intersects(r2);
//}




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




	Arena myArena(620, 460);

	

	while (window.isOpen())
	{
		window.clear(Color::White);
		window.draw(player.getHitbox());
		window.draw(player2.getHitbox());
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
				player.move(xMov, yMov);
			}
			if (!game.hasCollision(1, xMov, yMov)) {
				player2.move(xMov2, yMov2);
			}

			//if (!intersects(player2.getHitbox(), obstacle) && !intersects(player2.getHitbox(),top) && !intersects(player2.getHitbox(), bottom) && !intersects(player2.getHitbox(), left) && !intersects(player2.getHitbox(), right)) {
			//	player2.move(xMov2, yMov2);
			//}
		
			//else if (intersects(player2.getHitbox(), obstacle)|| intersects(player2.getHitbox(), top) || intersects(player2.getHitbox(), bottom) || intersects(player2.getHitbox(), right) || intersects(player2.getHitbox(), left) ) {
			//	player2.setPosition(player2.getHitbox().getPosition().x - xMov2 * 10, player2.getHitbox().getPosition().y - yMov2 * 10);
			//}
			//

			//if (!intersects(player.getHitbox(), obstacle) && !intersects(player.getHitbox(), top) && !intersects(player.getHitbox(), bottom) && !intersects(player.getHitbox(), left) && !intersects(player.getHitbox(), right)) {
			//	player.move(xMov, yMov);
			//}else if(intersects(player.getHitbox(), obstacle) || intersects(player.getHitbox(), top) || intersects(player.getHitbox(), bottom) || intersects(player.getHitbox(), right) || intersects(player.getHitbox(), left)){
			//	player.setPosition(player.getHitbox().getPosition().x -xMov*10, player.getHitbox().getPosition().y - yMov*10);
			//	
			//}
		}

		



		//}


	//	ball.move(ballSpeed.x, ballSpeed.y);

	}
	return EXIT_SUCCESS;
}