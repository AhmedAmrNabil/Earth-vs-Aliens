#include "AlienSoldier.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"


AlienSoldier::AlienSoldier(Game* game, int joinTime, double health, double power, int attackCapacity)
	: Unit(game, AS, joinTime, health, power, attackCapacity) {
}

bool AlienSoldier::attack() {
	int timestep = game->getTimestep();
	Unit* enemyUnit;
	LinkedQueue<Unit*> tempListSoldier;
	LinkedQueue<Unit*> tempListSaver;
	int soldierCount = this->getAttackCapacity();
	int saverCount = 0;
	if (game->saverIsActive()) { // If saver Units is active attack it
		soldierCount /= 2;
		saverCount = this->getAttackCapacity() - soldierCount;
	}
	bool attacked = false;
	while (soldierCount) {
		if (game->getEarthUnit(ES, enemyUnit)) {
			enemyUnit->getAttacked(this, timestep);
			tempListSoldier.enqueue(enemyUnit);
			attacked = true;
		}
		else break;
		--soldierCount;
	}

	// Adds the leftover capcity from soldiers if there are no soldiers left
	saverCount += soldierCount;
	while (saverCount) {
		if (game->getSaverUnit(enemyUnit)) {
			enemyUnit->getAttacked(this, timestep);
			tempListSaver.enqueue(enemyUnit);
			attacked = true;
		}
		else break;
		--saverCount;
	}

	// Adds the leftover capcity from savers if there are no savers left
	soldierCount += saverCount;
	while (soldierCount) {
		if (game->getEarthUnit(ES, enemyUnit)) {
			enemyUnit->getAttacked(this, timestep);
			tempListSoldier.enqueue(enemyUnit);
			attacked = true;
		}
		else break;
		--soldierCount;
	}


	// Print the attacked units
	if (game->isInteractive() && (!tempListSoldier.isEmpty() || !tempListSaver.isEmpty())) {
		string attackedIds = "\tAS ";
		attackedIds += this;
		attackedIds += " shots\t";
		if (tempListSoldier.dequeue(enemyUnit)) {
			attackedIds += "[";
			game->handleUnit(enemyUnit);
			attackedIds += enemyUnit;
			while (!tempListSoldier.isEmpty()) {
				tempListSoldier.dequeue(enemyUnit);
				game->handleUnit(enemyUnit);
				attackedIds += ", ";
				attackedIds += enemyUnit;
			}
			attackedIds += "]";
		}

		if (tempListSaver.dequeue(enemyUnit)) {
			attackedIds += "[";
			game->handleUnit(enemyUnit);
			attackedIds += enemyUnit;
			while (!tempListSaver.isEmpty()) {
				tempListSaver.dequeue(enemyUnit);
				game->handleUnit(enemyUnit);
				attackedIds += ", ";
				attackedIds += enemyUnit;
			}
			attackedIds += "]";
		}
		attackedIds += '\n';
		game->addToAttacked(attackedIds);

	}

	// Handle the attacked units if the game is in silent mode
	while (!tempListSoldier.isEmpty()) {
		tempListSoldier.dequeue(enemyUnit);
		game->handleUnit(enemyUnit);
	}

	while (!tempListSaver.isEmpty()) {
		tempListSaver.dequeue(enemyUnit);
		game->handleUnit(enemyUnit);
	}

	return attacked;
}






