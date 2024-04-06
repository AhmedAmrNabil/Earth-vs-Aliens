#include "EarthSoldier.h"

#include "../Game.h"

EarthSoldier::EarthSoldier(int id, int joinTime, int health, int power, int attackCapacity)
    : Unit(ES, id, joinTime, health, power, attackCapacity) {
    priority = 1;
}

void EarthSoldier::attack(Game* game, int timestep) {
    clearAttacked();
    Unit* enemyUnit;
    Unit* tmpUnit;
    LinkedQueue<Unit*> temp;
    int soldierCount = this->getAttackCapacity();
    while (soldierCount) {
        if (game->getAlienUnit(AS, enemyUnit, tmpUnit)) {
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
        game->addAlienUnit(enemyUnit);
    }
}
