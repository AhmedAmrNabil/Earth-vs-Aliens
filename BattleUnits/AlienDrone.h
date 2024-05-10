#ifndef ALIEN_DRONE_H
#define ALIEN_DRONE_H

#include "Unit.h"

class AlienDrone : public Unit {
   public:
    AlienDrone(Game* game, int joinTime, double health, double power, int attackCapacity);
    bool attack() override;
};

#endif