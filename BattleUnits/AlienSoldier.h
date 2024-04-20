#ifndef ALIEN_SOLDIER_H
#define ALIEN_SOLDIER_H

#include "Unit.h"

class AlienSoldier : public Unit {
   public:
    AlienSoldier(Game* game, int joinTime, int health, int power, int attackCapacity);
    void attack() override;
};

#endif