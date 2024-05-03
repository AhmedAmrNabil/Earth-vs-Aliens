#include "EarthTank.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"

EarthTank::EarthTank(Game* game,int joinTime, double health, double power, int attackCapacity)
    : Unit(game, ET, joinTime, health, power, attackCapacity) {
}
void EarthTank::attack() {
    int timestep = game->getTimestep();
    Unit* monster;
    Unit* soldier;
    bool attackSoldiers = false;
    LinkedQueue<Unit*> tmpmonster;
    LinkedQueue<Unit*> tmpsoldier;
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
            tmpsoldier.enqueue(soldier);
            soldierCount--;
        }
        else break;
    }
    monsterCount += soldierCount;
    while (monsterCount != 0) {
        if (game->getAlienUnit(AM, monster)) {
            monster->getAttacked(this, timestep);
            tmpmonster.enqueue(monster);
            monsterCount--;
        }
        else break;
    }
    if (!tmpsoldier.isEmpty() && game->isInteractive()) {
        cout << "\tET " << this << " shots ";
        cout << "\t";
        tmpsoldier.print();
        if (!tmpmonster.isEmpty()) tmpmonster.print();
        cout << endl;
    }
    Unit* unit;
    while (!tmpsoldier.isEmpty()) {
        tmpsoldier.dequeue(unit);
        game->handleUnit(unit);
    }
    while (!tmpmonster.isEmpty()) {
        tmpmonster.dequeue(unit);
        game->handleUnit(unit);
    }
}
