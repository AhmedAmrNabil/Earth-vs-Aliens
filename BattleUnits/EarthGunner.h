#pragma once

#include "../Armies/Army.h"
#include "../DataStructures/LinkedQueue.h"
#include "Unit.h"

class EarthGunner : public Unit 
{
   bool isAlien() override { return false; };
   public:
    EarthGunner(int id, int joinTime, int health, int power, int attackCapacity) 
        : Unit(EG,id , joinTime, health, power, attackCapacity){};

    virtual void attack(Army* enemyArmy, int timestep) {
        LinkedQueue<Unit*> tmpList;
        Unit* drone1;
        Unit* drone2;
        clearAttacked();

        for (int i = 0; i < this->getAttackCapacity(); ++i) {
            enemyArmy->getUnit(AD,drone1,drone2);
            drone1->getAttacked(this, timestep);
            attackedUnits.enqueue(drone1);
            if (drone1->isDead())
                enemyArmy->addToKilled(drone1);
            else
                tmpList.enqueue(drone1);

            if (drone2 != drone1) {
                drone2->getAttacked(this, timestep);
                attackedUnits.enqueue(drone2);
                if (drone2->isDead())
                    enemyArmy->addToKilled(drone2);
                else
                    tmpList.enqueue(drone2);
            }
        }

        while (!tmpList.isEmpty()) {
            tmpList.dequeue(drone1);
            enemyArmy->addExisting(AD, drone1);
        }
    }

    int getPriority(){
        return power * sqrt(health);
    }

    

};