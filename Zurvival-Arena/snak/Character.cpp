#include "Character.h"

using namespace sf;

void Character::move(float f1, float f2) {
	hitbox_.move(f1, f2);
}

void Character::setPosition(float f1, float f2) {
	hitbox_.setPosition(f1, f2);
}

void Character::setFillColor(Color c) {
	hitbox_.setFillColor(c);
}
void Character::setOutlineColor(Color c) {
	hitbox_.setOutlineColor(c);
}
void Character::setOutlineThickness(int i) {
	hitbox_.setOutlineThickness(i);
}

void Character::setSize(float f1, float f2) {
	hitbox_.setSize(Vector2f(f1, f2));
}
