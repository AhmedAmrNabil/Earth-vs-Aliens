#ifndef ALIEN_SOLDIER_H_
#define ALIEN_SOLDIER_H_

#include "Unit.h"

class Game;
class AlienSoldier : public Unit {
   public:
    AlienSoldier(int id, int joinTime, int health, int power, int attackCapacity)
        : Unit(AS, id, joinTime, health, power, attackCapacity){};

    void attack(Game* game, int timestep) override;
};

#endif