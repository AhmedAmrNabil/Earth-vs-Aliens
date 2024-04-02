#pragma once

#include "../Armies/Army.h"
#include "../DataStructures/LinkedQueue.h"
#include "Unit.h"
#include "../Game.h"

class AlienSoldier : public Unit {

public:
	AlienSoldier(int id,int joinTime ,int health, int power, int attackCapacity) 
		: Unit(AS,id , joinTime, health, power, attackCapacity){
	};

	void attack(Game* game, int timestep) override {
		LinkedQueue<Unit*> tmpList;
		Unit* enemyUnit;
		clearAttacked();
		for (int i = 0; i < this->getAttackCapacity(); ++i) {
			if (game->getEarthUnit(ES, enemyUnit)){
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
			game->addExistingEarthUnit(ES, enemyUnit);
		}
	};


};