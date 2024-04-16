#include "EarthGunner.h"

#include "../Game.h"

EarthGunner::EarthGunner(Game* game, int joinTime, int health, int power, int attackCapacity)
    : Unit(game,EG, joinTime, health, power, attackCapacity) {
};

void EarthGunner::attack() {
    int timestep = game->getTimestep();
    clearAttacked();
    Unit* drone = nullptr;
    Unit* monster = nullptr;
    LinkedListStack<Unit*> tempDrone;
    LinkedQueue<Unit*> tempMonster;

    int monsterCount = this->getAttackCapacity() / 2;
    int dronesCount = this->getAttackCapacity() - monsterCount;
    int dronesAttacked = 0;
    while (monsterCount > 0) {
        if (game->getAlienUnit(AM, monster)) {
            monster->getAttacked(this, timestep);
            attackedIDs.enqueue(monster->getId());
            if (monster->isDead())
                game->addToKilled(monster);
            else
                tempMonster.enqueue(monster);
        }
        --monsterCount;
    }

    while (dronesAttacked < dronesCount) {
        if (game->getAlienUnit(AD, drone)) {
            drone->getAttacked(this, timestep);
            attackedIDs.enqueue(drone->getId());
            if (drone->isDead())
                game->addToKilled(drone);
            else
                tempDrone.push(drone);
        }
        ++dronesAttacked;
    }

    while (!tempDrone.isEmpty()) {
        tempDrone.pop(drone);
        game->addAlienUnit(drone);
    }
    while (!tempMonster.isEmpty()) {
        tempMonster.dequeue(monster);
        game->addAlienUnit(monster);
    }
}
