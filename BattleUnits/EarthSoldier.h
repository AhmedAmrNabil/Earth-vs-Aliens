#ifndef EARTH_SOLDIER_H_
#define EARTH_SOLDIER_H_

#include "Unit.h"

class EarthSoldier : public Unit {
   public:
    EarthSoldier(Game* game,int joinTime, int health, int power, int attackCapacity);
    void attack() override;
};

#endif