#include "EarthSoldier.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"


EarthSoldier::EarthSoldier(Game* game, int joinTime, double health, double power, int attackCapacity)
	: Unit(game, ES, joinTime, health, power, attackCapacity) {
	infected = false;
	immune = false;
}

bool EarthSoldier::attack() {
	int timestep = game->getTimestep();
	bool attacked = false;
	Unit* enemyUnit;
	LinkedQueue<Unit*> tempList;
	int soldierCount = this->getAttackCapacity();
	while (soldierCount) {
		if (this->infected) { // Attacks earth soldiers if infected
			if (game->getEarthUnit(ES, enemyUnit)) {
				if (enemyUnit != this) {
					enemyUnit->getAttacked(this, timestep);
					tempList.enqueue(enemyUnit);
					attacked = true;
				}
				else game->handleUnit(enemyUnit);
			}
			else break;
		}
		else { 
			if (game->getAlienUnit(AS, enemyUnit)) {
				enemyUnit->getAttacked(this, timestep);
				tempList.enqueue(enemyUnit);
				attacked = true;
			}
			else break;
		}
		--soldierCount;
	}

	// Printing of the attacked list
	if (game->isInteractive() && !tempList.isEmpty()) {
		string attackedIds = "\tES ";
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

	// Handle the attacked units if the game is in silent mode
	while (!tempList.isEmpty()) {
		tempList.dequeue(enemyUnit);
		game->handleUnit(enemyUnit);
	}

	return attacked;
}

bool EarthSoldier::isInfected() {
	return infected;
}

void EarthSoldier::setInfected(bool b) {
	infected = b;
}

bool EarthSoldier::isImmune() {
	return immune;
}

void EarthSoldier::setImmunity(bool b) {
	immune = b;
}
