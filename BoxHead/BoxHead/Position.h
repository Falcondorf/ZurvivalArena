#pragma once

class Position
{
private:
	float x_;/*!< L'abscisse de la position. */
	float y_;/*!< L'ordonnée de la position */
public:
	inline Position();

	inline Position(float x, float y);


	inline float getX() const;

	inline float getY() const;

	inline void setX(float x);

	inline void setY(float y);


};

Position::Position() :x_(0), y_(0){}

Position::Position(float x, float y) :x_(x), y_(y) {}

float Position::getX() const {
	return this->x_;
}

float Position::getY() const {
	return this->y_;
}

void Position::setX(float x) {
	this->x_ = x;
}
void Position::setY(float y) {
	this->y_ = y;
}