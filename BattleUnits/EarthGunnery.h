#ifndef EARTH_GUNNER_H_
#define EARTH_GUNNER_H_

#include "Unit.h"

class EarthGunnery : public Unit {
   public:
    EarthGunnery(Game* game, int joinTime, int health, int power, int attackCapacity);
    void attack() override;
    int getPriority();
};

#endif