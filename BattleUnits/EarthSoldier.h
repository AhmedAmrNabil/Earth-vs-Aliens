#ifndef EARTH_SOLDIER_H_
#define EARTH_SOLDIER_H_

#include "Unit.h"

class Game;
class EarthSoldier : public Unit {
   public:
    EarthSoldier(int joinTime, int health, int power, int attackCapacity);
    void attack(Game* game, int timestep) override;
};

#endif