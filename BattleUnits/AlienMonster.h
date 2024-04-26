#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H

#include "Unit.h"

class AlienMonster : public Unit {
   public:
    AlienMonster(Game* game, int joinTime, double health, double power, int attackCapacity);
    void attack()override;
};

#endif