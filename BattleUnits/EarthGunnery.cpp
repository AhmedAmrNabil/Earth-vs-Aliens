#include "EarthGunnery.h"
#include "../Game.h"
#include <cmath>

EarthGunnery::EarthGunnery(Game* game, int joinTime, int health, int power, int attackCapacity)
    : Unit(game,EG, joinTime, health, power, attackCapacity) {
};

int EarthGunnery::getPriority() {
    return power * sqrt(health);
}

void EarthGunnery::attack() {
    int timestep = game->getTimestep();
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
