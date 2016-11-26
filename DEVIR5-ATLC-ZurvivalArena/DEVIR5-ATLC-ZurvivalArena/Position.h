#pragma once

class Position
{
private:
	unsigned x_;/*!< L'abscisse de la position. */
	unsigned y_;/*!< L'ordonnée de la position */
public:
	inline Position();

	inline Position(unsigned x, unsigned y);


	inline unsigned getX() const;

	inline unsigned getY() const;

	inline void setX(unsigned x);

	inline void setY(unsigned y);


};

Position::Position() :x_(0), y_(0){}

Position::Position(unsigned x, unsigned y) :x_(x), y_(y) {}

unsigned Position::getX() const {
	return this->x_;
}

unsigned Position::getY() const {
	return this->y_;
}

void Position::setX(unsigned x) {
	this->x_ = x;
}
void Position::setY(unsigned y) {
	this->y_ = y;
}