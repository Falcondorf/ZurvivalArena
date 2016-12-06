// BoxHead.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "HitBox.h"
#include <iostream>
#include "Character.h"
#include "Heroes.h"
#include "enemy.h"
#include "Element.h"


int main()
{

	
	// HEROES 

	Position pos1(5, 5);
	Position pos2(10, 10);
	HitBox hbHeroes(pos1, pos2);
	Heroes heroes("jules",1, hbHeroes);
	

	// ENEMY DOWN 0 DU HEROES OK 

	Position posd(3, 2);
	Position posd2(6, 7);
	HitBox hbDown(posd, posd2);	
	Enemy  en1(1,hbDown);

	heroes.setDirection(Direction::dir::down);

	std::cout << "TEST DOWN  000->1" << " " << heroes.hitPerimeter().overlaps(hbDown) << std::endl;


	// ENEMY UP 0 DU HEROES OK 

	Position posu(9, 9);
	Position posu2(11, 11);
	HitBox hbUp(posu, posu2);

	Enemy  en2(1, hbUp);


	heroes.setDirection(Direction::dir::up);
	std::cout << "TEST UP    000->1" << " " << heroes.hitPerimeter().overlaps(hbUp) << std::endl;

	// ENEMY UP 1 DU HEROES  ok

	Position posu3(6, 9);
	Position posu4(7, 11);
	HitBox hbUp2(posu3, posu4);

	Enemy  en3(1, hbUp2);

	heroes.setDirection(Direction::dir::up);
	std::cout << "TEST UP    001->1" << " " << heroes.hitPerimeter().overlaps(hbUp2) << std::endl;


	
	// ENEMY UP 2 DU HEROES  KO

	Position posu5(3, 3);
	Position posu6(5, 10);
	HitBox hbUp3(posu5, posu6);

	Enemy  en4(1, hbUp3);

	heroes.setDirection(Direction::dir::up);
	std::cout << "TEST UP    002->0" << " " << heroes.hitPerimeter().overlaps(hbUp3) << std::endl;

	// ENEMY LEFT 0 DU HEROES  OK

	Position posu7(3, 3);
	Position posu8(5, 10);
	HitBox hbLeft(posu7, posu8);

	Enemy  en5(1, hbLeft);

	heroes.setDirection(Direction::dir::left);
	std::cout << "TEST LEFT  000->1" << " " << heroes.hitPerimeter().overlaps(hbLeft) << std::endl;
	/*
	HitBox taysthb = heroes.hitPerimeter();
	std::cout << taysthb.getDL().getX() << " " << taysthb.getDL().getY() << std::endl;
	std::cout << taysthb.getHR().getX() << " " << taysthb.getHR().getY() << std::endl;
	std::cout<<taysthb.overlaps(hbLeft)<<std::endl;
	*/


	//ENEMY LEFT 1 DU HEROES KO

	Position posu20(0, 0);
	Position posu21(3, 10); //FRONTIERE DONC PAS TOUCHER DONC KO
	HitBox hbLeft2(posu20, posu21);

	Enemy  en20(1, hbLeft2);
	heroes.setDirection(Direction::dir::left);
	std::cout << "TEST LEFT  001->0" << " " << heroes.hitPerimeter().overlaps(hbLeft2) << std::endl;



	// ENEMY RIGHT 0 DU HEROES  KO
	
	Position posu9(6, 5);
	Position posu10(8, 10);
	HitBox hbRight(posu9, posu10);

	Enemy  en6(1, hbRight);

	heroes.setDirection(Direction::dir::right);
	std::cout << "TEST RIGHT 000->0" << " " << heroes.hitPerimeter().overlaps(hbLeft) << std::endl;
	

	// ENEMY RIGHT 1 DU HEROES  OK

	Position posu11(11, 6);
	Position posu12(12, 7);
	HitBox hbRight2(posu11, posu12);

	Enemy  en7(1, hbRight2);

	heroes.setDirection(Direction::dir::right);
	std::cout << "TEST RIGHT 001->1" << " " << heroes.hitPerimeter().overlaps(hbRight2) << std::endl;

	// Creation floor 

	Position posFloor(0, 0);
	Position posFloor2(2, 2);
	Element floor(posFloor, posFloor2, "floor");
	//std::cout << floor.getIsReachable();

}

