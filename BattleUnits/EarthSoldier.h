#pragma once
#pragma once

#include "../Armies/Army.h"
#include "../DataStructures/LinkedQueue.h"
#include "Unit.h"
#include "../Game.h"

class EarthSoldier : public Unit {
public:
	EarthSoldier(int id, int joinTime, int health, int power, int attackCapacity)
		: Unit(ES, id, joinTime, health, power, attackCapacity) {
	};

	void attack(Game* game, int timestep) override {
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
	};


};