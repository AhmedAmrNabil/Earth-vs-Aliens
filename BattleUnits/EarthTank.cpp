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
    Unit* monster;
    Unit* soldier;
    LinkedQueue<Unit*> tmpmonster;
    LinkedQueue<Unit*> tmpsoldier;
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
        if (game->getAlienUnit(AS, soldier)) {
            soldier->getAttacked(this, timestep);
            tmpsoldier.enqueue(soldier);
            soldierCount--;
            attacked = true;
        }
        else break;
    }
    monsterCount += soldierCount;
    while (monsterCount != 0) {
        if (game->getAlienUnit(AM, monster)) {
            monster->getAttacked(this, timestep);
            tmpmonster.enqueue(monster);
            monsterCount--;
            attacked = true;
        }
        else break;    
    }
    while (attackSoldiers && monsterCount != 0) {
        if (game->getAlienUnit(AS, soldier)) {
            soldier->getAttacked(this, timestep);
            tmpsoldier.enqueue(soldier);
            soldierCount--;
            attacked = true;
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
    return attacked;
}
