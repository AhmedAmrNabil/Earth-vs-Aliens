#include "AlienSoldier.h"

#include "../Game.h"

AlienSoldier::AlienSoldier(int id, int joinTime, int health, int power, int attackCapacity)
    : Unit(AS, id, joinTime, health, power, attackCapacity) {
    priority = 1;
}

void AlienSoldier::attack(Game* game, int timestep) {
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
