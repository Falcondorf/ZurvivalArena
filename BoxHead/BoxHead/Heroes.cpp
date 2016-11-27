#include "stdafx.h"
#include "Heroes.h"
#include "Position.h"


HitBox  Heroes::hitPerimeter() {
	

	switch (direction_) {
	case Direction::dir::up:
		HitBox hbHit(Position(hbChar_.getDL().getX(),hbChar_.getHR().getY()),Position(hbChar_.getHR().getX(),hbChar_.getHR().getY()+2));
		return hbHit;
		break;
		 //TODO CASE DOWN ? LEFT ? RIGHT ? 

	}
	return HitBox(Position(0,0), Position(0,0));
}