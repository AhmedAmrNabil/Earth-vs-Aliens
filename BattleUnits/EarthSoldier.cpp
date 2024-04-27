#include "EarthSoldier.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"


EarthSoldier::EarthSoldier(Game* game, int joinTime, double health, double power, int attackCapacity)
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
	if (!tempList.isEmpty() && game->isInteractive()) {
		cout << "\tES " << this << " shots ";
		cout << "\t";
		tempList.print();
		cout << endl;
	}
	while (!tempList.isEmpty()) {
		tempList.dequeue(enemyUnit);
		game->handleUnit(enemyUnit);
	}
}
