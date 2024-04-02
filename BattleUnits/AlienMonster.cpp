#include "AlienMonster.h"

void AlienMonster::attack(Game* game, int timestep)
{
    LinkedQueue<Unit*> tempSoldiers;
    LinkedListStack<Unit*> tempEarthTanks;
    Unit* T1 = nullptr;
    Unit* S1 = nullptr;

    for (int i = 0; i < this->getAttackCapacity(); ++i)
    {
        if (game->getEarthUnit(ET, T1)) {
            T1->getAttacked(this, timestep);
            if (T1->isDead())
                game->addToKilled(T1);
            else
                tempEarthTanks.push(T1);
        }
        if (game->getEarthUnit(AS, S1)) {
            S1->getAttacked(this, timestep);
            if (S1->isDead())
                game->addToKilled(S1);
            else
                tempSoldiers.enqueue(S1);
        }
    }
    Unit* temp = nullptr;
    while (!tempSoldiers.isEmpty())
    {
        tempSoldiers.dequeue(temp);
        game->addExistingEarthUnit(AS, temp);
    }
    while (!tempEarthTanks.isEmpty())
    {
        tempEarthTanks.pop(temp);
        game->addExistingEarthUnit(ET, temp);
    }
}
