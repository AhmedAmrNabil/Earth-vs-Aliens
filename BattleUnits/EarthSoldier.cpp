#include "EarthSoldier.h"

void EarthSoldier::attack(Game* game, int timestep) {
	LinkedQueue<Unit*> tmpList;
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
				tmpList.enqueue(enemyUnit);
		}
	}

	while (!tmpList.isEmpty()) {
		tmpList.dequeue(enemyUnit);
		game->addExistingAlienUnit(AS, enemyUnit);
	}
}
