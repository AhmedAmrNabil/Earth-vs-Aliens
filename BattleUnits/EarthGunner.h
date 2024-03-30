#pragma once

#include "../Armies/AlienArmy.h"
#include "../DataStructures/LinkedQueue.h"
#include "Unit.h"

class EarthGunner : public Unit {
   public:
    EarthGunner(int joinTime, int health, int power, int attackCapacity) : Unit(EG, joinTime, health, power, attackCapacity){};

    virtual void attack(Army* enemyArmy) {
        LinkedQueue<Unit*> tmpList;
        AlienArmy* enemyAlienArmy = dynamic_cast<AlienArmy*>(enemyArmy);
        Unit* drone1;
        Unit* drone2;

        for (int i = 0; i < this->getAttackCapacity(); ++i) {
            enemyAlienArmy->getDronePair(drone1, drone2);
            drone1->getAttacked(this);
            enemyAlienArmy->addAttacked(EG,drone1);
            if (drone1->isDead())
                enemyArmy->addToKilled(drone1);
            else
                tmpList.enqueue(drone1);

            if (drone2 != drone1) {
                drone2->getAttacked(this);
                enemyAlienArmy->addAttacked(EG,drone2);
                if (drone2->isDead())
                    enemyArmy->addToKilled(drone2);
                else
                    tmpList.enqueue(drone2);
            }
        }

        while(tmpList.isEmpty()){
            tmpList.dequeue(drone1);
            enemyArmy->addUnit(AD,drone1);
        }



    }
};