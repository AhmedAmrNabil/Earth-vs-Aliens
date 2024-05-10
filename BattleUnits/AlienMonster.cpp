#include "AlienMonster.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"
#include "../DataStructures/LinkedListStack.h"


AlienMonster::AlienMonster(Game* game, int joinTime, double health, double power, int attackCapacity)
    : Unit(game,AM, joinTime, health, power, attackCapacity) {
}

bool AlienMonster::attack() {
    int timestep = game->getTimestep();
    LinkedListStack<Unit*> tempEarthTanks;
    LinkedQueue<Unit*> temp;
    Unit* tank = nullptr;
    Unit* soldier = nullptr;
    int soldierCount = this->getAttackCapacity() / 2;
    int tankCount = this->getAttackCapacity() - soldierCount;
    bool attacked = false;
    while (tankCount > 0)
    {
        if (game->getEarthUnit(ET, tank)) {
            tank->getAttacked(this, timestep);
            tempEarthTanks.push(tank);
            --tankCount;
            attacked = true;
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
            attacked = true;
        }
        else break;
    }
    if ((!tempEarthTanks.isEmpty() || !temp.isEmpty()) && game->isInteractive()) {
        cout << "\tAM " << this << " shots ";
        cout << "\t";
        tempEarthTanks.print();
        temp.print();
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
    return attacked;
}
