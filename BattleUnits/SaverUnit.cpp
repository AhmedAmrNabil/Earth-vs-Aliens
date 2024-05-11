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
	if (!tempList.isEmpty() && game->isInteractive()) {
		cout << "\tSU " << this << " shots ";
		cout << "\t";
		tempList.print();
		cout << endl;
	}
	while (!tempList.isEmpty()) {
		tempList.dequeue(enemyUnit);
		game->handleUnit(enemyUnit);
	}

	return attacked;
}

