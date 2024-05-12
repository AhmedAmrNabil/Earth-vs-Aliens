#include "EarthGunnery.h"
#include "../Game.h"
#include <cmath>
#include "../DataStructures/LinkedListStack.h"
#include "../DataStructures/LinkedQueue.h"


EarthGunnery::EarthGunnery(Game* game, int joinTime, double health, double power, int attackCapacity)
    : Unit(game,EG, joinTime, health, power, attackCapacity) {
};

int EarthGunnery::getPriority() {
    return power * sqrt(health);
}

bool EarthGunnery::attack() {
    int timestep = game->getTimestep();
    Unit* enemyUnit = nullptr;
    LinkedListStack<Unit*> tempListDrone;
    LinkedQueue<Unit*> tempListPrint;
    LinkedQueue<Unit*> tempListMonster;
    bool attacked = false;

    int monsterCount = this->getAttackCapacity() / 2;
    int dronesCount = this->getAttackCapacity() - monsterCount;
    while (monsterCount) {
        if (game->getAlienUnit(AM, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListMonster.enqueue(enemyUnit);
            attacked = true;
        }
        else break;
        --monsterCount;
    }

    dronesCount += monsterCount;

    while (dronesCount) {
        if (game->getAlienUnit(AD, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListDrone.push(enemyUnit);
            tempListPrint.enqueue(enemyUnit);
            attacked = true;
        }
        else break;
        --dronesCount;
    }

    monsterCount += dronesCount;

    while (monsterCount) {
        if (game->getAlienUnit(AM, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListMonster.enqueue(enemyUnit);
            attacked = true;
        }
        else break;
        --monsterCount;
    }

    if (game->isInteractive() && (!tempListMonster.isEmpty() || !tempListPrint.isEmpty())) {
        string attackedIds = "\tEG ";
        attackedIds += this;
        attackedIds += " shots\t";
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

        if (tempListPrint.dequeue(enemyUnit)) {
            attackedIds += "[";
            attackedIds += enemyUnit;
            while (!tempListPrint.isEmpty()) {
                tempListPrint.dequeue(enemyUnit);
                attackedIds += ", ";
                attackedIds += enemyUnit;
            }
            attackedIds += "]";
        }
        attackedIds += '\n';
        game->addToAttacked(attackedIds);
    }

    while (!tempListDrone.isEmpty()) {
        tempListDrone.pop(enemyUnit);
        game->handleUnit(enemyUnit);
    }

    while (!tempListMonster.isEmpty()) {
        tempListMonster.dequeue(enemyUnit);
        game->handleUnit(enemyUnit);
    }
    while (!tempListPrint.isEmpty()) {
        tempListPrint.dequeue(enemyUnit);
    }

    return attacked;
}
