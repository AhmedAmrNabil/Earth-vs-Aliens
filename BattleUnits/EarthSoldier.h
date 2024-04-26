#ifndef EARTH_SOLDIER_H
#define EARTH_SOLDIER_H

#include "Unit.h"

class EarthSoldier : public Unit {
   public:
    EarthSoldier(Game* game,int joinTime, double health, double power, int attackCapacity);
    void attack() override;
};

#endif