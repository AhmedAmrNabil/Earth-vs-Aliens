#include "AlienMonster.h"
#include "../Game.h"


void AlienMonster::attack(Game* game, int timestep)
{
   
    Unit* tank = nullptr;
    Unit* soldier = nullptr;

    for (int i = 0; i < this->getAttackCapacity(); ++i)
    {
        if (game->getEarthUnit(ET, tank)) {
            tank->getAttacked(this, timestep);
            if (tank->isDead())
                game->addToKilled(tank);
            else
                game->addToTemp(tank);
        }
        if (game->getEarthUnit(AS, soldier)) {
            soldier->getAttacked(this, timestep);
            if (soldier->isDead())
                game->addToKilled(soldier);
            else
                game->addToTemp(soldier);
        }
    }
   
}
