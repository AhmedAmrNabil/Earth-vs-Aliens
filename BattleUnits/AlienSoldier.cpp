#include "AlienSoldier.h"

#include "../Game.h"

AlienSoldier::AlienSoldier(Game* game, int joinTime, int health, int power, int attackCapacity)
    : Unit(game,AS, joinTime, health, power, attackCapacity) {
}

void AlienSoldier::attack() {
    int timestep = game->getTimestep();
    clearAttacked();
    Unit* enemyUnit;
    LinkedQueue<Unit*> temp;
    int soldierCount = this->getAttackCapacity();
    while (soldierCount) {
        if (game->getEarthUnit(ES, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            attackedIDs.enqueue(enemyUnit->getId());
            if (enemyUnit->isDead())
                game->addToKilled(enemyUnit);
            else
                temp.enqueue(enemyUnit);
        }
        --soldierCount;
    }

    while (!temp.isEmpty()) {
        temp.dequeue(enemyUnit);
        game->addEarthUnit(enemyUnit);
    }
}
