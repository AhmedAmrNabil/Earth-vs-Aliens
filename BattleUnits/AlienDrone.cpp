#include "AlienDrone.h"
#include "../Game.h"
#include "../DataStructures/LinkedListStack.h"
#include "../DataStructures/LinkedQueue.h"



AlienDrone::AlienDrone(Game* game, int joinTime, double health, double power, int attackCapacity)
    : Unit(game,AD,joinTime, health, power, attackCapacity) {
}

bool AlienDrone::attack() {
    int timestep = game->getTimestep();
    LinkedListStack<Unit*> tempListTank;
    LinkedQueue<Unit*> tempListGunnery;
    LinkedQueue<Unit*> tempListPrint;
    Unit* enemyUnit = nullptr;
    int tankCount = this->getAttackCapacity() / 2;
    int gunnerCount =this->getAttackCapacity()- tankCount;
    bool attacked = false;
    while (gunnerCount > 0)
    {
        if (game->getEarthUnit(EG, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListGunnery.enqueue(enemyUnit);
            --gunnerCount;
            attacked = true;
        }
        else break;
    }

    // Adds the leftover capcity from gunnery if there are no gunneries left
    tankCount += gunnerCount;
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

    // Attacks the tanks with the leftover gunnery capcity
    while (tankCount > 0)
    {
        if (game->getEarthUnit(EG, enemyUnit)) {
            enemyUnit->getAttacked(this, timestep);
            tempListGunnery.enqueue(enemyUnit);
            --tankCount;
            attacked = true;
        }
        else break;
    }

    // Print the attacked units
    if (game->isInteractive() && (!tempListPrint.isEmpty() || !tempListGunnery.isEmpty())) {
        string attackedIds = "\tAD ";
        attackedIds += this;
        attackedIds += " shots\t";
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

        if (tempListGunnery.dequeue(enemyUnit)) {
            attackedIds += "[";
            attackedIds += enemyUnit;
            game->handleUnit(enemyUnit);
            while (!tempListGunnery.isEmpty()) {
                tempListGunnery.dequeue(enemyUnit);
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
    while (!tempListTank.isEmpty()) {
        tempListTank.pop(enemyUnit);
        game->handleUnit(enemyUnit);
    }
    while (!tempListGunnery.isEmpty()) {
        tempListGunnery.dequeue(enemyUnit);
        game->handleUnit(enemyUnit);
    }
    while (!tempListPrint.isEmpty()) {
        tempListPrint.dequeue(enemyUnit);
    }
    return attacked;
}
