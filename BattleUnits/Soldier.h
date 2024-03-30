#pragma once

#include "Unit.h"
#include "../Armies/Army.h"
#include "../DataStructures/LinkedQueue.h"

class Soldier : public Unit {
   public:
    Soldier(int joinTime, int health, int power, int attackCapacity):
    Unit(S,joinTime,health,power,attackCapacity){

    };

    void attack(Army* enemyArmy){
        LinkedQueue <Unit*> tmpList;
        Unit* enemyUnit;
        for(int i = 0; i < this->getAttackCapacity(); ++i){
            enemyArmy->getSoldier(enemyUnit);
            enemyUnit->getAttacked(this);
            enemyArmy->addAttacked(S,enemyUnit);
            if(enemyUnit->isDead())
                enemyArmy->addToKilled(enemyUnit);
            else
                tmpList.enqueue(enemyUnit);
        }

        while(tmpList.isEmpty()){
            tmpList.dequeue(enemyUnit);
            enemyArmy->addUnit(S,enemyUnit);
        }
    
    };


};