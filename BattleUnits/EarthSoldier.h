#ifndef EARTH_SOLDIER_H
#define EARTH_SOLDIER_H

#include "Unit.h"

class EarthSoldier : public Unit {
    bool infected;
    bool immune;
   public:
    EarthSoldier(Game* game,int joinTime, double health, double power, int attackCapacity);
    bool attack() override;
    bool isInfected();
    bool isImmune();
    void setInfected(bool b);
    void setImmunity(bool b);
};

#endif