#pragma once

#include "../Armies/Army.h"
#include "Unit.h"
#include "../DataStructures/LinkedListStack.h"
#include "../DataStructures/LinkedQueue.h"
#include "../Game.h"

class AlienMonster : public Unit {
   public:
    AlienMonster(int id,int joinTime, int health, int power, int attackCapacity) 
        : Unit(AM,id ,joinTime, health, power, attackCapacity) {}


    void attack(Game* game, int timestep) {
        LinkedQueue<Unit*> tempSoldiers;
        LinkedListStack<Unit*> tempEarthTanks;
        Unit* T1 = nullptr;
        Unit* S1 = nullptr;

        for (int i = 0; i < this->getAttackCapacity(); ++i)
        {
            if (game->getEarthUnit(ET, T1)){
                T1->getAttacked(this, timestep);
                if (T1->isDead())
                    game->addToKilled(T1);
                else
                    tempEarthTanks.push(T1);
            }
            if (game->getEarthUnit(AS, S1)){
                S1->getAttacked(this, timestep);
                if (S1->isDead())
                    game->addToKilled(S1);
                else
                    tempSoldiers.enqueue(S1);
            }
        }
        Unit* temp = nullptr;
        while (!tempSoldiers.isEmpty())
        {
            tempSoldiers.dequeue(temp);
            game->addExistingEarthUnit(AS, temp);
        }
        while (!tempEarthTanks.isEmpty()) 
        {
            tempEarthTanks.pop(temp);
            game->addExistingEarthUnit(ET, temp);
        }
    }

    
};
