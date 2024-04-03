#pragma once

#include "../Armies/Army.h"
#include "Unit.h"
#include "../DataStructures/LinkedListStack.h"
#include "../DataStructures/LinkedQueue.h"
class Game;

class AlienMonster : public Unit {
   public:
    AlienMonster(int id,int joinTime, int health, int power, int attackCapacity) 
        : Unit(AM,id ,joinTime, health, power, attackCapacity) {}


    void attack(Game* game, int timestep);

    
};
