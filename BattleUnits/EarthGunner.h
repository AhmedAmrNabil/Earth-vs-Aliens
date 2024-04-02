#pragma once

#include "../Armies/Army.h"
#include "../DataStructures/LinkedQueue.h"
#include "Unit.h"
#include "../Game.h"

class EarthGunner : public Unit
{
public:
	EarthGunner(int id, int joinTime, int health, int power, int attackCapacity)
		: Unit(EG, id, joinTime, health, power, attackCapacity) {};

	virtual void attack(Game* game, int timestep) {
		LinkedQueue<Unit*> tmpList;
		Unit* drone1;
		Unit* drone2 = nullptr;
		clearAttacked();

		for (int i = 0; i < this->getAttackCapacity(); ++i) {
			if (game->getAlienUnit(AD, drone1, drone2)) {
				drone1->getAttacked(this, timestep);
				attackedUnits.enqueue(drone1);
				if (drone1->isDead())
					game->addToKilled(drone1);
				else
					tmpList.enqueue(drone1);
			}

			if (drone2 != nullptr) {
				drone2->getAttacked(this, timestep);
				attackedUnits.enqueue(drone2);
				if (drone2->isDead())
					game->addToKilled(drone2);
				else
					tmpList.enqueue(drone2);
			}
		}

		while (!tmpList.isEmpty()) {
			tmpList.dequeue(drone1);
			game->addExistingAlienUnit(AD, drone1);
		}
	}

	int getPriority() {
		return power * sqrt(health);
	}

};