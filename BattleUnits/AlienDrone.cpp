#include "AlienDrone.h"

#include "../Game.h"

AlienDrone::AlienDrone(int id, int joinTime, int health, int power, int attackCapacity)
    : Unit(AD, id, joinTime, health, power, attackCapacity) {
    priority = 1;
}

void AlienDrone::attack(Game* game, int timestep) {
    LinkedListStack<Unit*> tempEarthTanks;
    LinkedQueue<Unit*> temp;
    Unit* tank = nullptr;
    Unit* gunnery = nullptr;
    clearAttacked();
    for (int i = 0; i < this->getAttackCapacity() / 2; ++i) {
        if (game->getEarthUnit(ET, tank)) {
            tank->getAttacked(this, timestep);
            if (tank->isDead())
                game->addToKilled(tank);
            else
                tempEarthTanks.push(tank);
        }
        if (game->getEarthUnit(EG, gunnery)) {
            gunnery->getAttacked(this, timestep);
            if (gunnery->isDead())
                game->addToKilled(gunnery);
            else
                temp.enqueue(gunnery);
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
        tempEarthTanks.pop(tmp);
        game->addEarthUnit(tmp);
    }
    while (!temp.isEmpty()) {
        temp.dequeue(gunnery);
        game->addEarthUnit(gunnery);
    }
}
