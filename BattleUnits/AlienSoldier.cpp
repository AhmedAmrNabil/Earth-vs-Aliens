#include "AlienSoldier.h"

#include "../Game.h"

void AlienSoldier::attack(Game* game, int timestep) {
    Unit* enemyUnit;
    clearAttacked();
    for (int i = 0; i < this->getAttackCapacity(); ++i) {
        if (game->getEarthUnit(ES, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            attackedUnits.enqueue(enemyUnit);
            if (enemyUnit->isDead())
                game->addToKilled(enemyUnit);
            else
                game->addToTemp(enemyUnit);
        }
    }
}
