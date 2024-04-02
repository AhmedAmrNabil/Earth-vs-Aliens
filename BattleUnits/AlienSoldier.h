#pragma once

#include "../Armies/Army.h"
#include "../DataStructures/LinkedQueue.h"
#include "Unit.h"

class AlienSoldier : public Unit {

public:
	AlienSoldier(int id,int joinTime ,int health, int power, int attackCapacity) 
		: Unit(AS,id , joinTime, health, power, attackCapacity){
	};

	void attack(Army* enemyArmy, int timestep) override {
		LinkedQueue<Unit*> tmpList;
		Unit* enemyUnit;
		Unit* tmp;
		clearAttacked();
		for (int i = 0; i < this->getAttackCapacity(); ++i) {
			if (enemyArmy->getUnit(ES, enemyUnit, tmp))
			{
				enemyUnit->getAttacked(this, timestep);
				attackedUnits.enqueue(enemyUnit);
				if (enemyUnit->isDead())
					enemyArmy->addToKilled(enemyUnit);
				else
					tmpList.enqueue(enemyUnit);
			}
		}

		while (!tmpList.isEmpty()) {
			tmpList.dequeue(enemyUnit);
			enemyArmy->addExisting(ES, enemyUnit);
		}
	};


};