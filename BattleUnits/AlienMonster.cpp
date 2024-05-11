#include "AlienMonster.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"
#include "../DataStructures/LinkedListStack.h"
#include <cstdlib> 
#include <time.h> 
#include "EarthSoldier.h"


AlienMonster::AlienMonster(Game* game, int joinTime, double health, double power, int attackCapacity,int infectionPercent)
    : Unit(game,AM, joinTime, health, power, attackCapacity) {
    this->infectionPercent = infectionPercent;
    srand(time(0));
}

bool AlienMonster::attack() {
    int timestep = game->getTimestep();
    LinkedListStack<Unit*> tempEarthTanks;
    LinkedQueue<Unit*> temp;
    LinkedQueue<Unit*> temp2;
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
            temp2.enqueue(tank);
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
            if (this->willInfect()) {
                EarthSoldier* s1 = dynamic_cast<EarthSoldier*>(soldier);
                if (!s1->isInfected()) {
                    s1->setInfected(true);
                    game->incrementInfected();
                }
            }
            attacked = true;
        }
        else break;
    }
    while (soldierCount > 0) 
    {
        if (game->getEarthUnit(ET, tank)) {
            tank->getAttacked(this, timestep);
            tempEarthTanks.push(tank);
            temp2.enqueue(tank);
            --soldierCount;
            attacked = true;
        }
        else break;
    }
    if ((!temp2.isEmpty() || !temp.isEmpty()) && game->isInteractive()) {
        cout << "\tAM " << this << " shots ";
        cout << "\t";
        temp2.print();
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
    while (!temp2.isEmpty()) {
        temp2.dequeue(tank);
    }
    return attacked;
}

bool AlienMonster::willInfect()
{
    int random = rand() % 100;
    return (random <= infectionPercent);
}
