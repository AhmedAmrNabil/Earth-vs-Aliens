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
    clearAttacked();
    for (int i = 0; i < this->getAttackCapacity() / 2; ++i) {
        if (game->getEarthUnit(ET, tank)) {
            tank->getAttacked(this, timestep);
            attackedIDs.enqueue(tank->getId());
            if (tank->isDead())
                game->addToKilled(tank);
            else
                tempEarthTanks.push(tank);
        }
        if (game->getEarthUnit(EG, gunnery)) {
            gunnery->getAttacked(this, timestep);
            attackedIDs.enqueue(gunnery->getId());
            if (gunnery->isDead())
                game->addToKilled(gunnery);
            else
                temp.enqueue(gunnery);
        }
    }
    if (this->getAttackCapacity() % 2 == 1) {
        if (game->getEarthUnit(ET, tank)) {
            tank->getAttacked(this, timestep);
            attackedIDs.enqueue(tank->getId());
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
