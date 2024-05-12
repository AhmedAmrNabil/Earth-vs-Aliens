#include "SaverUnit.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"


SaverUnit::SaverUnit(Game* game, int joinTime, double health, double power, int attackCapacity)
	: Unit(game, SU, joinTime, health, power, attackCapacity) {
}

bool SaverUnit::attack() {
	int timestep = game->getTimestep();
	bool attacked = false;
	Unit* enemyUnit;
	LinkedQueue<Unit*> tempList;
	int soldierCount = this->getAttackCapacity();
	while (soldierCount) {
		if (game->getAlienUnit(AS, enemyUnit)) {
			tempList.enqueue(enemyUnit);
			enemyUnit->getAttacked(this, timestep);
			attacked = true;
		}
		else break;
		--soldierCount;
	}

	if (game->isInteractive() && !tempList.isEmpty()) {
		string attackedIds = "\tSU ";
		attackedIds += this;
		attackedIds += " shots\t";
		if (tempList.dequeue(enemyUnit)) {
			attackedIds += "[";
			game->handleUnit(enemyUnit);
			attackedIds += enemyUnit;
			while (!tempList.isEmpty()) {
				tempList.dequeue(enemyUnit);
				game->handleUnit(enemyUnit);
				attackedIds += ", ";
				attackedIds += enemyUnit;
			}
			attackedIds += "]";
		}
		attackedIds += '\n';
		game->addToAttacked(attackedIds);
	}

	while (!tempList.isEmpty()) {
		tempList.dequeue(enemyUnit);
		game->handleUnit(enemyUnit);
	}

	return attacked;
}

