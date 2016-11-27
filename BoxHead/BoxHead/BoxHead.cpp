// BoxHead.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "HitBox.h"
#include <iostream>
#include "Character.h"
#include "Heroes.h"
#include "enemy.h"

int main()
{
/*
	Position pos1(1, 1);
	Position pos2(4, 4);
	HitBox hb1(pos1, pos2);



	Position pos3(1, 1);
	Position pos4(4, 4);
	HitBox hb2(pos3, pos4);
	
	//std::cout<<hb1.overlaps(hb2);
	*/
	
	




	Position pos1(1, 1);
	Position pos2(4, 4);
	HitBox hb3(pos1, pos2);
	Heroes ch("jules",1,hb3);
	
	

	Position pos3(0, 5);
	Position pos4(2, 8);
	HitBox hb4(pos3, pos4);
	
	Enemy  en(1,hb4);

	
	

	
	HitBox hbhit=ch.hitPerimeter();
	//std::cout << hbhit.overlaps(hb4)<<std::endl;
	std::cout<<"ennemi touche "<<"            "<<hbhit.overlaps(hb4)<<std::endl;

	ch.move(Direction::dir::left);
	std::cout << "ennemi rate " << "            " << hbhit.overlaps(hb4) << std::endl;




	/*
	std::cout << ch.getXDL() << ch.getYDL() << "   " << ch.getXHR() << ch.getYHR() << std::endl;
	
	ch.move(Direction::dir::up);
	std::cout << ch.getXDL() << ch.getYDL() << "   " << ch.getXHR() << ch.getYHR() << std::endl;
	*/

	

}

