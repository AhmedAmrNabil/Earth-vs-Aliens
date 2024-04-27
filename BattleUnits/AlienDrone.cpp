#include "AlienDrone.h"
#include "../Game.h"
#include "../DataStructures/LinkedListStack.h"
#include "../DataStructures/LinkedQueue.h"



AlienDrone::AlienDrone(Game* game, int joinTime, double health, double power, int attackCapacity)
    : Unit(game,AD,joinTime, health, power, attackCapacity) {
}

void AlienDrone::attack() {
    int timestep = game->getTimestep();
    LinkedListStack<Unit*> tempEarthTanks;
    LinkedQueue<Unit*> temp;
    LinkedQueue<Unit*> total;
    Unit* tank = nullptr;
    Unit* gunnery = nullptr;
    int gunnerCount = this->getAttackCapacity() / 2;
    int tankCount=this->getAttackCapacity()- gunnerCount;
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
    gunnerCount += tankCount;
    while (gunnerCount > 0)
    {
        if (game->getEarthUnit(EG, gunnery)) {
            gunnery->getAttacked(this, timestep);
            temp.enqueue(gunnery);
            total.enqueue(gunnery);
            --gunnerCount;
        }
        else break;
    }
    if (!total.isEmpty()) {
        cout << "\tAD " << this << " shots ";
        cout << "\t";
        total.print();
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
    while (!total.isEmpty()) 
    {
        total.dequeue(tank);
    }
}
