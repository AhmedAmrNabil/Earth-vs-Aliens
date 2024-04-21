#include "EarthSoldier.h"

#include "../Game.h"

EarthSoldier::EarthSoldier(Game* game, int joinTime, int health, int power, int attackCapacity)
	: Unit(game, ES, joinTime, health, power, attackCapacity) {
}

void EarthSoldier::attack() {
	int timestep = game->getTimestep();
	Unit* enemyUnit;
	LinkedQueue<Unit*> tempList;
	int soldierCount = this->getAttackCapacity();
	while (soldierCount) {
		if (game->getAlienUnit(AS, enemyUnit)) {
			enemyUnit->getAttacked(this, timestep);
			tempList.enqueue(enemyUnit);
		}
		else break;
		--soldierCount;
	}
	tempList.print();
	while (!tempList.isEmpty()) {
		tempList.dequeue(enemyUnit);
		if (enemyUnit->isDead())
			game->addToKilled(enemyUnit);
		else
			game->addAlienUnit(enemyUnit);
	}
}
