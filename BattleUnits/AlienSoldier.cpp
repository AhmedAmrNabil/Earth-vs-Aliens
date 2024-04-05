#include "AlienSoldier.h"

#include "../Game.h"

void AlienSoldier::attack(Game* game, int timestep) {
    Unit* enemyUnit;
    clearAttacked();
    LinkedQueue<Unit*> temp;
    for (int i = 0; i < this->getAttackCapacity(); ++i) {
        if (game->getEarthUnit(ES, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            attackedUnits.enqueue(enemyUnit);
            if (enemyUnit->isDead())
                game->addToKilled(enemyUnit);
            else
                temp.enqueue(enemyUnit);
        }
    }
    while (!temp.isEmpty())
    {
        temp.dequeue(enemyUnit);
        game->addEarthUnit(enemyUnit);
    }
}
