#pragma once
#include "Position.h"
#include "Direction.h"
class HitBox {



private:
	Position heightRight_;
	Position downLeft_;
	
public:
	inline HitBox();
	inline HitBox(Position downLeft,Position heightRight);
	
	bool overlaps(HitBox hb);
	inline  Position getHR() const;
	inline Position getDL()const;
	 void move(Direction::dir direction); 


};

HitBox::HitBox(Position downLeft, Position heightRight) :downLeft_(downLeft), heightRight_(heightRight) {

}

Position HitBox::getHR() const {
	return heightRight_;
 }
Position HitBox::getDL()const  {
	return downLeft_;
 }


