#pragma once

#include "../Armies/Army.h"
#include "../DataStructures/LinkedListStack.h"
#include "../DataStructures/LinkedQueue.h"
#include "Unit.h"
class Game;

class AlienMonster : public Unit {
   public:
    AlienMonster(int joinTime, int health, int power, int attackCapacity);
    void attack(Game* game, int timestep)override;
};
