#include "AlienSoldier.h"

#include "../Game.h"

AlienSoldier::AlienSoldier(Game* game, int joinTime, int health, int power, int attackCapacity)
	: Unit(game, AS, joinTime, health, power, attackCapacity) {
}

void AlienSoldier::attack() {
	int timestep = game->getTimestep();
	Unit* enemyUnit;
	LinkedQueue<Unit*> tempList;
	int soldierCount = this->getAttackCapacity();
	while (soldierCount) {
		if (game->getEarthUnit(ES, enemyUnit)) {
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
			game->addEarthUnit(enemyUnit);
	}
}
