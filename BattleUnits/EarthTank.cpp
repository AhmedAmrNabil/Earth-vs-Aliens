#include "EarthTank.h"

EarthTank::EarthTank(Game* game,int joinTime, int health, int power, int attackCapacity)
    : Unit(game, ET, joinTime, health, power, attackCapacity) {
}
void EarthTank::attack() {
    int timestep = game->getTimestep();
    Unit* monster;
    Unit* soldier;
    bool attackSoldiers = false;
    LinkedQueue<Unit*> total;
    int monsterCount , soldierCount;
    if (game->getSoldierRatio() < 30) attackSoldiers = true;
    if(attackSoldiers) {
        monsterCount = getAttackCapacity() / 2;
        soldierCount = getAttackCapacity() - monsterCount;
    }
    else {
        monsterCount = getAttackCapacity();
        soldierCount = 0;
    }
    while (attackSoldiers && soldierCount != 0 ) {
        if (game->getAlienUnit(AS, soldier)) {
            soldier->getAttacked(this, timestep);
            total.enqueue(soldier);
            if (game->getSoldierRatio() > 80) attackSoldiers = false;
            soldierCount--;
        }
        else break;
    }
    monsterCount += soldierCount;
    while (monsterCount != 0) {
        if (game->getAlienUnit(AM, monster)) {
            monster->getAttacked(this, timestep);
            total.enqueue(monster);
            monsterCount--;
        }
        else break;
    }

    total.print();
    Unit* unit;
    while (!total.isEmpty()) {
        total.dequeue(unit);
        if (unit->isDead()) game->addToKilled(unit);
        else game->addAlienUnit(unit);
    }
}
