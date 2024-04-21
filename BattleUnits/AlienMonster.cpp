#include "AlienMonster.h"

#include "../Game.h"

AlienMonster::AlienMonster(Game* game, int joinTime, int health, int power, int attackCapacity)
    : Unit(game,AM, joinTime, health, power, attackCapacity) {
}

void AlienMonster::attack() {
    int timestep = game->getTimestep();
    LinkedListStack<Unit*> tempEarthTanks;
    LinkedQueue<Unit*> temp;
    LinkedQueue<Unit*> total;
    Unit* tank = nullptr;
    Unit* soldier = nullptr;
    int soldierCount = this->getAttackCapacity() / 2;
    int tankCount = this->getAttackCapacity() - soldierCount;
    while (tankCount > 0)
    {
        if (game->getEarthUnit(ET, tank)) {
            tank->getAttacked(this, timestep);
            tempEarthTanks.push(tank);
            total.enqueue(tank);
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
            total.enqueue(soldier);
            --soldierCount;
        }
        else break;
    }
    if (!total.isEmpty()) {
        cout << "\tAM " << this << " shots ";
        cout << "\t";
        total.print();
        cout << endl;
    }
    while (!tempEarthTanks.isEmpty()) 
    {
       Unit* tmp = nullptr;
       tempEarthTanks.pop(tmp);
       if (tmp->isDead())
           game->addToKilled(tmp);
       else
           game->addEarthUnit(tmp);
    }
    while (!temp.isEmpty()) {
        temp.dequeue(soldier);
        if (soldier->isDead())
            game->addToKilled(soldier);
        else
            game->addEarthUnit(soldier);
    }
    while (!total.isEmpty())
    {
        total.dequeue(tank);
    }
}
