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

void EarthGunnery::attack() {
    int timestep = game->getTimestep();
    Unit* enemyUnit = nullptr;
    LinkedListStack<Unit*> tempListDrone;
    LinkedQueue<Unit*> tempListMonster;

    int monsterCount = this->getAttackCapacity() / 2;
    int dronesCount = this->getAttackCapacity() - monsterCount;
    while (monsterCount > 0) {
        if (game->getAlienUnit(AM, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListMonster.enqueue(enemyUnit);
        }
        else break;
        --monsterCount;
    }

    dronesCount += monsterCount;

    while (dronesCount>0) {
        if (game->getAlienUnit(AD, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListDrone.push(enemyUnit);
        }
        else break;
        --dronesCount;
    }

    if (!tempListDrone.isEmpty() || !tempListMonster.isEmpty()) {
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
}
