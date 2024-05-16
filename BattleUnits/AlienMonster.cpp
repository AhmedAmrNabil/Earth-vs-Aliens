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
    srand(int(time(0)));
}

bool AlienMonster::attack() {
    int timestep = game->getTimestep();
    LinkedListStack<Unit*> tempListTank;
    LinkedQueue<Unit*> tempListSoldier;
    LinkedQueue<Unit*> tempListPrint; // Used to print the ids in the proper order
    LinkedQueue<Unit*> tempListSaver;
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

    // Adds the leftover capcity from tanks if there are no tanks left
    soldierCount += tankCount;

    int soldiercount2 = soldierCount;
    int saverCount = 0;
    if (game->saverIsActive()) {
        // Split the solider count between saver units and earth soldiers
        soldiercount2 /= 2;
        saverCount = soldierCount - soldiercount2;
    }
    while (soldiercount2 > 0) {
        if (game->getEarthUnit(ES, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListSoldier.enqueue(enemyUnit);
            --soldierCount;
            --soldiercount2;
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
    // Adds the leftover capcity from soldier if there are no soldiers left
    saverCount += soldiercount2;
    while (saverCount > 0)
    {
        if (game->getSaverUnit(enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListSaver.enqueue(enemyUnit);
            attacked = true;
            --soldierCount;
            --saverCount;
        }
        else break;
    }

    // Attacks the earth soldiers with the leftover saver unit capcity
    while (saverCount > 0) {
        if (game->getEarthUnit(ES, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListSoldier.enqueue(enemyUnit);
            --soldierCount;
            --saverCount;
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

    // Attacks the tanks with the leftover soldier capcity
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

    // Print the attacked units
    if (game->isInteractive() && (!tempListSoldier.isEmpty() || !tempListPrint.isEmpty() || !tempListSaver.isEmpty())) {
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
        if (tempListSaver.dequeue(enemyUnit)) {
            attackedIds += "[";
            game->handleUnit(enemyUnit);
            attackedIds += enemyUnit;
            while (!tempListSaver.isEmpty()) {
                tempListSaver.dequeue(enemyUnit);
                game->handleUnit(enemyUnit);
                attackedIds += ", ";
                attackedIds += enemyUnit;
            }
            attackedIds += "]";
        }

        attackedIds += '\n';
        game->addToAttacked(attackedIds);

    }

    // Handle the attacked units if the game is in silent mode
    while (!tempListTank.isEmpty())
    {
        tempListTank.pop(enemyUnit);
        game->handleUnit(enemyUnit);
    }
    while (!tempListSoldier.isEmpty()) {
        tempListSoldier.dequeue(enemyUnit);
        game->handleUnit(enemyUnit);
    }
    while (!tempListSaver.isEmpty()) {
        tempListSaver.dequeue(enemyUnit);
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
