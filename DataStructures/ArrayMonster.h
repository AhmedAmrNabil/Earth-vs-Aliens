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
    ArrayMonster()
    {
        for (int i = 0; i < 1000; i++)
        {
            arrayMonster[i] = nullptr;
        }
        monsterCount = 0;
    }
    bool isEmpty()
    {
        if (monsterCount == 0)
            return true;
        return false;
    }
    bool isFull()
    {
        if (monsterCount == 1000)
            return true;
        return false;
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