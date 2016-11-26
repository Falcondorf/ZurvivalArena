#include "stdafx.h"
#include "HitBox.h"
#include "Direction.h"

bool HitBox::overlaps(HitBox hb) {

	return	(downLeft_.getX() < hb.getHR().getX()
		&& heightRight_.getX() > hb.getDL().getX()
		&& downLeft_.getY() < hb.getHR().getY()
		&& heightRight_.getY() > hb.getDL().getY());

}

void HitBox::move(Direction::dir direction) { 
	switch (direction) {
	case Direction::dir::up:  
		downLeft_.setY(downLeft_.getY() + 1);
		heightRight_.setY(heightRight_.getY() + 1);

		break;
	case Direction::dir::down:
		downLeft_.setY(downLeft_.getY() - 1);
		heightRight_.setY(heightRight_.getY() - 1);

		break;

	case Direction::dir::left:
		downLeft_.setX(downLeft_.getX() -1);
		heightRight_.setX(heightRight_.getX() -1);

		break;
	case Direction::dir::right:

		downLeft_.setX(downLeft_.getX() + 1);
		heightRight_.setX(heightRight_.getX() + 1);


		break;
	

	}


}