// BoxHead.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "HitBox.h"
#include <iostream>
#include "Character.h"

int main()
{

	Position pos1(1, 1);
	Position pos2(4, 4);
	HitBox hb1(pos1, pos2);



	Position pos3(1, 1);
	Position pos4(4, 4);
	HitBox hb2(pos3, pos4);
	//std::cout<<hb1.overlaps(hb2);


	Character ch(1, hb1);
	std::cout << ch.getXDL() << ch.getYDL() << "   " << ch.getXHR() << ch.getYHR() << std::endl;
	
	ch.move(Direction::dir::up);
	std::cout << ch.getXDL() << ch.getYDL() << "   " << ch.getXHR() << ch.getYHR() << std::endl;


}

