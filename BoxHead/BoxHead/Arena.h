#pragma once

#include <vector>
#include "Heroes.h"
#include "enemy.h"
#include <string>
class Arena
{
private:
	std::vector<Heroes> listHeroes;
	std::vector<Enemy> listEnemy;
	HitBox  perimetre;

public:
	inline Arena(std::vector<std::string> namesPlayers);
	inline void hit(Heroes player);
	
};

Arena::Arena(std::vector<std::string> namesPlayers) {
	

}

void Arena::hit(Heroes player) {
	for (Enemy e:listEnemy)
	{
		HitBox playerHB = player.hitPerimeter();
		if (playerHB.overlaps(e.getHitBox)) {
			e.removeLife;
		}
	}


}