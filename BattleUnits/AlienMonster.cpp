#include "AlienMonster.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"
#include "../DataStructures/LinkedListStack.h"


AlienMonster::AlienMonster(Game* game, int joinTime, double health, double power, int attackCapacity)
    : Unit(game,AM, joinTime, health, power, attackCapacity) {
}

void AlienMonster::attack() {
    int timestep = game->getTimestep();
    LinkedListStack<Unit*> tempEarthTanks;
    LinkedQueue<Unit*> temp;
    Unit* tank = nullptr;
    Unit* soldier = nullptr;
    int soldierCount = this->getAttackCapacity() / 2;
    int tankCount = this->getAttackCapacity() - soldierCount;
    while (tankCount > 0)
    {
        if (game->getEarthUnit(ET, tank)) {
            tank->getAttacked(this, timestep);
            tempEarthTanks.push(tank);
            --tankCount;
        }
        else break;
    }
    soldierCount += tankCount;
    while (soldierCount > 0)
    {
        if (game->getEarthUnit(ES, soldier)) {
            soldier->getAttacked(this, timestep);
            temp.enqueue(soldier);
            --soldierCount;
        }
        else break;
    }
    if (!tempEarthTanks.isEmpty()) {
        cout << "\tAM " << this << " shots ";
        cout << "\t";
        tempEarthTanks.print();
        if (!temp.isEmpty()) temp.print();
        cout << endl;
    }
    while (!tempEarthTanks.isEmpty())
    {
        Unit* tmp = nullptr;
        tempEarthTanks.pop(tmp);
        game->handleUnit(tmp);
    }
    while (!temp.isEmpty()) {
        temp.dequeue(soldier);
        game->handleUnit(soldier);
    }
}
