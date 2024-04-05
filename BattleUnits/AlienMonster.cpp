#include "AlienMonster.h"

#include "../Game.h"

AlienMonster::AlienMonster(int id, int joinTime, int health, int power, int attackCapacity)
    : Unit(AM, id, joinTime, health, power, attackCapacity) {
    priority = 1;
}

void AlienMonster::attack(Game* game, int timestep) {
    LinkedListStack<Unit*> tempEarthTanks;
    LinkedQueue<Unit*> temp;
    Unit* tank = nullptr;
    Unit* soldier = nullptr;
    clearAttacked();
    for (int i = 0; i < this->getAttackCapacity(); ++i) {
        if (game->getEarthUnit(ET, tank)) {
            tank->getAttacked(this, timestep);
            if (tank->isDead())
                game->addToKilled(tank);
            else
                tempEarthTanks.push(tank);
        }
        if (game->getEarthUnit(AS, soldier)) {
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
