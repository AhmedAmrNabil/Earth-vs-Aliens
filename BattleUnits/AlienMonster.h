#pragma once

#include "../Armies/Army.h"
#include "Unit.h"
#include "../DataStructures/LinkedListStack.h";
#include "../DataStructures/LinkedQueue.h";

class AlienMonster : public Unit {
   public:
    AlienMonster(int id,int joinTime, int health, int power, int attackCapacity) 
        : Unit(AM,id ,joinTime, health, power, attackCapacity) {}


    void attack(Army* enemyArmy, int timestep) {
        LinkedQueue<Unit*> tempSoldiers;
        LinkedListStack<Unit*> tempEarthTanks;
        Unit* T1 = nullptr;
        Unit* S1 = nullptr;
		Unit* tmp;
        for (int i = 0; i < this->getAttackCapacity(); ++i)
        {
            if (enemyArmy->getUnit(ET, T1, tmp))
            {
                T1->getAttacked(this, timestep);
                if (T1->isDead())
                    enemyArmy->addToKilled(T1);
                else
                    tempEarthTanks.push(T1);
            }
            if (enemyArmy->getUnit(AS, S1, tmp))
            {
                S1->getAttacked(this, timestep);
                if (S1->isDead())
                    enemyArmy->addToKilled(S1);
                else
                    tempSoldiers.enqueue(S1);
            }
        }
        Unit* temp = nullptr;
        while (!tempSoldiers.isEmpty())
        {
            tempSoldiers.dequeue(temp);
            enemyArmy->addExisting(AS, temp);
        }
        while (!tempEarthTanks.isEmpty()) 
        {
            tempEarthTanks.pop(temp);
            enemyArmy->addExisting(ET, temp);
        }
    }

    
};
