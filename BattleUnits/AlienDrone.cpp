#include "AlienDrone.h"
#include "../Game.h"
#include "../DataStructures/LinkedListStack.h"
#include "../DataStructures/LinkedQueue.h"



AlienDrone::AlienDrone(Game* game, int joinTime, double health, double power, int attackCapacity)
    : Unit(game,AD,joinTime, health, power, attackCapacity) {
}

bool AlienDrone::attack() {
    int timestep = game->getTimestep();
    LinkedListStack<Unit*> tempEarthTanks;
    LinkedQueue<Unit*> temp;
    Unit* tank = nullptr;
    Unit* gunnery = nullptr;
    int gunnerCount = this->getAttackCapacity() / 2;
    int tankCount=this->getAttackCapacity()- gunnerCount;
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
    gunnerCount += tankCount;
    while (gunnerCount > 0)
    {
        if (game->getEarthUnit(EG, gunnery)) {
            gunnery->getAttacked(this, timestep);
            temp.enqueue(gunnery);
            --gunnerCount;
            attacked = true;
        }
        else break;
    }
    if ((!tempEarthTanks.isEmpty() || !temp.isEmpty()) && game->isInteractive()) {
        cout << "\tAD " << this << " shots ";
        cout << "\t";
        tempEarthTanks.print();
        temp.print();
        cout << endl;
    }
    while (!tempEarthTanks.isEmpty()) {
        Unit* tmp = nullptr;
        tempEarthTanks.pop(tmp);
        game->handleUnit(tmp);
    }
    while (!temp.isEmpty()) {
        temp.dequeue(gunnery);
        game->handleUnit(gunnery);
    }
    return attacked;
}
