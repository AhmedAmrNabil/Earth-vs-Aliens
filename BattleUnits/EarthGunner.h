#ifndef EARTH_GUNNER_H_
#define EARTH_GUNNER_H_

#include "Unit.h"

class Game;
class EarthGunner : public Unit {
   public:
    EarthGunner(int id, int joinTime, int health, int power, int attackCapacity)
        : Unit(EG, id, joinTime, health, power, attackCapacity){};

    void attack(Game* game, int timestep);
    int getPriority();
};

#endif