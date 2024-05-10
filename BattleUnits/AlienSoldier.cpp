#include "AlienSoldier.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"


AlienSoldier::AlienSoldier(Game* game, int joinTime, double health, double power, int attackCapacity)
	: Unit(game, AS, joinTime, health, power, attackCapacity) {
}

bool AlienSoldier::attack() {
	int timestep = game->getTimestep();
	Unit* enemyUnit;
	LinkedQueue<Unit*> tempList;
	int soldierCount = this->getAttackCapacity();
	bool attacked = false;
	while (soldierCount) {
		if (game->getEarthUnit(ES, enemyUnit)) {
			enemyUnit->getAttacked(this, timestep);
			tempList.enqueue(enemyUnit);
			attacked = true;
		}
		else break;
		--soldierCount;
	}
	if (!tempList.isEmpty() && game->isInteractive()) {
		cout << "\tAS " << this << " shots ";
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
