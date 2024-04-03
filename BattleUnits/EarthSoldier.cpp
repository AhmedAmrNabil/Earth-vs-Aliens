#include "EarthSoldier.h"
#include "../Game.h"


void EarthSoldier::attack(Game* game, int timestep) {
	
	Unit* enemyUnit;
	Unit* tmp;
	clearAttacked();
	for (int i = 0; i < this->getAttackCapacity(); ++i) {
		if (game->getAlienUnit(AS, enemyUnit, tmp))
		{
			enemyUnit->getAttacked(this, timestep);
			attackedUnits.enqueue(enemyUnit);
			if (enemyUnit->isDead())
				game->addToKilled(enemyUnit);
			else
				game->addToTemp(enemyUnit);
		}
	}

	
}
