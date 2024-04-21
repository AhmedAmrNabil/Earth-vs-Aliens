#include "EarthGunnery.h"
#include "../Game.h"
#include <cmath>

EarthGunnery::EarthGunnery(Game* game, int joinTime, int health, int power, int attackCapacity)
    : Unit(game,EG, joinTime, health, power, attackCapacity) {
};

int EarthGunnery::getPriority() {
    return power * sqrt(health);
}

void EarthGunnery::attack() {
    int timestep = game->getTimestep();
    Unit* enemyUnit = nullptr;
    LinkedListStack<Unit*> tempList;

    int monsterCount = this->getAttackCapacity() / 2;
    int dronesCount = this->getAttackCapacity() - monsterCount;
    while (monsterCount > 0) {
        if (game->getAlienUnit(AM, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempList.push(enemyUnit);
        }
        else break;
        --monsterCount;
    }

    dronesCount += monsterCount;

    while (dronesCount>0) {
        if (game->getAlienUnit(AD, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempList.push(enemyUnit);
        }
        else break;
        --dronesCount;
    }
    tempList.print();
    while (!tempList.isEmpty()) {
        tempList.pop(enemyUnit);
        if (enemyUnit->isDead())
            game->addToKilled(enemyUnit);
        else
            game->addAlienUnit(enemyUnit);
    }
}
