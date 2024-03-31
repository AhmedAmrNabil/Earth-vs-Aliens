#pragma once

#include "../Armies/Army.h"
#include "../DataStructures/LinkedQueue.h"
#include "Unit.h"

class Soldier : public Unit {
   public:
    Soldier(int joinTime, int health, int power, int attackCapacity) : 
	Unit(S, joinTime, health, power, attackCapacity)
	{};

    void attack(Army* enemyArmy, int timestep) {
        LinkedQueue<Unit*> tmpList;
        Unit* enemyUnit;
        Unit* tmp;
        clearAttacked();
        for (int i = 0; i < this->getAttackCapacity(); ++i) {
            enemyArmy->getUnit(S, enemyUnit, tmp);
            enemyUnit->getAttacked(this, timestep);
            attackedUnits.enqueue(enemyUnit);
            if (enemyUnit->isDead())
                enemyArmy->addToKilled(enemyUnit);
            else
                tmpList.enqueue(enemyUnit);
        }

        while (!tmpList.isEmpty()) {
            tmpList.dequeue(enemyUnit);
            enemyArmy->addExisting(S, enemyUnit);
        }
    };
};