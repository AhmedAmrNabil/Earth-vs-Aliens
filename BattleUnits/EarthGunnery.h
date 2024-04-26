#ifndef EARTH_GUNNER_H
#define EARTH_GUNNER_H

#include "Unit.h"

class EarthGunnery : public Unit {
   public:
    EarthGunnery(Game* game, int joinTime, double health, double power, int attackCapacity);
    void attack() override;
    int getPriority();
};

#endif