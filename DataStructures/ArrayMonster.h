#pragma once
#include "../BattleUnits/AlienMonster.h"
#include <cmath>
#include <cstdlib> 
#include <time.h> 
class ArrayMonster
{
private:
    AlienMonster* arrayMonster[1000];
    int monsterCount;
public:
    ArrayMonster():arrayMonster()
    {
        monsterCount = 0;
    }
    bool isEmpty()
    {
        return (monsterCount == 0);
    }
    bool isFull()
    {
        return (monsterCount == 1000);
    }
    bool insert(AlienMonster* a1)
    {
        if (!isFull())
        {
            arrayMonster[monsterCount++] = a1;
            return true;
        }
        return false;
    }
    bool pick(AlienMonster*& AM)
    {
        if (!isEmpty())
        {
            srand(time(0));
            int random = 0 + (rand() % monsterCount);
            AM=arrayMonster[random];
            return true;
        }
        return false;
    }
};
