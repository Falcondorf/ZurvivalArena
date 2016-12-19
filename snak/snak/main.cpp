#include <SFML\Graphics.hpp>

#include "Character.h"
#include "Arena.h"

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



	top.setPosition(borderSize, 0);
	top.setSize(Vector2f(width - 2 * borderSize, borderSize));

	left.setPosition(0, 0);
	left.setSize(Vector2f(borderSize, height));

	right.setPosition(width - borderSize, 0);
	right.setSize(Vector2f(borderSize, height));

	bottom.setPosition(borderSize, height - borderSize);
	bottom.setSize(Vector2f(width - 2 * borderSize, borderSize));

	top.setFillColor(Color(100, 100, 100));
	top.setOutlineColor(Color::Blue);
	top.setOutlineThickness(3);

	left.setFillColor(Color(100, 100, 100));
	left.setOutlineColor(Color::Blue);
	left.setOutlineThickness(3);

	right.setFillColor(Color(100, 100, 100));
	right.setOutlineColor(Color::Blue);
	right.setOutlineThickness(3);

	bottom.setFillColor(Color(100, 100, 100));
	bottom.setOutlineColor(Color::Blue);
	bottom.setOutlineThickness(3);

	Arena myArena(400, 400);

	Character player;
	player.setPosition(width / 4, height / 4);
	player.setSize(20, 20);
	player.setFillColor(Color::Red);
	player.setOutlineColor(Color::Yellow);
	player.setOutlineThickness(1);

	Character player2;
	player2.setPosition(width / 6, height / 6);
	player2.setSize(20, 20);
	player2.setFillColor(Color::Blue);
	player2.setOutlineColor(Color::Yellow);
	player2.setOutlineThickness(1);



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

			if (!intersects(player2.getHitbox(), obstacle) && !intersects(player2.getHitbox(),top) && !intersects(player2.getHitbox(), bottom) && !intersects(player2.getHitbox(), left) && !intersects(player2.getHitbox(), right)) {
				player2.move(xMov2, yMov2);
			}
		
			else if (intersects(player2.getHitbox(), obstacle)|| intersects(player2.getHitbox(), top) || intersects(player2.getHitbox(), bottom) || intersects(player2.getHitbox(), right) || intersects(player2.getHitbox(), left) ) {
				player2.setPosition(player2.getHitbox().getPosition().x - xMov2 * 10, player2.getHitbox().getPosition().y - yMov2 * 10);
			}
			

			if (!intersects(player.getHitbox(), obstacle) && !intersects(player.getHitbox(), top) && !intersects(player.getHitbox(), bottom) && !intersects(player.getHitbox(), left) && !intersects(player.getHitbox(), right)) {
				player.move(xMov, yMov);
			}else if(intersects(player.getHitbox(), obstacle) || intersects(player.getHitbox(), top) || intersects(player.getHitbox(), bottom) || intersects(player.getHitbox(), right) || intersects(player.getHitbox(), left)){
				player.setPosition(player.getHitbox().getPosition().x -xMov*10, player.getHitbox().getPosition().y - yMov*10);
				
			}
		}

		



		//}


	//	ball.move(ballSpeed.x, ballSpeed.y);

	}
	return EXIT_SUCCESS;
}