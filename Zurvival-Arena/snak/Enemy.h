#pragma once
#include "Character.h"

class Enemy : public Character {
private:
	struct Node {
		sf::Vector2f parent;
		sf::Vector2f position;
		unsigned gValue;
		unsigned hValue;
		unsigned fValue;
	};

	std::vector<Node> nodeList;
public:
	Enemy(Position position, int pv);
	void uptadeSpritePosition();
	void loadNodeList();

};