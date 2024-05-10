#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H

#include "Unit.h"

class AlienMonster : public Unit {
    int infectionPercent;
   public:
    AlienMonster(Game* game, int joinTime, double health, double power, int attackCapacity, int infectionPercent);
    bool attack()override;
    bool willInfect();
};

#endif