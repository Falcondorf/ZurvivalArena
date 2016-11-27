#include "stdafx.h"
#include "Heroes.h"
#include "Position.h"


HitBox  Heroes::hitPerimeter() {
	HitBox hb(Position(0, 0), Position(0, 0));
	

	if (direction_ == Direction::dir::up) {
		HitBox hbHit(Position(hbChar_.getDL().getX(), hbChar_.getHR().getY()), Position(hbChar_.getHR().getX(), hbChar_.getHR().getY() + 2));
		hb = hbHit;
	}
	else if (direction_ == Direction::dir::down) {
		HitBox hbHit2(Position(hbChar_.getDL().getX(), hbChar_.getDL().getY() - 2), Position(hbChar_.getHR().getX(), hbChar_.getDL().getY()));
		hb = hbHit2;
	}
	else if (direction_ == Direction::dir::left) {
		HitBox hbHit3(Position(hbChar_.getDL().getX()-2, hbChar_.getDL().getY() ), Position(hbChar_.getDL().getX(), hbChar_.getHR().getY()));
		hb = hbHit3;
		
	}
	else if (direction_ == Direction::dir::right) {
		HitBox hbHit4(Position(hbChar_.getHR().getX() , hbChar_.getDL().getY()), Position(hbChar_.getHR().getX()+2, hbChar_.getHR().getY()));
		hb = hbHit4;
	}
	return hb;


	/*

	switch (direction_) {
	case Direction::dir::up:
		HitBox hbHit(Position(hbChar_.getDL().getX(),hbChar_.getHR().getY()),Position(hbChar_.getHR().getX(),hbChar_.getHR().getY()+2));
		hb = hbHit;
		
		break;

	case Direction::dir::down:
		HitBox hbHit2(Position(hbChar_.getDL().getX(), hbChar_.getDL().getY()-2), Position(hbChar_.getHR().getX(), hbChar_.getDL().getY()));
		hb = hbHit2;
		break;

	case Direction::dir::left:
		HitBox hbHit3(Position(hbChar_.getDL().getX(), hbChar_.getHR().getY()), Position(hbChar_.getHR().getX(), hbChar_.getHR().getY() + 2));
		hb = hbHit3;
		break;

	case Direction::dir::right:
		
		HitBox hbHit4(Position(hbChar_.getDL().getX(), hbChar_.getHR().getY()), Position(hbChar_.getHR().getX(), hbChar_.getHR().getY() + 2));
		hb = hbHit4;

		break;


	}
	return hb;
	*/
}