#ifndef ALIEN_DRONE_H
#define ALIEN_DRONE_H

#include "Unit.h"

class AlienDrone : public Unit {
   public:
    AlienDrone(Game* game, int joinTime, int health, int power, int attackCapacity);
    void attack() override;
};

#endif