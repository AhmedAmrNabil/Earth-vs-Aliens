#include "EarthTank.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"

EarthTank::EarthTank(Game* game,int joinTime, double health, double power, int attackCapacity)
    : Unit(game, ET, joinTime, health, power, attackCapacity) {
}
bool EarthTank::attackSoldiers = false;

bool EarthTank::attack() {
    bool attacked = false;
    if (!attackSoldiers && game->getSoldierRatio() < 30) attackSoldiers = true;
    if ( attackSoldiers && game->getSoldierRatio() > 80) attackSoldiers = false;
    int timestep = game->getTimestep();
    Unit* enemyUnit;
    LinkedQueue<Unit*> tempListMonster;
    LinkedQueue<Unit*> tempListSolider;
    int monsterCount , soldierCount;
    if(attackSoldiers) {
        monsterCount = getAttackCapacity() / 2;
        soldierCount = getAttackCapacity() - monsterCount;
    }
    else {
        monsterCount = getAttackCapacity();
        soldierCount = 0;
    }
    while (attackSoldiers && soldierCount != 0 ) {
        if (game->getAlienUnit(AS, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListSolider.enqueue(enemyUnit);
            soldierCount--;
            attacked = true;
        }
        else break;
    }
    monsterCount += soldierCount;
    while (monsterCount != 0) {
        if (game->getAlienUnit(AM, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListMonster.enqueue(enemyUnit);
            monsterCount--;
            attacked = true;
        }
        else break;    
    }
    while (attackSoldiers && monsterCount != 0) {
        if (game->getAlienUnit(AS, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListSolider.enqueue(enemyUnit);
            soldierCount--;
            attacked = true;
        }
        else break;
    }
    if (game->isInteractive() && (!tempListMonster.isEmpty() || !tempListSolider.isEmpty())) {
        string attackedIds = "\tET ";
        attackedIds += this;
        attackedIds += " shots\t";

        if (tempListSolider.dequeue(enemyUnit)) {
            attackedIds += "[";
            game->handleUnit(enemyUnit);
            attackedIds += enemyUnit;
            while (!tempListSolider.isEmpty()) {
                tempListSolider.dequeue(enemyUnit);
                game->handleUnit(enemyUnit);
                attackedIds += ", ";
                attackedIds += enemyUnit;
            }
            attackedIds += "]";
        }

        if (tempListMonster.dequeue(enemyUnit)) {
            attackedIds += "[";
            game->handleUnit(enemyUnit);
            attackedIds += enemyUnit;
            while (!tempListMonster.isEmpty()) {
                tempListMonster.dequeue(enemyUnit);
                game->handleUnit(enemyUnit);
                attackedIds += ", ";
                attackedIds += enemyUnit;
            }
            attackedIds += "]";
        }
    }
    while (!tempListSolider.isEmpty()) {
        tempListSolider.dequeue(enemyUnit);
        game->handleUnit(enemyUnit);
    }
    while (!tempListMonster.isEmpty()) {
        tempListMonster.dequeue(enemyUnit);
        game->handleUnit(enemyUnit);
    }
    return attacked;
}
