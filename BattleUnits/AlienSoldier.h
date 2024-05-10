#ifndef ALIEN_SOLDIER_H
#define ALIEN_SOLDIER_H

#include "Unit.h"

class AlienSoldier : public Unit {
   public:
    AlienSoldier(Game* game, int joinTime, double health, double power, int attackCapacity);
    bool attack() override;
};

#endif