#pragma once
#include "../DataStructures/LinkedListStack.h"
#include "Unit.h"

class AlienDrone : public Unit {
   public:
    AlienDrone(Game* game, int joinTime, int health, int power, int attackCapacity);
    void attack() override;
};