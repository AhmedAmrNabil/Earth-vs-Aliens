#include "AlienDrone.h"

#include "../Game.h"

AlienDrone::AlienDrone(Game* game, int joinTime, int health, int power, int attackCapacity)
    : Unit(game,AD,joinTime, health, power, attackCapacity) {
}

void AlienDrone::attack() {
    int timestep = game->getTimestep();
    LinkedListStack<Unit*> tempEarthTanks;
    LinkedQueue<Unit*> temp;
    Unit* tank = nullptr;
    Unit* gunnery = nullptr;
    int gunnerCount = this->getAttackCapacity() / 2;
    int tankCount=this->getAttackCapacity()- gunnerCount;
    while (tankCount > 0) 
    {
        if (game->getEarthUnit(ET, tank)) {
            tank->getAttacked(this, timestep);
            tempEarthTanks.push(tank);
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
            --gunnerCount;
        }
        else break;
    }
    tempEarthTanks.print();
    while (!tempEarthTanks.isEmpty()) {
        Unit* tmp = nullptr;
        tempEarthTanks.pop(tmp);
        if (tmp->isDead())
            game->addToKilled(tmp);
        else
            game->addEarthUnit(tmp);
    }
    temp.print();
    while (!temp.isEmpty()) {
        temp.dequeue(gunnery);
        if(gunnery->isDead())
            game->addToKilled(gunnery);
        else
            game->addEarthUnit(gunnery);
    }
}
