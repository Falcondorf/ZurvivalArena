#include <SFML\Graphics.hpp>
#include "Character.h"

using namespace sf;

bool intersects(const RectangleShape & rect1, const RectangleShape & rect2)
{
	FloatRect r1 = rect1.getGlobalBounds();
	FloatRect r2 = rect2.getGlobalBounds();
	return r1.intersects(r2);
}

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

	Character player;
	player.setPosition(width / 4, height / 4);
	player.setSize(20, 20);
	player.setFillColor(Color::Red);
	player.setOutlineColor(Color::Yellow);
	player.setOutlineThickness(1);



	while (window.isOpen())
	{
		window.clear(Color::White);
		window.draw(top);
		window.draw(bottom);
		window.draw(left);
		window.draw(right);
		window.draw(player.getHitbox());
		window.draw(obstacle);
		window.display();

		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) ||
				((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
				window.close();

		}


		if (event.type == Event::KeyPressed){
			float xMov = 0, yMov = 0;
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

			if (!intersects(player.getHitbox(),obstacle)) {
				player.move(xMov, yMov);
			}else {
				player.setPosition(player.getHitbox().getPosition().x -xMov*10, player.getHitbox().getPosition().y - yMov*10);
			}
			
		}



		//}


	//	ball.move(ballSpeed.x, ballSpeed.y);

	}
	return EXIT_SUCCESS;
}