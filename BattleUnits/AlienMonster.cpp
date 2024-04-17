#include "AlienMonster.h"

#include "../Game.h"

AlienMonster::AlienMonster(Game* game, int joinTime, int health, int power, int attackCapacity)
    : Unit(game,AM, joinTime, health, power, attackCapacity) {
}

void AlienMonster::attack() {
    int timestep = game->getTimestep();
    LinkedListStack<Unit*> tempEarthTanks;
    LinkedQueue<Unit*> temp;
    Unit* tank = nullptr;
    Unit* soldier = nullptr;
    for (int i = 0; i < this->getAttackCapacity() / 2; ++i) {
        if (game->getEarthUnit(ET, tank)) {
            tank->getAttacked(this, timestep);
            if (tank->isDead())
                game->addToKilled(tank);
            else
                tempEarthTanks.push(tank);
        }
        if (game->getEarthUnit(ES, soldier)) {
            soldier->getAttacked(this, timestep);
            if (soldier->isDead())
                game->addToKilled(soldier);
            else
                temp.enqueue(soldier);
        }
    }
    if (this->getAttackCapacity() % 2 == 1) {
        if (game->getEarthUnit(ET, tank)) {
            tank->getAttacked(this, timestep);
            attackedIDs.enqueue(tank->getId());
            if (tank->isDead())
                game->addToKilled(tank);
            else
                tempEarthTanks.push(tank);
        }
    }
    while (!tempEarthTanks.isEmpty()) {
        Unit* tmp = nullptr;
        tempEarthTanks.pop(tank);
        game->addEarthUnit(tmp);
    }
    while (!temp.isEmpty()) {
        temp.dequeue(soldier);
        game->addEarthUnit(soldier);
    }
}
