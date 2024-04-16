#ifndef ALIEN_SOLDIER_H_
#define ALIEN_SOLDIER_H_

#include "Unit.h"

class AlienSoldier : public Unit {
   public:
    AlienSoldier(Game* game, int joinTime, int health, int power, int attackCapacity);
    void attack() override;
};

#endif