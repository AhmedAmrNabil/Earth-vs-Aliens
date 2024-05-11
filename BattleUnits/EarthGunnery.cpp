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

    if ((!tempListDrone.isEmpty() || !tempListMonster.isEmpty()) && game->isInteractive()) {
        cout << "\tEG " << this << " shots ";
        cout << "\t";
        tempListMonster.print();
        tempListDrone.print();
        cout << endl;
    }

    while (!tempListDrone.isEmpty()) {
        tempListDrone.pop(enemyUnit);
        game->handleUnit(enemyUnit);
    }

    while (!tempListMonster.isEmpty()) {
        tempListMonster.dequeue(enemyUnit);
        game->handleUnit(enemyUnit);
    }

    return attacked;
}
