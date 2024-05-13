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
    LinkedListStack<Unit*> tempListTank;
    LinkedQueue<Unit*> tempListSoldier;
    LinkedQueue<Unit*> tempListPrint;
    Unit* enemyUnit = nullptr;
    int soldierCount = this->getAttackCapacity() / 2;
    int tankCount = this->getAttackCapacity() - soldierCount;
    bool attacked = false;
    while (tankCount > 0)
    {
        if (game->getEarthUnit(ET, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListTank.push(enemyUnit);
            tempListPrint.enqueue(enemyUnit);
            --tankCount;
            attacked = true;
        }
        else break;
    }
    soldierCount += tankCount;
    while (soldierCount > 0)
    {
        if (game->getEarthUnit(ES, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListSoldier.enqueue(enemyUnit);
            --soldierCount;
            if (this->willInfect()) {
                EarthSoldier* soldier = dynamic_cast<EarthSoldier*>(enemyUnit);
                if (!soldier->isInfected() && !soldier->isImmune()) {
                    soldier->setInfected(true);
                    game->incrementInfected();
                }
            }
            attacked = true;
        }
        else break;
    }
    while (soldierCount > 0) 
    {
        if (game->getEarthUnit(ET, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListTank.push(enemyUnit);
            tempListPrint.enqueue(enemyUnit);
            --soldierCount;
            attacked = true;
        }
        else break;
    }
    if (game->isInteractive() && (!tempListSoldier.isEmpty() || !tempListPrint.isEmpty())) {
        string attackedIds = "\tAM ";
        attackedIds += this;
        attackedIds += " shots\t";
        if (tempListSoldier.dequeue(enemyUnit)) {
            attackedIds += "[";
            game->handleUnit(enemyUnit);
            attackedIds += enemyUnit;
            while (!tempListSoldier.isEmpty()) {
                tempListSoldier.dequeue(enemyUnit);
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
    while (!tempListTank.isEmpty())
    {
        tempListTank.pop(enemyUnit);
        game->handleUnit(enemyUnit);
    }
    while (!tempListSoldier.isEmpty()) {
        tempListSoldier.dequeue(enemyUnit);
        game->handleUnit(enemyUnit);
    }
    while (!tempListPrint.isEmpty()) {
        tempListPrint.dequeue(enemyUnit);
    }
    return attacked;
}

bool AlienMonster::willInfect()
{
    int random = rand() % 100;
    return (random <= infectionPercent);
}
